#ifndef MOUSEVOLUME_H
#define MOUSEVOLUME_H

#include <QWidget>
#include <QScrollBar>
#include <QWheelEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class MainWindow; //Forward declare

class MouseVolume : public QWidget
{
    Q_OBJECT

public:
    explicit MouseVolume(Ui::MainWindow *ui, MainWindow *mainWindow, QWidget *parent = nullptr);
    void InitializeVolumeBar(QScrollBar *volumeBar);
    void updateVolume();

protected:
    void wheelEvent(QWheelEvent *event) override;

private:
    MainWindow *mainWindow;  // Pointer to MainWindow
    Ui::MainWindow *ui;
    QScrollBar *volumeBar;
    double trackVolume;

};

#endif // MOUSEVOLUME_H
