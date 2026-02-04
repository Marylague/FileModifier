#include "fileprocessor.h"
#include <QDirIterator>
#include <QFile>
#include <QDebug>

FileProcessor::FileProcessor(QObject *parent)
    : QObject{parent}
{}

void FileProcessor::processFiles(const ProcessingSettings& settings) {
    emit statusUpdated("Поиск файлов");
    emit progressChanged(0);

    QDirIterator it(settings.inputPath, {settings.fileMask}, QDir::Files);
    QList<QString> filesToProcess;

    while(it.hasNext()) {
        filesToProcess.append(it.next());
    }

    if (filesToProcess.empty()) {
        emit statusUpdated("Нет файлов для обработки");
        emit finished();
        return;
    }

    int count = filesToProcess.size();
    emit statusUpdated(QString("Файлов найдено: %1").arg(count));

    for (int i = 0; i < count; i++) {
        const QString& filePath = filesToProcess.at(i);
        emit statusUpdated(QString("Работаем с  %1 из %2: %3").
                           arg(i + 1).arg(count).arg(QFileInfo(filePath).fileName()));

        QFileInfo fileInfo(filePath);
        QFile inFile(filePath);

        if (!inFile.open(QIODevice::ReadOnly)) {
            emit statusUpdated("Ошибка открытия файла");
            continue;
        }

        QString outFilePath;

        if (settings.onDuplicateAction == 1) {

            const QString baseName = fileInfo.baseName();
            const QString suffix = fileInfo.suffix();
            if (suffix.isEmpty()) {
                outFilePath = QString("%1/%2_1")
                                  .arg(settings.outputPath).arg(baseName);
            } else {
                outFilePath = QString("%1/%2_1.%3").arg(settings.outputPath).arg(baseName).arg(suffix);
            }

        } else {
            outFilePath = settings.outputPath + "/" + fileInfo.fileName();
        }

        QFile outFile(outFilePath);
        if (!outFile.open(QIODevice::WriteOnly)) {
            emit statusUpdated("Ошибка: невозможжно создать файл вывода: " + outFilePath);
            inFile.close();
            continue;
        }

        const qint64 bufferSize = 4096;
        char buffer[bufferSize];
        qint64 bytesRead;

        qint64 totalPosition = 0;

        const char* keyBytes = settings.xorKey.constData();
        const int keySize = settings.xorKey.size();

        while ((bytesRead = inFile.read(buffer, bufferSize)) > 0) {
            for (qint64 j = 0; j < bytesRead; ++j) {
                buffer[j] ^= keyBytes[(totalPosition + j) % keySize];
            }
            outFile.write(buffer, bytesRead);

            totalPosition += bytesRead;
        }

        inFile.close();
        outFile.close();

        if (settings.deleteSource) {
            QFile::remove(filePath);
        }

        emit progressChanged((i + 1) * 100 / count);
    }

    emit statusUpdated("Обработка завершена.");
    emit finished();
}
