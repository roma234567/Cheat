#include "AIConfig.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

AIConfig::AIConfig(QString filePath) : filePath_(std::move(filePath)) {}

AISettings AIConfig::load() const {
    AISettings cfg;

    QFile file(filePath_);
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return cfg;
    }

    const QJsonObject obj = QJsonDocument::fromJson(file.readAll()).object();
    cfg.enabled = obj.value("enabled").toBool(cfg.enabled);
    cfg.keyBind = obj.value("keyBind").toInt(cfg.keyBind);
    cfg.smooth = obj.value("smooth").toInt(cfg.smooth);
    cfg.fov = obj.value("fov").toInt(cfg.fov);
    cfg.autoShoot = obj.value("autoShoot").toBool(cfg.autoShoot);
    cfg.modelPath = obj.value("modelPath").toString(cfg.modelPath);
    return cfg;
}

bool AIConfig::save(const AISettings& settings) const {
    QFile file(filePath_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        return false;
    }

    QJsonObject obj;
    obj.insert("enabled", settings.enabled);
    obj.insert("keyBind", settings.keyBind);
    obj.insert("smooth", settings.smooth);
    obj.insert("fov", settings.fov);
    obj.insert("autoShoot", settings.autoShoot);
    obj.insert("modelPath", settings.modelPath);

    file.write(QJsonDocument(obj).toJson(QJsonDocument::Indented));
    return true;
}
