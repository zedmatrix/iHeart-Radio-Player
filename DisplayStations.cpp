#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayoutItem>
#include "mainwindow.h"
#include "ui_mainwindow.h"
void MainWindow::clearLayout(QLayout* layout) {
    if (layout == nullptr) return;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void MainWindow::DisplayStations() {
    QString outputText;
    clearLayout(ui->verticalLayout);

    for (const auto& station : allStations) {
        QString id = station.value(Stations::id);
        QString name = station.value(Stations::name);
        QString desc = station.value(Stations::desc);
        QString logo = station.value(Stations::newlogo);

        outputText += QString("ID: %1 Name: %2 Description: %3\n").arg(id, name, desc);

        QPushButton* stationButton = new QPushButton(id, ui->verticalLayoutWidget);
        stationButton->setObjectName("stationButton" + id);
        stationButton->setFixedWidth(40);
        connect(stationButton, &QPushButton::clicked, this, [id, this]() { StreamTriggered(id, true); });

// Create the QLabel for Stations::name
        QLabel* nameLabel = new QLabel(name, ui->verticalLayoutWidget);
        nameLabel->setObjectName("nameLabel" + id);
        nameLabel->setMaximumWidth(200);
        nameLabel->setMaximumHeight(50);
        nameLabel->setStyleSheet("QLabel { background-color: brown; border-radius: 5px; border: 2px solid darkred;  }");

// Create the QPushButton for Stations::logo/newlogo
        QPushButton* logoButton = new QPushButton(ui->verticalLayoutWidget);
        logoButton->setObjectName("logoButton" + id);
        logoButton->setFixedSize(40,40);

        logoButtonMap[id.toInt()] = logoButton;
        connect(logoButton, &QPushButton::clicked, this, [id, name, this]() { popupImage(id.toInt(), name); });

        QLabel* descLabel = new QLabel(desc, ui->verticalLayoutWidget);
        descLabel->setObjectName("descLabel" + id);
        descLabel->setMaximumWidth(200);
        descLabel->setMaximumHeight(50);
        descLabel->setStyleSheet("QLabel { background-color: green; border-radius: 5px; border: 2px solid lightgreen; }");

        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addWidget(stationButton);
        hLayout->addWidget(nameLabel);
        hLayout->addWidget(logoButton);
        hLayout->addWidget(descLabel);
        ui->verticalLayout->addLayout(hLayout);

    }
    ui->outputText->setPlainText(outputText);
}
