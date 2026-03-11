#include "FileUtils.h"

#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

bool FileUtils::createDirectory(const QString& path) {
    QDir dir;
    return dir.mkpath(path);
}

bool FileUtils::copyFile(const QString& source, const QString& destination) {
    if (!QFileInfo::exists(source)) {
        return false;
    }

    QFile::remove(destination);
    return QFile::copy(source, destination);
}

bool FileUtils::downloadFile(const QString& url, const QString& outputPath) {
    QNetworkAccessManager manager;
    QNetworkRequest request(QUrl(url));

    QEventLoop loop;
    QNetworkReply* reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
        reply->deleteLater();
        return false;
    }

    QFile file(outputPath);
    if (!file.open(QIODevice::WriteOnly)) {
        reply->deleteLater();
        return false;
    }

    file.write(reply->readAll());
    file.close();
    reply->deleteLater();
    return true;
}

bool FileUtils::fileExists(const QString& path) {
    return QFileInfo::exists(path);
}
