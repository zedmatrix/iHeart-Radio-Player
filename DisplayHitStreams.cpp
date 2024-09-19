void MainWindow::DisplayHitStreams() {
    auto streamToString = [](Streams stream) -> QString {
        switch (stream) {
            case Streams::pls:
                return "PLS ";
            case Streams::secure_pls:
                return "Secure PLS ";
            case Streams::hls:
                return "HLS ";
            case Streams::secure_hls:
                return "Secure HLS ";
            case Streams::shoutcast:
                return "Shoutcast ";
            case Streams::secure_shoutcast:
                return "Secure Shoutcast ";
            default:
                return "Unknown Stream ";
        }
    };

    QString outputText;
    clearLayout(ui->verticalLayout);

    QString id = hitsMap.value(Hits::id);
    QString name = hitsMap.value(Hits::name);
    QString desc = hitsMap.value(Hits::desc);

    outputText += QString("ID: %1 Name: %2 Description: %3\n").arg(id, name, desc);

    QHBoxLayout* hLayout = new QHBoxLayout();

    // Create the label for the logo
    QLabel* logoLabel = new QLabel();
    logoLabel->setPixmap(imageMap[id.toInt()].scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    QVBoxLayout* vLayout = new QVBoxLayout();

    QLabel* idLabel = new QLabel(id, ui->verticalLayoutWidget);
    idLabel->setObjectName("idLabel" + id);
    idLabel->setFixedHeight(30);
    idLabel->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

    QLabel* nameLabel = new QLabel(name, ui->verticalLayoutWidget);
    nameLabel->setObjectName("nameLabel" + id);
    nameLabel->setFixedHeight(30);
    nameLabel->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

    QLabel* descLabel = new QLabel(desc, ui->verticalLayoutWidget);
    descLabel->setObjectName("descLabel" + id);
    descLabel->setFixedHeight(30);
    descLabel->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

    vLayout->addWidget(idLabel);
    vLayout->addWidget(nameLabel);
    vLayout->addWidget(descLabel);

    for (auto it = streamsMap.constBegin(); it != streamsMap.constEnd(); ++it) {
        if (!it.value().isEmpty()) {
            QString streamKey = streamToString(it.key());
            QString streamValue = it.value();
            QString streamName = streamKey + streamValue;

            QPushButton* streamButton = new QPushButton(streamName, ui->verticalLayoutWidget);
            streamButton->setObjectName("streamButton" + id);
            streamButton->setFixedHeight(30);
            QUrl streamURL = QUrl(streamValue);
            connect(streamButton, &QPushButton::clicked, this, [name, streamURL, this]() { PlayBack(name, streamURL, true); });
            vLayout->addWidget(streamButton);
        }
    }
    hLayout->addWidget(logoLabel);
    hLayout->addLayout(vLayout);
    ui->verticalLayout->addLayout(hLayout);
}
