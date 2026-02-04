#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>

struct ProcessingSettings {
    QString inputPath;
    QString fileMask;
    QString outputPath;
    bool deleteSource;
    int onDuplicateAction;
    QByteArray xorKey;
};

class FileProcessor : public QObject
{
    Q_OBJECT
public:
    explicit FileProcessor(QObject *parent = nullptr);

public slots:
    void processFiles(const ProcessingSettings& settings);

signals:
    void progressChanged(int value);
    void statusUpdated(const QString& status);
    void finished();
};

#endif // FILEPROCESSOR_H
