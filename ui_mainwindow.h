#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 800);
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
        rawText->setGeometry(QRect(840, 340, 300, 260));
        outputText = new QTextEdit(centralwidget);
        outputText->setObjectName("outputText");
        outputText->setGeometry(QRect(840, 50, 300, 260));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 40, 800, 700));
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE
#endif  //UI_MAINWINDOW_H
