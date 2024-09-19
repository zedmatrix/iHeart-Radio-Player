#include "mainwindow.h"

void MainWindow::jsonParser(const QByteArray &responseData, bool Search, bool Stream) {
    // auto keyValue = [](const QJsonObject &newObj) {
    //     qDebug() << newObj;
    //     QStringList outList;
    //     QJsonValue value;
    //     foreach (const QString &key, newObj.keys()) {
    //         value = newObj.value(key);
    //         outList.append(QString("%1 => %2").arg(key).arg(value.toString()));
    //     }
    //     return outList.join("\n");
    // };

    if (!responseData.isEmpty()) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        if (Search) {
            populate(jsonObj, "stations");
            qDebug() << "Stations populated. Total count:" << allStations.size();
            DisplayStations();
        }
        if (Stream) {
            populate(jsonObj, "hits");
            DisplayHitStreams();
            qDebug() << "Hits Map populated. Total count:" << hitsMap.size();
            qDebug() << "Stream Map populated. Total count:" << streamsMap.size();

        }
        // // Create a string to hold formatted output
        // QJsonValue value;
        // foreach (const QString &key, jsonObj.keys()) {
        //     value = jsonObj.value(key);
        //     outputText += key + " => " + value.toString() + "\n";
        // }

        QString jsonString = QString::fromUtf8(QJsonDocument(jsonObj).toJson(QJsonDocument::Indented));
        ui->rawText->setPlainText(jsonString);

        QStringList keyList = jsonObj.keys();

        qsizetype jsonObjectSize = jsonObj.size();

        QString keyString = keyList.join("\n");

        QString outputString = QString("Number of keys: %1\n\nKeys:\n%2").arg(jsonObjectSize).arg(keyString);

        ui->rawText->setPlainText(outputString);
    }
}
