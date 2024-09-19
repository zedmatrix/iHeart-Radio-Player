#ifndef ENUM_PARSER_H
#define ENUM_PARSER_H

enum class Hits {
    id,
    desc,
    name,
    link,
    logo,
    band,
    freq,
    call,
    active,
    website,
    countries,
    feeds,
    format,
    genres,
    markets,
    HitsCount,
    Unknown
};

inline Hits hitToEnum(const QString &key) {
    if (key == "id") return Hits::id;
    if (key == "isActive") return Hits::active;
    if (key == "description") return Hits::desc;
    if (key == "name") return Hits::name;
    if (key == "link") return Hits::link;
    if (key == "logo") return Hits::logo;
    if (key == "band") return Hits::band;
    if (key == "freq") return Hits::freq;
    if (key == "callLetters") return Hits::call;
    if (key == "website") return Hits::website;
    if (key == "countries") return Hits::countries;
    if (key == "feeds") return Hits::feeds;
    if (key == "format") return Hits::format;
    if (key == "genres") return Hits::genres;
    if (key == "markets") return Hits::markets;
    if (key.contains("ads")) return Hits::Unknown;
    if (key.contains("rds")) return Hits::Unknown;
    if (key == "cume" || key == "modified") return Hits::Unknown;
    if (key == "pronouncements" || key == "provider") return Hits::Unknown;
    if (key == "responseType" || key == "streamingPlatform" || key == "talkbackEnabled") return Hits::Unknown;
    if (key == "score" || key == "social") return Hits::Unknown;

    throw std::invalid_argument("Unknown key: " + key.toStdString());
}

enum class Streams {
    pls,
    secure_pls,
    hls,
    secure_hls,
    shoutcast,
    secure_shoutcast,
    StreamsCount
};

inline Streams stringToEnum(const QString &key) {
    if (key == "pls_stream") return Streams::pls;
    if (key == "secure_pls_stream") return Streams::secure_pls;
    if (key == "hls_stream") return Streams::hls;
    if (key == "secure_hls_stream") return Streams::secure_hls;
    if (key == "shoutcast_stream") return Streams::shoutcast;
    if (key == "secure_shoutcast_stream") return Streams::secure_shoutcast;

    throw std::invalid_argument("Unknown key: " + key.toStdString());
}

enum class Stations {
    band,
    call,
    city,
    url,
    desc,
    freq,
    id,
    logo,
    name,
    newlogo,
    rank,
    score,
    state,
    link,
    StationsCount
};

inline Stations searchEnum(const QString &key) {
    if (key == "band") return Stations::band;
    if (key == "callLetters") return Stations::call;
    if (key == "city") return Stations::city;
    if (key == "dartUrl") return Stations::url;
    if (key == "description") return Stations::desc;
    if (key == "frequency") return Stations::freq;
    if (key == "logo") return Stations::logo;
    if (key == "name") return Stations::name;
    if (key == "newlogo") return Stations::newlogo;
    if (key == "rank") return Stations::rank;
    if (key == "score") return Stations::score;
    if (key == "state") return Stations::state;
    if (key == "id") return Stations::id;
    if (key == "shareLink") return Stations::link;

    throw std::invalid_argument("Unknown key: " + key.toStdString());
}

extern QMap<Hits, QString> hitsMap;
extern QMap<Streams, QString> streamsMap;
extern QMap<Stations, QString> stationMap;
extern QList<QMap<Stations, QString>> allStations;

#endif //ENUM_PARSER_H
