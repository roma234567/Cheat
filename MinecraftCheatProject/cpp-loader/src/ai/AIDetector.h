#pragma once

#include <QString>
#include <QVector>
#include <QImage>
#include <memory>

#include <onnxruntime_cxx_api.h>

struct DetectionTarget {
    float x{};
    float y{};
    float width{};
    float height{};
    float confidence{};
};

class AIDetector {
public:
    AIDetector();

    bool loadModel(const QString& modelPath);
    QVector<DetectionTarget> detectPlayers(const QImage& frame);

private:
    Ort::Env env_;
    std::unique_ptr<Ort::Session> session_;
    bool loaded_{false};
};
