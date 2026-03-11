#pragma once

#include <QString>
#include <QStringList>

class VersionManager {
public:
    static QStringList getVersions();
    bool downloadVersion(const QString& version, const QString& destinationDir) const;
};
