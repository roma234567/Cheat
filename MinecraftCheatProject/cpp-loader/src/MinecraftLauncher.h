#pragma once

#include <QString>

class MinecraftLauncher {
public:
    explicit MinecraftLauncher(QString nickname, QString version);

    bool launch();
    QString findJava() const;
    QString generateUUID() const;

private:
    QString nickname_;
    QString version_;
    QString javaPath_;
    QString gameDir_;
};
