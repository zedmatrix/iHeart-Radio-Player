#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , player(new QMediaPlayer(this))
    , audioOutput(new QAudioOutput(this))
    , manager(new QNetworkAccessManager(this))

{

    ui->setupUi(this);
    this->setWindowTitle("iHeart Radio App");
    QIcon windowIcon(":/resources/iHeartRadio_Icon.png");
    this->setWindowIcon(windowIcon);

    audioOutput->setVolume(0.4);
    player->setAudioOutput(audioOutput);

    searchText = ui->searchTerm->text();
    qDebug() << searchText;

    MouseVolume *volumeControl = new MouseVolume(ui, this, this);
    volumeControl->InitializeVolumeBar(ui->volumeBar);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::MediaStatus);
    connect(player, &QMediaPlayer::errorOccurred, this, &MainWindow::MediaPlayerError);

    connect(ui->searchTerm, &QLineEdit::returnPressed, this, &MainWindow::SearchTriggered);
    connect(ui->Quit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->GetSearch, &QPushButton::clicked, this, &MainWindow::SearchTriggered);
    connect(ui->updateMetaData, &QPushButton::clicked, this, &MainWindow::updateMetadata);
    connect(ui->GetStreams, &QPushButton::clicked, this, [this]() { StreamTriggered(searchText, false); });
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onFinished);

    //Lambda to stop and player from streamUrl
    StartPlay = [this](const QUrl &streamUrl) {
        player->stop();
        player->setSource(streamUrl);
        player->play();
        metaUrl = streamUrl.toString();
        rawText = QString("*** StartPlay: %1\n").arg(metaUrl);

        GetMetaData(metaUrl);
        if (streamUrl.toString().contains("playlist")) {
            rawText = QString("*** NEW Request: %1\n").arg(metaUrl);
            QNetworkRequest request(streamUrl);
            reply = manager->get(request);
        }
        ui->rawText->append(rawText);
    };

    // Setup url for request
    QUrl url("http://api2.iheart.com/api/v1/catalog/searchAll");
    query.addQueryItem("keywords", searchText);
    url.setQuery(query);
    QNetworkRequest request(url);

    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QIODevice::readyRead, this, &MainWindow::slotReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &MainWindow::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &MainWindow::slotSslErrors);

}

MainWindow::~MainWindow()
{
    delete ui;
    if (Format_Context) {
        avformat_close_input(&Format_Context);
    }
    avformat_network_deinit();
}

void MainWindow::updateMetadata() {
    openMedia(metaUrl);
    if (title != "") { ui->title->setText(title); }
    if (artist != "") { ui->artist->setText(artist); }
    ui->outputText->setText(outputText);
}

void MainWindow::GetMetaData(const QString &metaUrl) {
    openMedia(metaUrl);
    if (title != "") { ui->title->setText(title); }
    if (artist != "") { ui->artist->setText(artist); }
    ui->outputText->setText(outputText);
}

void MainWindow::PlayBack(const QString &streamName, const QUrl &streamUrl, bool fromGui) {
    if (fromGui) {
        ui->rawText->append(QString(streamUrl.toString()));

        if (streamUrl.isValid()) {
            // HLS Stream decode
            if (streamUrl.toString().contains("hls.m3u8")) {

                QNetworkRequest request(streamUrl);
                reply = manager->get(request);

            // PLS Stream decode
            } else if (streamUrl.toString().contains(".pls")) {

                QNetworkRequest request(streamUrl);
                reply = manager->get(request);

            }
            audioOutput->setVolume(0.5);
            StartPlay(streamUrl);
            statusBar()->showMessage("Playing: " + streamName);
        } else {
            statusBar()->showMessage("Error: Invalid URL for " + streamName);
        }

    } else {
        rawText = QString(":ERROR: %1\n").arg(streamUrl.toString());
        ui->rawText->append(rawText);
    }

}

void MainWindow::parseM3U(const QString &m3uContent) {
    QRegularExpression regex(R"#(title="([^"]+)",artist="([^"]+)")#");
    QRegularExpressionMatch match = regex.match(m3uContent);

    if (match.hasMatch()) {
        QString title = match.captured(1);
        QString artist = match.captured(2);

        ui->rawText->append(QString("Title: %1\nArtist: %2").arg(title).arg(artist));
        ui->title->setText(title);
        ui->artist->setText(artist);
    } else {
        ui->rawText->append("No match found.");
    }
}

void MainWindow::SearchTriggered() {
    allStations.clear();
    imageMap.clear();
    query.clear();

    ui->rawText->setText("Search has been Triggered");

    searchText = ui->searchTerm->text();

    query.addQueryItem("keywords", searchText);
    QUrl url("http://api2.iheart.com/api/v1/catalog/searchAll");
    url.setQuery(query);
    request.setUrl(url);

    QNetworkRequest request(url);
    reply = manager->get(request);
}

void MainWindow::StreamTriggered(const QString &id, bool fromGui) {
    outputText = QString("Stream Triggered: %1").arg(id);
    //qDebug() << "Stream Triggered:" << id;
    hitsMap.clear();
    streamsMap.clear();

    QUrl url("https://api.iheart.com/api/v2/content/liveStations/");

    if (fromGui) {
        ui->rawText->setText("Station ID Clicked:" + id);
        url.setPath(url.path() + id);
        outputText += QString("Full URL: %1\n").arg(url.toString());
        //qDebug() << "Full URL:" << url.toString();
        QNetworkRequest request(url);
        reply = manager->get(request);
    } else {
        QString y = ui->searchTerm->text();
        QRegularExpression regex("^\\d{4}$");

        if (regex.match(y).hasMatch()) {
            url.setPath(url.path() + y);
            outputText += QString("Full URL: %1\n").arg(url.toString());
            //qDebug() << "Full URL:" << url.toString();
            QNetworkRequest request(url);
            reply = manager->get(request);
        } else {
            outputText += QString("Error: Invalid 4 Digit Stream Id.%1\n").arg(id);
            //qDebug() << "Invalid 4-digit value for Stream Get.";
        }
    }

    //Update rawText Left Display
    ui->rawText->setText(outputText);
}
