#include "VersionManager.h"

#include <QDir>

#include "utils/FileUtils.h"

QStringList VersionManager::getVersions() {
    return {"1.21.4", "1.21.3", "1.20.6"};
}

bool VersionManager::downloadVersion(const QString& version, const QString& destinationDir) const {
    // Simplified placeholder downloader logic.
    QDir dir(destinationDir);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {
            return false;
        }
    }

    const QString manifestUrl = QString("https://launchermeta.mojang.com/mc/game/version_manifest_v2.json");
    const QString targetFile = dir.filePath(QString("%1_manifest.json").arg(version));
    return FileUtils::downloadFile(manifestUrl, targetFile);
}
