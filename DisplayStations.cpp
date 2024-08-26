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
            widget->deleteLater();  // Schedule the widget for deletion
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);  // Recursively clear nested layouts
        }
        delete item;  // Delete the layout item itself
    }
}

void MainWindow::DisplayStations() {
    QString outputText;

    // Clear any existing widgets in the vertical layout
    clearLayout(ui->verticalLayout);

    // Iterate through each station in allstations
    for (const auto& station : allStations) {
        // Extract the ID, name, and description from the QMap
        QString id = station.value(Stations::id);        // id is an enum value in Stations
        QString name = station.value(Stations::name);    // name is an enum value in Stations
        QString desc = station.value(Stations::desc);    // desc is an enum value in Stations
        QString logo = station.value(Stations::newlogo);    // desc is an enum value in Stations
        // Append the extracted information to outputText
        outputText += QString("ID: %1 Name: %2 Description: %3\n").arg(id, name, desc);

        // Create the QPushButton for Stations::id
        QPushButton* stationButton = new QPushButton(id, ui->verticalLayoutWidget);
        stationButton->setObjectName("stationButton" + id);
        stationButton->setFixedWidth(50);
        connect(stationButton, &QPushButton::clicked, this, [id, this]() { StreamTriggered(id, true); });

        // Create the QLabel for Stations::name
        QLabel* nameLabel = new QLabel(name, ui->verticalLayoutWidget);
        nameLabel->setObjectName("nameLabel" + id);
        nameLabel->setFixedWidth(150);
        nameLabel->setStyleSheet("QLabel { background-color: brown; border-radius: 5px; border: 2px solid darkred;  }");


        // Create the QPushButton for Stations::logo/newlogo
        QPushButton* logoButton = new QPushButton(ui->verticalLayoutWidget);
        logoButton->setObjectName("logoButton" + id);
        logoButton->setFixedSize(50,50);
        //logoLabel->setStyleSheet("QLabel { border-radius: 4px; border: 2px solid green; }");
        // Store the QLabel in the map with the station ID as the key
        logoButtonMap[id.toInt()] = logoButton;
        connect(logoButton, &QPushButton::clicked, this, [id, name, this]() { popupImage(id.toInt(), name); });

        // Create the QLabel for Stations::desc
        QLabel* descLabel = new QLabel(desc, ui->verticalLayoutWidget);
        descLabel->setObjectName("descLabel" + id);
        descLabel->setStyleSheet("QLabel { background-color: green; border-radius: 5px; border: 2px solid lightgreen; }");

        // Add these widgets to a horizontal layout
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addWidget(stationButton);
        hLayout->addWidget(nameLabel);
        hLayout->addWidget(logoButton);
        hLayout->addWidget(descLabel);

        // Add the horizontal layout to the existing vertical layout
        ui->verticalLayout->addLayout(hLayout);

    }

    // Set the text to the outputText QTextEdit or QLabel in the UI
    ui->outputText->setPlainText(outputText);

}
