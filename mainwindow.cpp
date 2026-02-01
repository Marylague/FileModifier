#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainThread = new QThread(this);
    mainProcessor = new FileProcessor();
    mainProcessor->moveToThread(mainThread);

    connect(this, &MainWindow::startProcess, mainProcessor, &FileProcessor::processFiles);

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

void MainWindow::clickOnButtonStart_Stop() {
    if (ui->SingleShot->isChecked()) {
        processByTimer();
        return;
    }
    if (mainTimer->isActive()) {
        mainTimer->stop();
        ui->TextStatusLabel->setText("Timer Stopped");
    } else {
        int interval = ui->TimerInterval->value() * 1000;
        mainTimer->start(interval);
        ui->TextStatusLabel->setText("Timer Started");
    }
}

void MainWindow::processByTimer() {
    if (mainTimer->isActive()) {
        mainTimer->stop();
        ui->TextStatusLabel->setText("Timer Stopped");
    }
    ui->StartStopButton->setEnabled(false);

    ProcessingSettings newSettings;
    newSettings.fileMask = ui->FileMask->text();
    newSettings.outputPath = ui->FilesOutput->text();
    newSettings.deleteSource = ui->DeleteSource->isChecked();
    newSettings.onDuplicateAction = ui->DubleActions->currentIndex();

    bool ok;
    quint64 key =ui->HexKey->text().toULongLong(&ok, 16);
    if (!ok) {
        ui->TextStatusLabel->setText("Error: unsupported hex key!");
        ui->StartStopButton->setEnabled(true);
        return;
    }
    emit startProcess(newSettings);
}
