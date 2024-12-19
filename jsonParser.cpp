#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::jsonParser(const QByteArray &responseData, bool Search, bool Stream) {
    outputText.clear();

    if (!responseData.isEmpty()) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        if (Search) {
            populate(jsonObj, "stations");
            DisplayStations();
        }
        if (Stream) {
            populate(jsonObj, "hits");
            DisplayHitStreams();

        }

        QString jsonString = QString::fromUtf8(QJsonDocument(jsonObj).toJson(QJsonDocument::Indented));
        outputText += QString("jsonString: %1\n").arg(jsonString);

        QStringList keyList = jsonObj.keys();

        qsizetype jsonObjectSize = jsonObj.size();

        QString keyString = keyList.join("\n");

        outputText += QString("Number of keys: %1\nKeys:\n%2").arg(jsonObjectSize).arg(keyString);

        ui->rawText->setText(outputText);
    }
}
