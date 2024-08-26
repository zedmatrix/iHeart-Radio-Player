#include "mainwindow.h"
//#include "json_keytypes.cpp"

void MainWindow::jsonParser(const QByteArray &responseData, bool Search, bool Stream) {
    auto keyValue = [](const QJsonObject &newObj) {
        qDebug() << newObj;
        QStringList outList;
        QJsonValue value;
        foreach (const QString &key, newObj.keys()) {
            value = newObj.value(key);
            outList.append(QString("%1 => %2").arg(key).arg(value.toString()));
        }
        return outList.join("\n"); // Join the list into a single QString
    };

    if (!responseData.isEmpty()) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);  // Convert to JSON format
        QJsonObject jsonObj = jsonDoc.object();  // Convert to JSON object

        if (Search) {
            //writeJsonFile(jsonDoc, "search.json");
            populate(jsonObj, "stations");
            qDebug() << "Stations populated. Total count:" << allStations.size();
            DisplayStations();
        }
        if (Stream) {
            //writeJsonFile(jsonDoc, "stream.json");
            populate(jsonObj, "hits");
            DisplayHitStreams();
            qDebug() << "Hits Map populated. Total count:" << hitsMap.size();
            qDebug() << "Stream Map populated. Total count:" << streamsMap.size();

            // Populate Hits -> Streams
            //populateHits(jsonObj);
        }
        // Create a string to hold formatted output
        QJsonValue value;
        foreach (const QString &key, jsonObj.keys()) {
            value = jsonObj.value(key);
            outputText += key + " => " + value.toString() + "\n";  // Concatenate and format the string correctly
        }

        // Convert the JSON object to a QString in a pretty format
        QString jsonString = QString::fromUtf8(QJsonDocument(jsonObj).toJson(QJsonDocument::Indented));

        // Set the formatted JSON string to the rawText QTextEdit
        ui->rawText->setPlainText(jsonString);

        QStringList keyList = jsonObj.keys();

        qsizetype jsonObjectSize = jsonObj.size();

        QString keyString = keyList.join("\n");

        QString outputString = QString("Number of keys: %1\n\nKeys:\n%2").arg(jsonObjectSize).arg(keyString);

        ui->rawText->setPlainText(outputString);

        // returns artists Array(10), stations Array(10), trackBundles Array(10), tracks Array(10)
    }
}
