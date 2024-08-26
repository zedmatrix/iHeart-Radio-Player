void MainWindow::popupImage(const int &id, QString const &stationName) {
    ui->rawText->append(QString("Message Box Id: %1, Name: %2").arg(id).arg(stationName));

    QPixmap pixmap = imageMap[id];
    QMessageBox msgBox;
    msgBox.setWindowTitle(stationName);
    //msgBox.setText("Here is the station image:");

    // Set the pixmap as the icon
    msgBox.setIconPixmap(pixmap);

    // Resize the message box after it's shown
    msgBox.setMinimumSize(300, 300);  // Set minimum size
    msgBox.setMaximumSize(300, 300);  // Set maximum size (optional)

    // Execute and show the message box
    msgBox.exec();

}
