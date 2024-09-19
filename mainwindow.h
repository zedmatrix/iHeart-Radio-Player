#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGlobal>
#include <QApplication>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QNetworkAccessManager>
#include <QRegularExpression>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStatusBar>
#include <QMenuBar>
#include <QTextEdit>
#include <QLineEdit>
#include <QAction>
#include <QLabel>
#include <QDebug>
#include <QWindow>
#include <QTimer>
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>
#include <QTextDocument>
#include "enum_parser.h"

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/avutil.h>
    #include <libavutil/log.h>
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QAudioOutput *audioOutput;
    QMediaPlayer *player;
    QNetworkAccessManager *manager;
    void jsonParser(const QByteArray &responseData, bool Search, bool Stream);

    // List to hold the station mappings
    QMap<Hits, QString> hitsMap;
    QMap<Streams, QString> streamsMap;
    QMap<Stations, QString> stationMap;
    QList<QMap<Stations, QString>> allStations;
    QMap<int, QPixmap> imageMap;
    QMap<int, QPushButton*> logoButtonMap;
    QString metaUrl, outputText, searchText, errorText, title, artist;
    QUrl streamUrl;
    const char* FFurl;
    bool Search, Stream;

private slots:

    void openMedia(const QString &metaUrl);
    void SearchTriggered();
    void StreamTriggered(const QString &id, bool fromGui);
    void PlayBack(const QString &streamName, const QUrl &streamUrl, bool fromGui);
    void onFinished(QNetworkReply* reply);
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError code);
    void slotSslErrors(const QList<QSslError> &errors);
    void MediaPlayerError(QMediaPlayer::Error error);
    void MediaStatus(QMediaPlayer::MediaStatus status);
    void parseM3U(const QString &m3uContent);

private:
    Ui::MainWindow *ui;
    QUrl url;
    QUrlQuery query;
    QNetworkRequest request;
    QNetworkReply *reply;
    QTimer *metadataTimer;
    QString plsData, playlistData, hlsData;
    QStringList lines;
    AVFormatContext* Format_Context = nullptr;
    AVDictionaryEntry* tag = nullptr;
    AVStream* stream = nullptr;
    AVDictionary* metadata = nullptr;
    AVDictionary* streamMetadata = nullptr;
    QMap<Stations, QString> populateStationMap(const QJsonObject &obj, QMap<Stations, QString> &stationMap);
    void populateHitsMap (const QJsonObject &obj, QMap<Hits, QString> &hitsMap, QMap<Streams, QString> &streamsMap);
    void populate(const QJsonObject &jsonObj, const QString &key);
    void DisplayStations();
    void DisplayHitStreams();
    void clearLayout(QLayout* layout);
    void popupImage(const int &id, QString const &stationName);
    std::function<void(const QUrl&)> StartPlay;
    void GetMetaData(const QString &metaUrl);
    void updateMetadata();
};

#endif // MAINWINDOW_H
