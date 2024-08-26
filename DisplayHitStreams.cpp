void MainWindow::DisplayHitStreams() {
    auto streamToString = [](Streams stream) -> QString {
        switch (stream) {
            case Streams::pls:
                return "PLS";
            case Streams::secure_pls:
                return "Secure PLS";
            case Streams::hls:
                return "HLS";
            case Streams::secure_hls:
                return "Secure HLS";
            case Streams::shoutcast:
                return "Shoutcast";
            case Streams::secure_shoutcast:
                return "Secure Shoutcast";
            default:
                return "Unknown Stream";
        }
    };

    QString outputText;

    // Clear any existing widgets in the vertical layout
    clearLayout(ui->verticalLayout);

    // Extract the Id, name, and description from the QMap
    QString id = hitsMap.value(Hits::id);        // Assuming id is an enum value in Hits
    QString name = hitsMap.value(Hits::name);    // Assuming name is an enum value in Hits
    QString desc = hitsMap.value(Hits::desc);    // Assuming desc is an enum value in Hits
    // Append the extracted information to outputText
    outputText += QString("ID: %1 Name: %2 Description: %3\n").arg(id, name, desc);

    // Create two horizontal layouts and Add to verticalLayout
    QHBoxLayout* TopHLayout = new QHBoxLayout();
    ui->verticalLayout->addLayout(TopHLayout);
    QVBoxLayout* vLayout = new QVBoxLayout();
    ui->verticalLayout->addLayout(vLayout);
    //QHBoxLayout* hLayout = new QHBoxLayout();
    //vLayout->addLayout(hLayout);


    QLabel* idLabel = new QLabel(id, ui->verticalLayoutWidget);
    idLabel->setObjectName("idLabel" + id);
    idLabel->setFixedHeight(50);
    idLabel->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

    QLabel* nameLabel = new QLabel(name, ui->verticalLayoutWidget);
    nameLabel->setObjectName("nameLabel" + id);
    nameLabel->setFixedHeight(50);
    nameLabel->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

    QLabel* descLabel = new QLabel(desc, ui->verticalLayoutWidget);
    descLabel->setObjectName("descLabel" + id);
    descLabel->setFixedHeight(50);
    descLabel->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

    TopHLayout->addWidget(idLabel);
    TopHLayout->addWidget(nameLabel);
    TopHLayout->addWidget(descLabel);

    for (auto it = streamsMap.constBegin(); it != streamsMap.constEnd(); ++it) {
        if (!it.value().isEmpty()) {
            outputText += QString("%1 -> %2\n").arg(streamToString(it.key())).arg(it.value());

            // Generate Labels for Streams
            QString streamKey = streamToString(it.key());
            QString streamValue = it.value();

            // Create the QLabel for Stations::desc
            QLabel* streamType = new QLabel(streamKey, ui->verticalLayoutWidget);
            streamType->setObjectName("streamType" + id);
            streamType->setFixedHeight(50);
            streamType->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

            QPushButton* streamButton = new QPushButton(streamValue, ui->verticalLayoutWidget);
            streamButton->setObjectName("streamButton" + id);
            streamButton->setFixedHeight(50);
            QUrl streamURL = QUrl(streamValue);
            connect(streamButton, &QPushButton::clicked, this, [name, streamURL, this]() { PlayBack(name, streamURL, true); });
            //streamURL->setStyleSheet("QLabel { border-radius: 5px; border: 2px solid darkred; }");

            // Add these widgets to a horizontal layout
            vLayout->addWidget(streamType);
            vLayout->addWidget(streamButton);

        }
    }

    // Set the text to the outputText QTextEdit or QLabel in the UI
    ui->outputText->append(outputText);
}
