#include <QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    if (msg.contains("Opening")) {
        qDebug() << "Intercepted Qt Log Message:" << msg;
    }

    QByteArray localMsg = msg.toLocal8Bit();
    fprintf(stderr, "%s\n", localMsg.constData());
}

void log_callback(void* ptr, int level, const char* fmt, va_list vl) {
    char msg[1024];
    vsnprintf(msg, sizeof(msg), fmt, vl);
    QString message = QString::fromUtf8(msg);
    qDebug() << "Log message:" << message;

    if (message.contains("Opening")) {
        qDebug() << message;
    }
    vfprintf(stderr, fmt, vl);
}

int main(int argc, char *argv[]) {
    qInstallMessageHandler(customMessageHandler);
    avformat_network_init();
    av_log_set_callback(log_callback);
    av_log_set_level(AV_LOG_QUIET);

    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    return app.exec();
}
#include <QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();
    return app.exec();
}
