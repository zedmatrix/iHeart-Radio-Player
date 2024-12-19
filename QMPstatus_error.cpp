#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::MediaPlayerError(QMediaPlayer::Error error)
{
    QString errorMessage;
    switch (error) {
        case QMediaPlayer::NoError:
            errorMessage = "No error.";
            break;
        case QMediaPlayer::ResourceError:
            errorMessage = "Resource error: Unable to access the media resource.";
            break;
        case QMediaPlayer::FormatError:
            errorMessage = "Format error: The media format is not supported.";
            break;
        case QMediaPlayer::NetworkError:
            errorMessage = "Network error: A network error occurred.";
            break;
        case QMediaPlayer::AccessDeniedError:
            errorMessage = "Access denied: Insufficient permissions to access the media.";
            break;
        default:
            errorMessage = "Unknown error.";
            break;
    }

    statusBar()->showMessage(errorMessage);
}

void MainWindow::MediaStatus(QMediaPlayer::MediaStatus status)
{
    QString statusMessage;
    switch (status) {
        case QMediaPlayer::NoMedia:
            statusMessage = "No media loaded.";
            break;
        case QMediaPlayer::LoadingMedia:
            statusMessage = "Loading media.";
            break;
        case QMediaPlayer::LoadedMedia:
            statusMessage = "Media loaded.";
            break;
        case QMediaPlayer::StalledMedia:
            statusMessage = "Media playback stalled.";
            break;
        case QMediaPlayer::BufferingMedia:
            statusMessage = "Buffering media.";
            break;
        case QMediaPlayer::BufferedMedia:
            statusMessage = "Media buffered.";
            break;
        case QMediaPlayer::EndOfMedia:
            statusMessage = "End of media.";
            break;
        case QMediaPlayer::InvalidMedia:
            statusMessage = "Invalid media.";
            break;
    }
    statusBar()->showMessage(statusMessage);
}
