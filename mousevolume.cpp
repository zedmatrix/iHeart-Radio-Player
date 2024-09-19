#include "mousevolume.h"
#include "mainwindow.h"

/*
    >> Add to mainwindow.cpp
    >> CMakeLists.txt >> mousevolume.{h,cpp}

    MouseVolume *volumeControl = new MouseVolume(ui, this, this);
    volumeControl->InitializeVolumeBar(ui->volumeBar);
*/

MouseVolume::MouseVolume(Ui::MainWindow *ui, MainWindow *mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(ui)
    , volumeBar(ui->volumeBar)
    , mainWindow(mainWindow)
    , trackVolume(0.4)
{

}

void MouseVolume::InitializeVolumeBar(QScrollBar *volumeBar) {
    volumeBar->setRange(0, 100);
    volumeBar->setValue(static_cast<int>(trackVolume * 100)); // Convert 0.0–1.0 to 0–100
    connect(volumeBar, &QScrollBar::valueChanged, this, &MouseVolume::updateVolume);

}

void MouseVolume::updateVolume() {
    int value = volumeBar->value();
    trackVolume = value / 100.0;
    mainWindow->audioOutput->setVolume(trackVolume);
}

void MouseVolume::wheelEvent(QWheelEvent *event)
{
    int numSteps = event->angleDelta().y() / 120;
    if (numSteps > 0) {
        volumeBar->setValue(volumeBar->value() - 1);
    } else {
        volumeBar->setValue(volumeBar->value() + 1);
    }
    event->accept();
    updateVolume();
}
