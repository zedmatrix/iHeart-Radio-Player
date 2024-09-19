/********************************************************************************
** Form generated from reading UI file 'mainwindowQneENk.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOWQNEENK_H
#define MAINWINDOWQNEENK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *searchTerm;
    QLabel *search;
    QTextEdit *rawText;
    QTextEdit *outputText;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *GetStreams;
    QPushButton *GetSearch;
    QPushButton *Quit;
    QLabel *title;
    QLabel *artist;
    QPushButton *updateMetaData;
    QScrollBar *volumeBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        searchTerm = new QLineEdit(centralwidget);
        searchTerm->setObjectName("searchTerm");
        searchTerm->setGeometry(QRect(100, 10, 140, 22));
        search = new QLabel(centralwidget);
        search->setObjectName("search");
        search->setGeometry(QRect(10, 10, 80, 22));
        rawText = new QTextEdit(centralwidget);
        rawText->setObjectName("rawText");
        rawText->setGeometry(QRect(10, 440, 361, 130));
        outputText = new QTextEdit(centralwidget);
        outputText->setObjectName("outputText");
        outputText->setGeometry(QRect(419, 440, 361, 130));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 49, 781, 351));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        GetStreams = new QPushButton(centralwidget);
        GetStreams->setObjectName("GetStreams");
        GetStreams->setGeometry(QRect(360, 10, 90, 22));
        GetSearch = new QPushButton(centralwidget);
        GetSearch->setObjectName("GetSearch");
        GetSearch->setGeometry(QRect(260, 10, 90, 22));
        Quit = new QPushButton(centralwidget);
        Quit->setObjectName("Quit");
        Quit->setGeometry(QRect(460, 10, 80, 22));
        title = new QLabel(centralwidget);
        title->setObjectName("title");
        title->setGeometry(QRect(19, 410, 301, 20));
        artist = new QLabel(centralwidget);
        artist->setObjectName("artist");
        artist->setGeometry(QRect(419, 410, 281, 20));
        updateMetaData = new QPushButton(centralwidget);
        updateMetaData->setObjectName("updateMetaData");
        updateMetaData->setGeometry(QRect(550, 10, 80, 22));
        volumeBar = new QScrollBar(centralwidget);
        volumeBar->setObjectName("volumeBar");
        volumeBar->setGeometry(QRect(380, 440, 31, 121));
        volumeBar->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        volumeBar->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        volumeBar->setMaximum(100);
        volumeBar->setSliderPosition(30);
        volumeBar->setOrientation(Qt::Orientation::Vertical);
        volumeBar->setInvertedAppearance(true);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        searchTerm->setText(QCoreApplication::translate("MainWindow", "classic", nullptr));
        search->setText(QCoreApplication::translate("MainWindow", "Search Term:", nullptr));
        GetStreams->setText(QCoreApplication::translate("MainWindow", "Get Streams", nullptr));
        GetSearch->setText(QCoreApplication::translate("MainWindow", "Get Search", nullptr));
        Quit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        title->setText(QCoreApplication::translate("MainWindow", "title", nullptr));
        artist->setText(QCoreApplication::translate("MainWindow", "artist", nullptr));
        updateMetaData->setText(QCoreApplication::translate("MainWindow", "Meta Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOWQNEENK_H
