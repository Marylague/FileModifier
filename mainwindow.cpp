#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainThread = new QThread(this);
    mainProcessor = new FileProcessor();
    mainProcessor->moveToThread(mainThread);

    connect(this, &MainWindow::startProcess, mainProcessor, &FileProcessor::processFiles);
    connect(ui->StartStopButton, &QPushButton::clicked, this, &MainWindow::on_StartStopButton_clicked);
    connect(mainProcessor, &FileProcessor::progressChanged, ui->progressBar, &QProgressBar::setValue);
    connect(mainProcessor, &FileProcessor::statusUpdated, ui->TextStatusLabel, &QLabel::setText);

    connect(mainProcessor, &FileProcessor::finished, this, [this]() {
        ui->StartStopButton->setEnabled(true);
        if(ui->Timer->isChecked()) {
            mainTimer->start();
        }
    });

    mainThread->start();
    mainTimer = new QTimer(this);
    connect(mainTimer, &QTimer::timeout, this, &MainWindow::processByTimer);

}

MainWindow::~MainWindow()
{
    mainThread->quit();
    mainThread->wait();
    delete ui;
}

void MainWindow::on_StartStopButton_clicked() {
    if (ui->SingleShot->isChecked()) {
        processByTimer();
        return;
    }
    if (mainTimer->isActive()) {
        mainTimer->stop();
        ui->TextStatusLabel->setText("Таймер остановлен");
    } else {
        int interval = ui->TimerInterval->value() * 1000;
        mainTimer->start(interval);
        ui->TextStatusLabel->setText("Таймер начат");
    }
}

void MainWindow::processByTimer() {
    if (mainTimer->isActive()) {
        mainTimer->stop();
        ui->TextStatusLabel->setText("Таймер остановлен");
    }
    ui->StartStopButton->setEnabled(false);

    ProcessingSettings newSettings;
    newSettings.inputPath = ui->FilesInput->text();
    newSettings.fileMask = ui->FileMask->text();
    newSettings.outputPath = ui->FilesOutput->text();
    newSettings.deleteSource = ui->DeleteSource->isChecked();
    newSettings.onDuplicateAction = ui->DubleActions->currentIndex();

    QByteArray key = QByteArray::fromHex(ui->HexKey->text().toLatin1());

    if (key.isEmpty()) {
        ui->TextStatusLabel->setText("Ошибка: введите ключ для шифрования.");
        return;
    }

    if (key.size() != 8) {
        ui->TextStatusLabel->setText("Ошибка: ключ должен состоять ровно из 16-ти hex-символов.");
        ui->StartStopButton->setEnabled(true);
        return;
    }

    newSettings.xorKey = key;
    emit startProcess(newSettings);
}

void MainWindow::on_BrowseButtonOutput_clicked() {
    QString directory = QFileDialog::getExistingDirectory(this, "Выбрать папку для сохранения");
    if (!directory.isEmpty()) {
        ui->FilesOutput->setText(directory);
    }
}

void MainWindow::on_BrowseButtonInput_clicked() {
    QString directory = QFileDialog::getExistingDirectory(this, "Выбрать входную папку");
    if (!directory.isEmpty()) {
        ui->FilesInput->setText(directory);
    }
}
