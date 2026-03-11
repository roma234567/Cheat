#include "MinecraftLauncher.h"

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QStandardPaths>

#include "AuthManager.h"

MinecraftLauncher::MinecraftLauncher(QString nickname, QString version)
    : nickname_(std::move(nickname)), version_(std::move(version)) {
    gameDir_ = QDir::homePath() + "/.minecraft";
}

bool MinecraftLauncher::launch() {
    javaPath_ = findJava();
    if (javaPath_.isEmpty()) {
        return false;
    }

    QProcess* process = new QProcess();
    process->setProgram(javaPath_);

    AuthManager auth;
    QStringList args;
    args << "-Xmx2G";
    args << auth.getLaunchArgs(nickname_);
    args << "--version" << version_;
    args << "--gameDir" << gameDir_;

    process->setArguments(args);
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start();

    return process->waitForStarted(5000);
}

QString MinecraftLauncher::findJava() const {
    const QString javaExe = QStandardPaths::findExecutable("java");
    if (!javaExe.isEmpty()) {
        return javaExe;
    }

#ifdef Q_OS_WIN
    const QStringList candidates = {
        "C:/Program Files/Java/jdk-21/bin/java.exe",
        "C:/Program Files/Eclipse Adoptium/jdk-21*/bin/java.exe"
    };
#else
    const QStringList candidates = {
        "/usr/bin/java",
        "/usr/local/bin/java"
    };
#endif

    for (const auto& path : candidates) {
        if (QFileInfo::exists(path)) {
            return path;
        }
    }

    return {};
}

QString MinecraftLauncher::generateUUID() const {
    return AuthManager().generateOfflineUUID(nickname_);
}
