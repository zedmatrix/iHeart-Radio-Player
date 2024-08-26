#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QMediaPlayer>
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
#include <QIcon>
#include <QPixmap>
#include <QMessageBox>

#include "enum_parser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QNetworkAccessManager *manager; // Declare as a pointer
    void jsonParser(const QByteArray &responseData, bool Search, bool Stream);

    // List to hold the station mappings
    QMap<Hits, QString> hitsMap;
    QMap<Streams, QString> streamsMap;
    QMap<Stations, QString> stationMap;
    QList<QMap<Stations, QString>> allStations;  // Define the variable
    QMap<int, QPixmap> imageMap; // Maps station IDs to their corresponding QPixmaps
    QMap<int, QPushButton*> logoButtonMap; // Declare this map as extern to access it globally
    QString outputText, searchText, errorText;
    bool Search, Stream;

private slots:
    //Private functions
    void SearchTriggered();
    void StreamTriggered(const QString &id, bool fromGui);
    void PlayBack(const QString &streamName, const QUrl &streamUrl, bool fromGui);
    void onFinished(QNetworkReply* reply);
    void slotReadyRead();
    void slotError(QNetworkReply::NetworkError code);
    void slotSslErrors(const QList<QSslError> &errors);
    QMap<Stations, QString> populateStationMap(const QJsonObject &obj, QMap<Stations, QString> &stationMap);
    void populateHitsMap (const QJsonObject &obj, QMap<Hits, QString> &hitsMap, QMap<Streams, QString> &streamsMap);
    void populate(const QJsonObject &jsonObj, const QString &key);
    void DisplayStations();
    void DisplayHitStreams();
    void clearLayout(QLayout* layout);
    void popupImage(const int &id, QString const &stationName);

private:
    Ui::MainWindow *ui;
    QUrl url;
    QUrlQuery query;
    QNetworkRequest request;
    QNetworkReply *reply;
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

};

#endif // MAINWINDOW_H
