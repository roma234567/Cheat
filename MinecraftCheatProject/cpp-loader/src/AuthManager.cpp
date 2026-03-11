#include "AuthManager.h"

#include <QCryptographicHash>

QString AuthManager::generateOfflineUUID(const QString& nickname) const {
    const QByteArray input = QString("OfflinePlayer:%1").arg(nickname).toUtf8();
    const QByteArray hash = QCryptographicHash::hash(input, QCryptographicHash::Md5).toHex();

    QString uuid(hash);
    uuid.insert(8, '-');
    uuid.insert(13, '-');
    uuid.insert(18, '-');
    uuid.insert(23, '-');
    return uuid;
}

QStringList AuthManager::getLaunchArgs(const QString& nickname) const {
    return {
        "--username", nickname,
        "--uuid", generateOfflineUUID(nickname),
        "--accessToken", "null",
        "--userType", "legacy"
    };
}
