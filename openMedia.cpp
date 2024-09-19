// Global outputText, title, artist

void MainWindow::openMedia(const QString &metaUrl) {
    if (Format_Context) {
        avformat_close_input(&Format_Context);
        Format_Context = nullptr;
    }

    avformat_network_init();
    FFurl = metaUrl.toUtf8().constData();

    if (avformat_open_input(&Format_Context, FFurl, nullptr, nullptr) < 0) {
        qDebug() << "Could not open source: " << FFurl;
        return;
    }
    if (avformat_find_stream_info(Format_Context, nullptr) < 0) {
        qDebug() << "*** Error: Could Not Find Stream Information ***";
        return;
    }

    // Print detailed information about the format
    av_dump_format(Format_Context, 0, FFurl, 0);

    metadata = Format_Context->metadata;
     if (metadata) {
        AVDictionaryEntry* tag = nullptr;
        while ((tag = av_dict_get(metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            QString key = QString::fromUtf8(tag->key);
            QString value = QString::fromUtf8(tag->value);
            QTextDocument textDoc;
            textDoc.setHtml(value);
            outputText += QString("NEW Key: %1, Value: %2\n").arg(key).arg(value);
            if (key == "StreamTitle") {
                QString icyname = textDoc.toPlainText();
                QStringList icyparts = icyname.split(" - ");
                if (icyparts.size() == 2) {
                    artist = icyparts.at(0).trimmed();
                    title = icyparts.at(1).trimmed();
                } else {
                    qDebug() << "Unexpected format:" << icyname;
                }

            } else if (key == "icy-name") {
                title = textDoc.toPlainText();
            }
        }
     }
    outputText += QString("Format: %1\n").arg(Format_Context->iformat->name);
    outputText += QString("Duration: %1 seconds\n").arg(Format_Context->duration / AV_TIME_BASE);

    int numStreams = Format_Context->nb_streams;
    if (numStreams > 0) {
        outputText += QString("** Number of Streams: %1\n").arg(numStreams);
        for (unsigned int i = 0; i < numStreams; ++i) {
            AVStream* stream = Format_Context->streams[i];
            outputText += QString("Stream #%1:%2 codec=%3, bitrate=%4\n")
                    .arg(i)
                    .arg(stream->id)
                    .arg(avcodec_get_name(stream->codecpar->codec_id))
                    .arg(stream->codecpar->bit_rate);

            if (stream) {
                tag = nullptr;
                while ((tag = av_dict_get(stream->metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
                    outputText += QString("  %1: %2\n").arg(tag->key).arg(tag->value);
                    if (strcmp(tag->key, "title") == 0) {
                        title = QString::fromUtf8(tag->value);
                    }
                    if (strcmp(tag->key, "artist") == 0) {
                        artist = QString::fromUtf8(tag->value);
                    }
                    if (strcmp(tag->key, "lyrics") == 0) {
                        outputText += QString("Lyrics: %1\n").arg(tag->value);
                    }
                }
            } else {
                outputText += QString("No Streams or metadata available\n");
            }
        }
    }

    AVDictionary* metadata = Format_Context->metadata;
    if (metadata) {

        while ((tag = av_dict_get(metadata, "", tag, AV_DICT_IGNORE_SUFFIX))) {
            outputText += QString("Key: %1, Value: %2").arg(tag->key).arg(tag->value);
        }

    } else {
        outputText += QString("No metadata available.");
    }
    avformat_close_input(&Format_Context);
    Format_Context = nullptr;
}
