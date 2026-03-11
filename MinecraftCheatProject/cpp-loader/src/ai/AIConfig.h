#pragma once

#include <QString>

struct AISettings {
    bool enabled{false};
    int keyBind{2};          // VK_RBUTTON by default
    int smooth{8};
    int fov{180};
    bool autoShoot{false};
    QString modelPath{"models/yolov8_player.onnx"};
};

class AIConfig {
public:
    explicit AIConfig(QString filePath);

    AISettings load() const;
    bool save(const AISettings& settings) const;

private:
    QString filePath_;
};
