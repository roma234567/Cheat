#pragma once

#include <QMainWindow>
#include <memory>

class QLineEdit;
class QComboBox;
class QPushButton;
class QTextEdit;
class QCheckBox;
class QSlider;
class QTimer;

class AimbotLogic;
class AIConfig;

class LauncherGUI : public QMainWindow {
    Q_OBJECT

public:
    explicit LauncherGUI(QWidget* parent = nullptr);
    ~LauncherGUI() override = default;

public slots:
    void onLaunchClicked();
    void onLogMessage(const QString& message);
    void onAIToggle();
    void onAISettings();

private:
    QLineEdit* nicknameEdit_{};
    QComboBox* versionCombo_{};
    QPushButton* launchButton_{};
    QTextEdit* logOutput_{};

    QCheckBox* aiEnableCheck_{};
    QSlider* smoothSlider_{};
    QSlider* fovSlider_{};
    QComboBox* keyBindCombo_{};
    QPushButton* loadModelButton_{};
    QTimer* aiTickTimer_{};

    std::unique_ptr<AimbotLogic> aiModule_;
    std::unique_ptr<AIConfig> aiConfig_;

    void setupUI();
    void loadVersions();
};
