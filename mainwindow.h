#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "fileprocessor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_StartStopButton_clicked();
    void on_BrowseButtonOutput_clicked();
    void on_BrowseButtonInput_clicked();
    void processByTimer();
    void onTimerTick();

signals:
    void startProcess(const ProcessingSettings& settings);

private:
    Ui::MainWindow *ui;
    QThread* mainThread;
    FileProcessor* mainProcessor;
    QTimer* mainTimer;
    bool mainIsProcessing;
};
#endif // MAINWINDOW_H
