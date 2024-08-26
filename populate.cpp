#include "enum_parser.h"
// Populate Hits and Streams Maps from Get Stream Function
void MainWindow::populateHitsMap (const QJsonObject &obj, QMap<Hits, QString> &hitsMap, QMap<Streams, QString> &streamsMap) {
    QString hitsKey, skey, subStream;
    QJsonValue hitsValue, svalue;
    QJsonObject streamObj;
    for (auto itHits = obj.begin(); itHits != obj.end(); ++itHits) {
        hitsKey = itHits.key();
        hitsValue = itHits.value();
        if (hitsKey == "streams") {
            if (hitsValue.isObject()) {
                streamObj = hitsValue.toObject();
                for (auto s = streamObj.begin(); s != streamObj.end(); ++s) {
                    skey = s.key();
                    svalue = s.value();
                    try {
                        Streams sEnum = stringToEnum(skey);
                        streamsMap[sEnum] = svalue.toString();
                    } catch (const std::invalid_argument &e) {
                        qDebug() << "Error: " << e.what();
                    }
                }
            } else {
                qDebug() << "Invalid Stream Definition";
            }
        } else {
            try {
                Hits hEnum = hitToEnum(hitsKey);
                if (hEnum != Hits::Unknown) hitsMap[hEnum] = hitsValue.toString();
                if (hEnum == Hits::id) hitsMap[hEnum] = QString::number(hitsValue.toInt());
                if (hEnum == Hits::genres) {
                    QJsonArray genresArray = hitsValue.toArray();
                    QString genresString = QJsonDocument(genresArray).toJson(QJsonDocument::Compact);
                    hitsMap[hEnum] = genresString;
                }
                if (hEnum == Hits::feeds) {
                    if (hitsValue.isArray()) {
                        // If hitsValue is an array
                        QJsonArray feedsArray = hitsValue.toArray();
                        QString feedsString = QJsonDocument(feedsArray).toJson(QJsonDocument::Compact);
                        hitsMap[hEnum] = feedsString;
                    } else if (hitsValue.isObject()) {
                        // If hitsValue is an object
                        QJsonObject feedsObject = hitsValue.toObject();
                        QString feedsString = QJsonDocument(feedsObject).toJson(QJsonDocument::Compact);
                        hitsMap[hEnum] = feedsString;
                    }
                }
                if (hEnum == Hits::markets) {
                    if (hitsValue.isArray()) {
                        // If hitsValue is an array
                        QJsonArray marketsArray = hitsValue.toArray();
                        QString marketsString = QJsonDocument(marketsArray).toJson(QJsonDocument::Compact);
                        hitsMap[hEnum] = marketsString;
                    } else if (hitsValue.isObject()) {
                        // If hitsValue is an object
                        QJsonObject marketsObject = hitsValue.toObject();
                        QString marketsString = QJsonDocument(marketsObject).toJson(QJsonDocument::Compact);
                        hitsMap[hEnum] = marketsString;
                    }
                }


            } catch (const std::invalid_argument &e) {
                qDebug() << "Error: " << e.what();
            }
        }
    }
}

// Populate Station Map from Search Function
QMap<Stations, QString> MainWindow::populateStationMap (const QJsonObject &obj, QMap<Stations, QString> &stationMap) {
    QString stationKey;
    QJsonValue stationValue;
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        stationKey = it.key();
        stationValue = it.value();
        try {
            Stations sEnum = searchEnum(stationKey);
            stationMap[sEnum] = stationValue.toString();
            if (sEnum == Stations::id) stationMap[sEnum] = QString::number(stationValue.toInt());
            if (stationKey == "logo" || stationKey == "newlogo") {
                QString urlString = stationValue.toString();
                if (!urlString.isEmpty() && urlString != "null") {
                    QUrl url(urlString);
                    QNetworkRequest request(url);
                    reply = manager->get(request);
                }
            }
        } catch (const std::invalid_argument &e) {
                qDebug() << "Error: " << e.what();
        }
    }
    return stationMap;
}
// Main Populate Function Called from Network reply functions -> 'hits' and 'stations'
void MainWindow::populate(const QJsonObject &jsonObj, const QString &key) {
    QJsonValue newValue = jsonObj.value(key);
    if (newValue.isArray()) {
        QJsonArray newArray = newValue.toArray();
        for (const QJsonValue &value : newArray) {
            if (value.isObject()) {
                QJsonObject newObj = value.toObject();
                //Function to Map 'hits' or 'stations'
                if (key == "hits") {
                    populateHitsMap(newObj, hitsMap, streamsMap);
                } else if (key == "stations") {
                    allStations.append(populateStationMap(newObj, stationMap));
                } else {
                    qDebug() << "Undefined Mapping Key";
                }
            }
        }
    } else {
        qDebug() << "Error: Expected an array for " << key << " key";
    }
}
