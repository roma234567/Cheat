#include "NetworkManager.h"

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

NetworkManager::NetworkManager(QObject* parent) : QObject(parent) {}

QByteArray NetworkManager::getSync(const QUrl& url, bool* ok) {
    QNetworkAccessManager manager;
    QNetworkRequest request(url);

    QEventLoop loop;
    QNetworkReply* reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    const bool success = reply->error() == QNetworkReply::NoError;
    if (ok != nullptr) {
        *ok = success;
    }

    const QByteArray payload = success ? reply->readAll() : QByteArray{};
    reply->deleteLater();
    return payload;
}
