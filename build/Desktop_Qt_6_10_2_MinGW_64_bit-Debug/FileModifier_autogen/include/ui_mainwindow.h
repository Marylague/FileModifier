/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *FileMask;
    QCheckBox *DeleteSource;
    QLineEdit *FilesOutput;
    QPushButton *BrowseButton;
    QComboBox *DubleActions;
    QLineEdit *HexKey;
    QRadioButton *SingleShot;
    QRadioButton *Timer;
    QSpinBox *TimerInterval;
    QPushButton *StartStopButton;
    QProgressBar *progressBar;
    QLabel *TextStatusLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        FileMask = new QLineEdit(centralwidget);
        FileMask->setObjectName("FileMask");
        FileMask->setGeometry(QRect(20, 30, 221, 21));
        DeleteSource = new QCheckBox(centralwidget);
        DeleteSource->setObjectName("DeleteSource");
        DeleteSource->setGeometry(QRect(20, 60, 151, 31));
        FilesOutput = new QLineEdit(centralwidget);
        FilesOutput->setObjectName("FilesOutput");
        FilesOutput->setGeometry(QRect(20, 100, 221, 21));
        BrowseButton = new QPushButton(centralwidget);
        BrowseButton->setObjectName("BrowseButton");
        BrowseButton->setGeometry(QRect(20, 135, 221, 21));
        DubleActions = new QComboBox(centralwidget);
        DubleActions->addItem(QString());
        DubleActions->addItem(QString());
        DubleActions->setObjectName("DubleActions");
        DubleActions->setGeometry(QRect(20, 171, 221, 21));
        HexKey = new QLineEdit(centralwidget);
        HexKey->setObjectName("HexKey");
        HexKey->setGeometry(QRect(20, 210, 221, 20));
        SingleShot = new QRadioButton(centralwidget);
        SingleShot->setObjectName("SingleShot");
        SingleShot->setGeometry(QRect(20, 240, 221, 21));
        Timer = new QRadioButton(centralwidget);
        Timer->setObjectName("Timer");
        Timer->setGeometry(QRect(20, 270, 221, 21));
        TimerInterval = new QSpinBox(centralwidget);
        TimerInterval->setObjectName("TimerInterval");
        TimerInterval->setGeometry(QRect(20, 300, 221, 22));
        StartStopButton = new QPushButton(centralwidget);
        StartStopButton->setObjectName("StartStopButton");
        StartStopButton->setGeometry(QRect(20, 337, 221, 21));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(20, 370, 221, 23));
        progressBar->setValue(24);
        TextStatusLabel = new QLabel(centralwidget);
        TextStatusLabel->setObjectName("TextStatusLabel");
        TextStatusLabel->setGeometry(QRect(20, 410, 221, 21));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        FileMask->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\274\320\260\321\201\320\272\321\203 \321\204\320\260\320\271\320\273\320\276\320\262 (Ex: *.txt)", nullptr));
        DeleteSource->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\321\217\321\202\321\214 \320\270\321\201\321\205\320\276\320\264\320\275\321\213\320\265  \321\204\320\260\320\271\320\273\321\213", nullptr));
        FilesOutput->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\264\320\273\321\217 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\270\321\200\321\203\321\216\321\211\320\270\321\205 \321\204\320\260\320\271\320\273\320\276\320\262", nullptr));
        BrowseButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\320\267\320\276\321\200", nullptr));
        DubleActions->setItemText(0, QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        DubleActions->setItemText(1, QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\263\320\276", nullptr));

        HexKey->setText(QCoreApplication::translate("MainWindow", "HEX key", nullptr));
        SingleShot->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\276\320\262\321\213\320\271 \320\267\320\260\321\203\320\277\321\201\320\272", nullptr));
        Timer->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272 \320\277\320\276 \321\202\320\260\320\271\320\274\320\265\321\200\321\203", nullptr));
        StartStopButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202/\320\241\321\202\320\276\320\277", nullptr));
        TextStatusLabel->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \321\201\321\202\320\260\321\202\321\203\321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
