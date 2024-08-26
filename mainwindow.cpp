#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enum_parser.h"
#include "jsonParser.cpp"
#include "populate.cpp"
#include "network_manager.cpp"
#include "DisplayStations.cpp"
#include "DisplayHitStreams.cpp"
#include "popupImage.cpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    // Setup the Ui:: MainWindow
    ui->setupUi(this);

    this->setWindowTitle("iHeart Radio App");
    QIcon windowIcon(":/resources/iHeartRadio_Icon.png");
    this->setWindowIcon(windowIcon);

    // Initialize MediaPlayer
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    audioOutput->setVolume(0.4); // Volume is from 0.0 to 1.0
    player->setAudioOutput(audioOutput);

    searchText = ui->searchTerm->text();
    qDebug() << searchText;
    // connect the buttons to routines
    connect(ui->Quit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->GetSearch, &QPushButton::clicked, this, &MainWindow::SearchTriggered);
    connect(ui->GetStreams, &QPushButton::clicked, this, [this]() { StreamTriggered(searchText, false); });

    manager = new QNetworkAccessManager(this); // Instantiate the pointer
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onFinished);

    // Setup url for reuest
    QUrl url("http://api2.iheart.com/api/v1/catalog/searchAll");

    // Add query parameters
    query.addQueryItem("keywords", searchText);

    // Set the query on the URL
    url.setQuery(query);

    // Create the request with the URL
    QNetworkRequest request(url);

    // Set the raw header (e.g., User-Agent)
    request.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    // Send the request using QNetworkAccessManager
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QIODevice::readyRead, this, &MainWindow::slotReadyRead);
    connect(reply, &QNetworkReply::errorOccurred, this, &MainWindow::slotError);
    connect(reply, &QNetworkReply::sslErrors, this, &MainWindow::slotSslErrors);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::PlayBack(const QString &streamName, const QUrl &streamUrl, bool fromGui) {
    if (fromGui) {
        ui->rawText->append(QString(streamUrl.toString()));

        if (streamUrl.isValid()) {
            player->setSource(streamUrl);  // Set the media stream URL
            audioOutput->setVolume(0.5);
            player->play();  // Play the stream
            statusBar()->showMessage("Playing: " + streamName);  // Update the status bar
    } else {
        // Handle invalid URL or error
        statusBar()->showMessage("Error: Invalid URL for " + streamName);
        //qDebug() << "Failed to set Downtown stream URL.";
    }

    } else {
        qDebug() << ":Error: " << fromGui << streamUrl;
    }


}

void MainWindow::SearchTriggered() {
    // clear previous allStations
    allStations.clear();
    imageMap.clear();
    qDebug() << "Station Map Size: " << stationMap.size();
    // Code to execute when the action is triggered
    ui->rawText->setText("Search has been Triggered");
    QString x = ui->searchTerm->text();
    if (x != searchText) {
        searchText = ui->searchTerm->text();
        query.clear();

        // setup for new query item
        query.addQueryItem("keywords", searchText);
        QUrl url("http://api2.iheart.com/api/v1/catalog/searchAll");
        url.setQuery(query);
        request.setUrl(url);

        // Debug the URL and query
        qDebug() << "Full URL:" << url.toString();
        qDebug() << "Query:" << query.toString();
        QNetworkRequest request(url);
        reply = manager->get(request);
    } else {
        qDebug() << "Error: Search Text is not different";
    }
}

void MainWindow::StreamTriggered(const QString &id, bool fromGui) {
    // Code to execute when the action is triggered
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
        // Check if the input matches the 4-digit pattern
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
