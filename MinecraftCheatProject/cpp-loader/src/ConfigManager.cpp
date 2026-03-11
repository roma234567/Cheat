#include "ConfigManager.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

ConfigManager::ConfigManager(QString filePath) : filePath_(std::move(filePath)) {}

bool ConfigManager::load() {
    QFile file(filePath_);
    if (!file.exists()) {
        return true;
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    const auto json = QJsonDocument::fromJson(file.readAll());
    const auto obj = json.object();
    nickname_ = obj.value("nickname").toString();
    selectedVersion_ = obj.value("selectedVersion").toString("1.21.4");
    return true;
}

bool ConfigManager::save() const {
    QFile file(filePath_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }

    QJsonObject obj;
    obj.insert("nickname", nickname_);
    obj.insert("selectedVersion", selectedVersion_);

    // TODO: Encrypt sensitive fields when online auth is introduced.
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
    return true;
}

QString ConfigManager::nickname() const { return nickname_; }
void ConfigManager::setNickname(const QString& value) { nickname_ = value; }

QString ConfigManager::selectedVersion() const { return selectedVersion_; }
void ConfigManager::setSelectedVersion(const QString& value) { selectedVersion_ = value; }
