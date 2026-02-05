#include <QTest>
#include <QSignalSpy>
#include "tst_fileprocessortest.h"

FileProcessorTest::FileProcessorTest()
    : processor(nullptr)
{}

FileProcessorTest::~FileProcessorTest() {}

void FileProcessorTest::initTestCase()
{
    QVERIFY(tempDir.isValid());
    inputPath = tempDir.path() + "/input";
    outputPath = tempDir.path() + "/output";
    QDir().mkdir(inputPath);
    QDir().mkdir(outputPath);
}

void FileProcessorTest::init()
{
    processor = new FileProcessor();

    QDir dir(outputPath);
    dir.removeRecursively();
    QDir().mkdir(outputPath);
}

void FileProcessorTest::cleanupTestCase()
{
    tempDir.remove();
}

void FileProcessorTest::cleanup()
{
    delete processor;
    processor = nullptr;
}

void FileProcessorTest::createTestFile(const QString& path, const QString& content)  {
    QFile file(path);
    QVERIFY(file.open(QIODevice::WriteOnly));
    file.write(content.toUtf8());
    file.close();
}

QByteArray FileProcessorTest::xorCrypt(const QByteArray& data, const QByteArray& key) {
    QByteArray result = data;
    const char* keyBytes = key.constData();
    const int keySize = key.size();
    for (int i = 0; i < result.size(); ++i) {
        result[i] = result[i] ^ keyBytes[i % keySize];
    }
    return result;
}

void FileProcessorTest::testBasicProcessing() {
    const QString originalContent = "Hello, World!";
    createTestFile(inputPath + "/test.txt", originalContent);

    ProcessingSettings settings;
    settings.inputPath = inputPath;
    settings.outputPath = outputPath;
    settings.fileMask = "*.txt";
    settings.deleteSource = false;
    settings.onDuplicateAction = 0;
    settings.xorKey = QByteArray::fromHex("1234567890123456");

    processor->processFiles(settings);

    QVERIFY(QFile::exists(inputPath + "/test.txt"));

    QString outFilePath = outputPath + "/test.txt";
    QVERIFY(QFile::exists(outFilePath));

    QFile outFile(outFilePath);
    QVERIFY(outFile.open(QIODevice::ReadOnly));
    QByteArray encryptedContent = outFile.readAll();
    outFile.close();

    QByteArray decryptedContent = xorCrypt(encryptedContent, settings.xorKey);
    QCOMPARE(decryptedContent, originalContent.toUtf8());
}

void FileProcessorTest::testDeleteSource() {
    createTestFile(inputPath + "/file_to_delete.txt", "Some data");

    ProcessingSettings settings;
    settings.inputPath = inputPath;
    settings.outputPath = outputPath;
    settings.fileMask = "*.txt";
    settings.deleteSource = true;
    settings.onDuplicateAction = 0;
    settings.xorKey = QByteArray::fromHex("FFFFFFFF");

    processor->processFiles(settings);

    QVERIFY(!QFile::exists(inputPath + "/file_to_delete.txt"));

    QVERIFY(QFile::exists(outputPath + "/file_to_delete.txt"));
}

void FileProcessorTest::testDuplicateRename() {
    createTestFile(outputPath + "/duplicate.txt", "old file.");
    createTestFile(inputPath + "/duplicate.txt", "new file.");

    ProcessingSettings settings;
    settings.inputPath = inputPath;
    settings.outputPath = outputPath;
    settings.fileMask = "*.txt";
    settings.deleteSource = false;
    settings.onDuplicateAction = 1;
    settings.xorKey = QByteArray::fromHex("03057304");

    processor->processFiles(settings);

   QFile oldFile(outputPath + "/duplicate.txt");
    QVERIFY(oldFile.open(QIODevice::ReadOnly));
    QCOMPARE(oldFile.readAll(), QByteArray("old file."));
    oldFile.close();

    QString newFilePath = outputPath + "/duplicate_1.txt";
    QVERIFY(QFile::exists(newFilePath));

    QFile newFile(newFilePath);
    QVERIFY(newFile.open(QIODevice::ReadOnly));
    QByteArray decryptedContent = xorCrypt(newFile.readAll(), settings.xorKey);
    QCOMPARE(decryptedContent, QByteArray("new file."));
    newFile.close();
}

void FileProcessorTest::testNoFilesFound() {
    ProcessingSettings settings;
    settings.inputPath = inputPath;
    settings.outputPath = outputPath;
    settings.fileMask = "*.blabla";
    settings.xorKey = QByteArray::fromHex("112233");

    QSignalSpy finishedSpy(processor, &FileProcessor::finished);
    QSignalSpy statusSpy(processor, &FileProcessor::statusUpdated);

    processor->processFiles(settings);

    QCOMPARE(finishedSpy.count(), 1);

    QVERIFY(!statusSpy.isEmpty());
    QCOMPARE(statusSpy.last().at(0).toString(), "Нет файлов для обработки");
}

void FileProcessorTest::testSignalEmissions() {
    createTestFile(inputPath + "/file1.log", "data1");
    createTestFile(inputPath + "/file2.log", "data2");

    ProcessingSettings settings;
    settings.inputPath = inputPath;
    settings.outputPath = outputPath;
    settings.fileMask = "*.log";
    settings.deleteSource = false;
    settings.onDuplicateAction = 0;
    settings.xorKey = QByteArray::fromHex("ABCDEF");

    QSignalSpy progressSpy(processor, &FileProcessor::progressChanged);
    QSignalSpy finishedSpy(processor, &FileProcessor::finished);

    processor->processFiles(settings);

    QCOMPARE(finishedSpy.count(), 1);

    QCOMPARE(progressSpy.count(), 3);

    QList<QVariant> initialProgress = progressSpy.takeFirst();
    QCOMPARE(initialProgress.at(0).toInt(), 0);

    QList<QVariant> firstProgress = progressSpy.takeFirst();
    QCOMPARE(firstProgress.at(0).toInt(), 50);

    QList<QVariant> secondProgress = progressSpy.takeFirst();
    QCOMPARE(secondProgress.at(0).toInt(), 100);
}


QTEST_APPLESS_MAIN(FileProcessorTest)
