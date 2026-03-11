#include "ScreenCapture.h"

#include <QGuiApplication>
#include <QScreen>

bool ScreenCapture::initialize() {
    initialized_ = QGuiApplication::primaryScreen() != nullptr;
    return initialized_;
}

QImage ScreenCapture::captureFrame(const QRect& region) {
    if (!initialized_) {
        initialize();
    }

    auto* screen = QGuiApplication::primaryScreen();
    if (!screen) {
        return {};
    }

    QRect targetRegion = region;
    if (targetRegion.isNull()) {
        targetRegion = screen->geometry();
    }

    const QPixmap pixmap = screen->grabWindow(0, targetRegion.x(), targetRegion.y(), targetRegion.width(), targetRegion.height());
    return pixmap.toImage();
}
