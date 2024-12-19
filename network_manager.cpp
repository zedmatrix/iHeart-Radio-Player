#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::onFinished(QNetworkReply* reply)
{
    rawText.clear();
    // Handle onFinished signal here
    if (reply->error() == QNetworkReply::NoError) {

        QUrl requestUrl = reply->request().url();
        rawText += QString("Request URL: %1").arg(requestUrl.toString());

        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if (requestUrl.toString().contains("playlist")) {
            playlistData = reply->readAll();
            parseM3U(playlistData);
        }

        if (requestUrl.path().contains(".pls")) {
            plsData = reply->readAll();
            lines = plsData.split('\n');
            for (const QString& line : lines) {
                if (line.trimmed().startsWith("File1=")) {
                    streamUrl = line.split('=').last().trimmed();
                    break;
                }
            }
            StartPlay(streamUrl);
            rawText += QString("*** PLS Stream *** %1\n").arg(streamUrl.toString());
        }

        if (requestUrl.toString().contains("hls.m3u8")) {
            hlsData = reply->readAll();
            lines = hlsData.split('\n');
            for (const QString& line : lines) {
                if (!line.trimmed().startsWith("#")) {
                    streamUrl = line.trimmed();
                    break;
                }
            }
            StartPlay(streamUrl);
            rawText += QString("*** HLS Stream *** %1\n").arg(streamUrl.toString());
        }

        if (requestUrl.path().contains("/searchAll")) {
            QByteArray responseData = reply->readAll();
            jsonParser(responseData, true, false);
        } else if (requestUrl.path().contains("/liveStations")) {

            if (statusCode.isValid() && statusCode.toInt() == 200) {
                rawText += QString("Request successful, status code: %1\n").arg(statusCode.toInt());
                QByteArray responseData = reply->readAll();
                Stream = true;
                Search = false;
                jsonParser(responseData, false, true);
            } else {
                rawText += QString("Request failed, status code: %1\n").arg(statusCode.toInt());
            }
        } else if (requestUrl.path().contains("assets")) {

// Search through allStations for the matching newlogo
            if (statusCode.isValid() && statusCode.toInt() == 200) {
                QByteArray imageData = reply->readAll();
                QImage image;
                if (image.loadFromData(imageData)) {

                    for (const auto &stationMap : allStations) {
                        if (stationMap.value(Stations::newlogo) == requestUrl.toString()) {
                            QString Idstring = stationMap.value(Stations::id);
                            int stationId = Idstring.toInt();
                            QPixmap pixmap = QPixmap::fromImage(image);
                            imageMap[stationId] = pixmap;

                            if (logoButtonMap.contains(stationId)) {
                                QPushButton* logoButton = logoButtonMap[stationId];
                                QIcon buttonIcon(pixmap.scaled(38, 38, Qt::KeepAspectRatio));
                                logoButton->setIcon(buttonIcon);
                                logoButton->setIconSize(QSize(38,38));
                        }
                            rawText += QString("Image loaded and stored for station ID: %1\n").arg(Idstring);
                        }
                    }
                    int numImages = imageMap.size();
                    rawText += QString("Number of pixmaps stored: %1\n").arg(numImages);
                }
            } else {
                rawText += QString("Image Request Failed Status Code: %1\n").arg(statusCode.toInt());
            }
        } else {
            rawText += QString("Received response for an unexpected path: %1\n").arg(requestUrl.toString());
        }
    } else {
        QString errorText = reply->errorString();
        rawText += QString("Error Text From Network Manager: %1\n").arg(errorText);
    }
    ui->rawText->setPlainText(rawText);
    reply->deleteLater();
}

void MainWindow::slotReadyRead()
{
    ui->rawText->insertPlainText(":slot Ready Read:");
}

void MainWindow::slotError(QNetworkReply::NetworkError code)
{
    rawText = QString(":Network Error: %1 (%2)\n").arg(code).arg(reply->errorString());
    ui->rawText->insertPlainText(rawText);

}

void MainWindow::slotSslErrors(const QList<QSslError> &errors)
{
    QStringList errorMessages;
    errorMessages.append(":SSL Error List:");

    for (const QSslError &error : errors) {
        errorMessages.append(error.errorString());
    }

    rawText = errorMessages.join("\n") + "\n";
    ui->rawText->insertPlainText(rawText);
}
