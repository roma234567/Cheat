#pragma once

#include <QObject>
#include <QUrl>

class NetworkManager : public QObject {
    Q_OBJECT

public:
    explicit NetworkManager(QObject* parent = nullptr);

    QByteArray getSync(const QUrl& url, bool* ok = nullptr);

    // TODO: Add async API with retries and timeout configuration.
};
