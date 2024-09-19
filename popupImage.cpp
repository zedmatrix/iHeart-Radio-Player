void MainWindow::popupImage(const int &id, QString const &stationName) {
    ui->rawText->append(QString("Message Box Id: %1, Name: %2").arg(id).arg(stationName));

    QPixmap pixmap = imageMap[id];
    QMessageBox msgBox;
    msgBox.setWindowTitle(stationName);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.setIconPixmap(pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    msgBox.setMinimumSize(100, 100);
    msgBox.setMaximumSize(300, 300);
    // Execute and show the message box
    msgBox.exec();

}
