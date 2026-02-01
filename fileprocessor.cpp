#include "fileprocessor.h"
#include <QDirIterator>
#include <QFile>
#include <QDebug>

FileProcessor::FileProcessor(QObject *parent)
    : QObject{parent}
{}

void FileProcessor::processFiles(const ProcessingSettings& settings) {
    emit statusUpdated("Searching files");
    emit progressChanged(0);

    QDirIterator it(QFileInfo(settings.fileMask).path(), {QFileInfo(settings.fileMask).fileName()}, QDir::Files);
    QList<QString> filesToProcess;

    while(it.hasNext()) {
        filesToProcess.append(it.next());
    }

    if (filesToProcess.empty()) {
        emit statusUpdated("There is no files to work with");
        emit finished();
        return;
    }

    int count = filesToProcess.size();
    emit statusUpdated(QString("Find %1 files").arg(count));

    for (int i = 0; i < count; i++) {
        const QString& filePath = filesToProcess.at(i);
        emit statusUpdated(QString("Work with  %1 from %2: %3").arg(i + 1).arg(count).arg(QFileInfo(filePath).fileName()));

        QFileInfo fileInfo(filePath);

        QFile inFile(filePath);
        if (!inFile.open(QIODevice::ReadOnly)) {
            emit statusUpdated("Error to open file");
            continue;
        }

        QString baseName = fileInfo.baseName();
        QString sufFile = fileInfo.suffix();
        QString outFilePath = settings.outputPath + "/" + fileInfo.fileName();
        if (settings.onDuplicateAction == 1) {
            int num = 1;
            while (QFile::exists(outFilePath)) {
                outFilePath = QString("%1/%2_%3.%4").arg(settings.outputPath).arg(baseName).arg(num++).arg(sufFile);
            }
        }

        QFile outFile(outFilePath);
        if (!outFile.open(QIODevice::WriteOnly)) {
            emit statusUpdated("Error: Can't create output file: " + outFilePath);
            inFile.close();
            continue;
        }

        const qint64 bufferSize = 4096;
        char buffer[bufferSize];
        qint64 bytesRead;
        while ((bytesRead = inFile.read(buffer, bufferSize)) > 0) {
            for(qint64 j = 0; j < bytesRead; j++) {
                buffer[j] ^= reinterpret_cast<const char*>(&settings.xorKey)[j % sizeof(qint64)];
            }
            outFile.write(buffer, bytesRead);
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
