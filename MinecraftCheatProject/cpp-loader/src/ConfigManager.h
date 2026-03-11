#pragma once

#include <QString>

class ConfigManager {
public:
    explicit ConfigManager(QString filePath);

    bool load();
    bool save() const;

    QString nickname() const;
    void setNickname(const QString& value);

    QString selectedVersion() const;
    void setSelectedVersion(const QString& value);

private:
    QString filePath_;
    QString nickname_;
    QString selectedVersion_;

    // TODO: Add validation and migration for future config schema versions.
};
