#include "UUIDGenerator.h"

#include <QCryptographicHash>

QString UUIDGenerator::generateFromString(const QString& input) {
    const QByteArray hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Md5).toHex();

    QString uuid(hash);
    uuid.insert(8, '-');
    uuid.insert(13, '-');
    uuid.insert(18, '-');
    uuid.insert(23, '-');
    return uuid;
}
