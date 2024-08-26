void MainWindow::onFinished(QNetworkReply* reply)
{
    // Handle onFinished signal here
    if (reply->error() == QNetworkReply::NoError) {
        ui->rawText->setText("No Error");
        QUrl requestUrl = reply->request().url();
        // Get the status code from the reply
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

        if (requestUrl.path().contains("/searchAll")) {
            QByteArray responseData = reply->readAll();     //get reply from server
            jsonParser(responseData, true, false);          // Set Search = true, Stream = false
        } else if (requestUrl.path().contains("/liveStations")) {
            // Check if the status code is 200
            if (statusCode.isValid() && statusCode.toInt() == 200) {
                qDebug() << "Request successful, status code:" << statusCode.toInt();
                QByteArray responseData = reply->readAll(); // Optionally read the data
                Stream = true;
                Search = false;
                jsonParser(responseData, false, true);      // Set Search = false, Stream = true
            } else {
                qDebug() << "Request failed, status code:" << statusCode.toInt();
            }
        } else if (requestUrl.path().contains("assets")) {
            //Images get from url
            if (statusCode.isValid() && statusCode.toInt() == 200) {
                QByteArray imageData = reply->readAll();
                QImage image;
                if (image.loadFromData(imageData)) {
                    // Search through allStations for the matching newlogo
                    for (const auto &stationMap : allStations) {
                        if (stationMap.value(Stations::newlogo) == requestUrl.toString()) {
                            int stationId = stationMap.value(Stations::id).toInt();
                            QPixmap pixmap = QPixmap::fromImage(image);
                            imageMap[stationId] = pixmap;

                            if (logoButtonMap.contains(stationId)) {
                                QPushButton* logoButton = logoButtonMap[stationId];
                                QIcon buttonIcon(pixmap.scaled(48, 48, Qt::KeepAspectRatio));
                                logoButton->setIcon(buttonIcon);
                                logoButton->setIconSize(QSize(48,48));
                                //logoLabel->setPixmap(pixmap.scaled(80, 60, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
                        }
                            qDebug() << "Image loaded and stored for station ID:" << stationId;
                        }
                    }
                    int numImages = imageMap.size();
                    qDebug() << "Number of pixmaps stored:" << numImages;

                }
            } else {
                qDebug() << "Image Request Failed Status Code:" << statusCode.toInt();
            }
        } else {
            // Handle unexpected or unrecognized paths
            qDebug() << "Received response for an unexpected path:" << requestUrl.path();
        }
    } else {
        errorText = reply->errorString();
        ui->rawText->setText("Error " + errorText);
    }
    reply->deleteLater();
}

void MainWindow::slotReadyRead()
{
    // Handle readyRead signal here
    qDebug() << ":slot Ready Read:";
}

void MainWindow::slotError(QNetworkReply::NetworkError code)
{
    // Handle errorOccurred signal here
    qDebug() << ":Network Error code:" << code;
}

void MainWindow::slotSslErrors(const QList<QSslError> &errors)
{
    // Handle sslErrors signal here
    qDebug() << ":ssl Error List:";
    for (const QSslError &error : errors) {
        qDebug() << error.errorString();
    }
}
