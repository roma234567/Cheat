#pragma once

#include <QPointF>
#include <QVector>

#include "AIDetector.h"
#include "AIConfig.h"
#include "ScreenCapture.h"

class AimbotLogic {
public:
    AimbotLogic();

    void setSettings(const AISettings& settings);
    AISettings settings() const;

    bool loadModel(const QString& modelPath);
    void processFrameAndAim();

private:
    DetectionTarget chooseBestTarget(const QVector<DetectionTarget>& targets, const QSize& frameSize, bool* ok) const;
    void smoothAimTo(const QPointF& target, const QSize& frameSize) const;

    AISettings settings_{};
    ScreenCapture capture_{};
    AIDetector detector_{};
};
