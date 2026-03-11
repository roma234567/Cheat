#pragma once

#include <QImage>
#include <QRect>

class ScreenCapture {
public:
    ScreenCapture() = default;

    bool initialize();
    QImage captureFrame(const QRect& region = {});

private:
    bool initialized_{false};
    // TODO: Replace fallback capture with Desktop Duplication API for 30-60 FPS sustained capture.
};
