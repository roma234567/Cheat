#pragma once

#include <QString>

class FileUtils {
public:
    static bool createDirectory(const QString& path);
    static bool copyFile(const QString& source, const QString& destination);
    static bool downloadFile(const QString& url, const QString& outputPath);
    static bool fileExists(const QString& path);
};
