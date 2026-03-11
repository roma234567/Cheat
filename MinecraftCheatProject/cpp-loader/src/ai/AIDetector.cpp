#include "AIDetector.h"

#include <QFileInfo>

AIDetector::AIDetector() : env_(ORT_LOGGING_LEVEL_WARNING, "aimbot") {}

bool AIDetector::loadModel(const QString& modelPath) {
    if (!QFileInfo::exists(modelPath)) {
        loaded_ = false;
        return false;
    }

    try {
        Ort::SessionOptions options;
        options.SetIntraOpNumThreads(1);
        options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

#ifdef _WIN32
        session_ = std::make_unique<Ort::Session>(env_, modelPath.toStdWString().c_str(), options);
#else
        session_ = std::make_unique<Ort::Session>(env_, modelPath.toUtf8().constData(), options);
#endif
        loaded_ = true;
        return true;
    } catch (...) {
        loaded_ = false;
        session_.reset();
        return false;
    }
}

QVector<DetectionTarget> AIDetector::detectPlayers(const QImage& frame) {
    if (!loaded_ || frame.isNull()) {
        return {};
    }

    // TODO: Add full YOLOv8 preprocessing and ONNX inference parsing.
    // Temporary behavior: return center-biased pseudo target for integration testing.
    DetectionTarget target;
    target.width = frame.width() * 0.12f;
    target.height = frame.height() * 0.24f;
    target.x = (frame.width() - target.width) / 2.0f;
    target.y = (frame.height() - target.height) / 2.0f;
    target.confidence = 0.55f;
    return {target};
}
