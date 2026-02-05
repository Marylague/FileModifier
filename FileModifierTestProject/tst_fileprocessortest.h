#ifndef TST_FILEPROCESSORTEST_H
#define TST_FILEPROCESSORTEST_H

#include <QObject>
#include <QTemporaryDir>
#include "../fileprocessor.h"

class FileProcessorTest : public QObject
{
    Q_OBJECT

public:
    FileProcessorTest();
    ~FileProcessorTest();

private slots:
    void initTestCase();
    void init();
    void cleanupTestCase();
    void cleanup();

    void testBasicProcessing();
    void testDeleteSource();
    void testDuplicateRename();
    void testNoFilesFound();
    void testSignalEmissions();

private:
    void createTestFile(const QString& path, const QString& content);
    QByteArray xorCrypt(const QByteArray& data, const QByteArray& key);

    QTemporaryDir tempDir;
    QString inputPath;
    QString outputPath;
    FileProcessor* processor;
};

#endif // TST_FILEPROCESSORTEST_H
