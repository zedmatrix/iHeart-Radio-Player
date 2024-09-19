#include <QMainWindow>
#include "DisplayStations.cpp"
#include "DisplayHitStreams.cpp"
#include "enum_parser.h"
#include "jsonParser.cpp"
#include "populate.cpp"
#include "network_manager.cpp"
#include "popupImage.cpp"
#include "QMPstatus_error.cpp"
#include "openMedia.cpp"
#include <QWidget>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mousevolume.h"

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
        ui->rawText->append(QString(streamUrl.toString()));
        qDebug() << "*** StartPlay: " << streamUrl;
        metaUrl = streamUrl.toString();
        GetMetaData(metaUrl);
        if (streamUrl.toString().contains("playlist")) {
            qDebug() << "*** NEW Request ***" << streamUrl;
            QNetworkRequest request(streamUrl);
            reply = manager->get(request);
        }
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
    qDebug() << "*** metaData Update:" << metaUrl;
    openMedia(metaUrl);
    if (title != "") { ui->title->setText(title); }
    if (artist != "") { ui->artist->setText(artist); }
    ui->outputText->setText(outputText);
}

void MainWindow::GetMetaData(const QString &metaUrl) {
    qDebug() << "*** Getting MetaData:" << metaUrl;
    openMedia(metaUrl);
    if (title != "") { ui->title->setText(title); }
    if (artist != "") { ui->artist->setText(artist); }
    ui->outputText->setText(outputText);
}

void MainWindow::PlayBack(const QString &streamName, const QUrl &streamUrl, bool fromGui) {
    if (fromGui) {
        ui->rawText->append(QString(streamUrl.toString()));

        if (streamUrl.isValid()) {
            if (streamUrl.toString().contains("hls.m3u8")) {
                //qDebug() << "** HLS Stream URL:" << streamUrl.toString();
                QNetworkRequest request(streamUrl);
                reply = manager->get(request);
            } else if (streamUrl.toString().contains(".pls")) {
                //qDebug() << "** PLS Stream URL:" << streamUrl.toString();
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
        qDebug() << ":Error: " << fromGui << streamUrl;
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
        qDebug() << "No match found.";
    }
}

void MainWindow::SearchTriggered() {
    allStations.clear();
    imageMap.clear();
    query.clear();
    //qDebug() << "Station Map Size: " << stationMap.size();

    ui->rawText->setText("Search has been Triggered");

    searchText = ui->searchTerm->text();

    query.addQueryItem("keywords", searchText);
    QUrl url("http://api2.iheart.com/api/v1/catalog/searchAll");
    url.setQuery(query);
    request.setUrl(url);

        // Debug the URL and query
        //qDebug() << "Full URL:" << url.toString();
        //qDebug() << "Query:" << query.toString();
    QNetworkRequest request(url);
    reply = manager->get(request);
}

void MainWindow::StreamTriggered(const QString &id, bool fromGui) {
    qDebug() << "Stream Triggered:" << id;
    hitsMap.clear();
    streamsMap.clear();

    QUrl url("https://api.iheart.com/api/v2/content/liveStations/");

    if (fromGui) {
        ui->rawText->setText("Station ID Clicked:" + id);
        url.setPath(url.path() + id);
        qDebug() << "Full URL:" << url.toString();
        QNetworkRequest request(url);
        reply = manager->get(request);
    } else {
        QString y = ui->searchTerm->text();
        QRegularExpression regex("^\\d{4}$");

        if (regex.match(y).hasMatch()) {
            url.setPath(url.path() + y);
            qDebug() << "Full URL:" << url.toString();
            QNetworkRequest request(url);
            reply = manager->get(request);
        } else {
            qDebug() << "Invalid 4-digit value for Stream Get.";
        }
    }
}
