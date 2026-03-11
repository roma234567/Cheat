#pragma once

#include <QString>
#include <QStringList>

class AuthManager {
public:
    QString generateOfflineUUID(const QString& nickname) const;
    QStringList getLaunchArgs(const QString& nickname) const;
};
