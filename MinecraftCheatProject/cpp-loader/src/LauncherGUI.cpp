#include "LauncherGUI.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSlider>
#include <QTabWidget>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "MinecraftLauncher.h"
#include "VersionManager.h"
#include "ai/AimbotLogic.h"
#include "ai/AIConfig.h"

LauncherGUI::LauncherGUI(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Minecraft Cheat Loader");
    resize(800, 600);

    aiModule_ = std::make_unique<AimbotLogic>();
    aiConfig_ = std::make_unique<AIConfig>("ai_settings.json");

    setupUI();
    loadVersions();

    const AISettings loaded = aiConfig_->load();
    aiEnableCheck_->setChecked(loaded.enabled);
    smoothSlider_->setValue(loaded.smooth);
    fovSlider_->setValue(loaded.fov);

    const int keyIndex = keyBindCombo_->findData(loaded.keyBind);
    if (keyIndex >= 0) {
        keyBindCombo_->setCurrentIndex(keyIndex);
    }
    aiModule_->setSettings(loaded);

    aiTickTimer_ = new QTimer(this);
    aiTickTimer_->setInterval(16); // ~60 FPS processing loop
    connect(aiTickTimer_, &QTimer::timeout, this, [this]() { aiModule_->processFrameAndAim(); });
    aiTickTimer_->start();

}

void LauncherGUI::setupUI() {
    auto* central = new QWidget(this);
    auto* rootLayout = new QVBoxLayout(central);
    auto* tabs = new QTabWidget(central);

    // Launch tab
    auto* launchTab = new QWidget(tabs);
    auto* launchLayout = new QVBoxLayout(launchTab);

    auto* nicknameLayout = new QHBoxLayout();
    auto* nicknameLabel = new QLabel("Nickname:", launchTab);
    nicknameEdit_ = new QLineEdit(launchTab);
    nicknameEdit_->setPlaceholderText("Enter your nickname...");
    nicknameLayout->addWidget(nicknameLabel);
    nicknameLayout->addWidget(nicknameEdit_);

    auto* versionLayout = new QHBoxLayout();
    auto* versionLabel = new QLabel("Minecraft version:", launchTab);
    versionCombo_ = new QComboBox(launchTab);
    versionLayout->addWidget(versionLabel);
    versionLayout->addWidget(versionCombo_);

    launchButton_ = new QPushButton("Launch", launchTab);
    logOutput_ = new QTextEdit(launchTab);
    logOutput_->setReadOnly(true);

    launchLayout->addLayout(nicknameLayout);
    launchLayout->addLayout(versionLayout);
    launchLayout->addWidget(launchButton_);
    launchLayout->addWidget(logOutput_, 1);

    tabs->addTab(launchTab, "Launcher");

    // AI tab
    auto* aiTab = new QWidget(tabs);
    auto* aiLayout = new QVBoxLayout(aiTab);

    aiEnableCheck_ = new QCheckBox("Включить AI", aiTab);
    aiLayout->addWidget(aiEnableCheck_);

    auto* smoothLabel = new QLabel("Smoothness (1-20)", aiTab);
    smoothSlider_ = new QSlider(Qt::Horizontal, aiTab);
    smoothSlider_->setRange(1, 20);
    smoothSlider_->setValue(8);

    auto* fovLabel = new QLabel("FOV (50-500)", aiTab);
    fovSlider_ = new QSlider(Qt::Horizontal, aiTab);
    fovSlider_->setRange(50, 500);
    fovSlider_->setValue(180);

    auto* keyLabel = new QLabel("Activation key", aiTab);
    keyBindCombo_ = new QComboBox(aiTab);
    keyBindCombo_->addItem("RMB", 0x02);
    keyBindCombo_->addItem("ALT", 0x12);
    keyBindCombo_->addItem("SHIFT", 0x10);
    keyBindCombo_->addItem("X", 0x58);

    loadModelButton_ = new QPushButton("Загрузить модель", aiTab);

    aiLayout->addWidget(smoothLabel);
    aiLayout->addWidget(smoothSlider_);
    aiLayout->addWidget(fovLabel);
    aiLayout->addWidget(fovSlider_);
    aiLayout->addWidget(keyLabel);
    aiLayout->addWidget(keyBindCombo_);
    aiLayout->addWidget(loadModelButton_);
    aiLayout->addStretch(1);

    tabs->addTab(aiTab, "AI Aimbot");

    rootLayout->addWidget(tabs);
    setCentralWidget(central);

    QFile styleFile("style.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setStyleSheet(QString::fromUtf8(styleFile.readAll()));
    }

    connect(launchButton_, &QPushButton::clicked, this, &LauncherGUI::onLaunchClicked);
    connect(aiEnableCheck_, &QCheckBox::toggled, this, &LauncherGUI::onAIToggle);
    connect(smoothSlider_, &QSlider::valueChanged, this, &LauncherGUI::onAISettings);
    connect(fovSlider_, &QSlider::valueChanged, this, &LauncherGUI::onAISettings);
    connect(keyBindCombo_, &QComboBox::currentIndexChanged, this, &LauncherGUI::onAISettings);
    connect(loadModelButton_, &QPushButton::clicked, this, [this]() {
        const QString modelPath = QFileDialog::getOpenFileName(this, "Load ONNX model", "models", "ONNX (*.onnx)");
        if (modelPath.isEmpty()) {
            return;
        }
        if (aiModule_->loadModel(modelPath)) {
            onLogMessage(QString("AI model loaded: %1").arg(modelPath));
            onAISettings();
        } else {
            QMessageBox::warning(this, "AI", "Failed to load selected model.");
        }
    });
}

void LauncherGUI::loadVersions() {
    const auto versions = VersionManager::getVersions();
    for (const auto& version : versions) {
        versionCombo_->addItem(version);
    }

    if (versionCombo_->count() == 0) {
        versionCombo_->addItem("1.21.4");
    }

    onLogMessage(QString("Loaded %1 version(s)").arg(versionCombo_->count()));
}

void LauncherGUI::onLaunchClicked() {
    const QString nickname = nicknameEdit_->text().trimmed();
    const QString version = versionCombo_->currentText();

    if (nickname.isEmpty()) {
        QMessageBox::warning(this, "Validation", "Please enter a nickname.");
        return;
    }

    onLogMessage(QString("Launching game for %1 on %2...").arg(nickname, version));

    MinecraftLauncher launcher(nickname, version);
    const bool ok = launcher.launch();
    if (ok) {
        onLogMessage("Launch process started successfully.");
    } else {
        onLogMessage("Failed to launch Minecraft process.");
    }
}

void LauncherGUI::onLogMessage(const QString& message) {
    const auto ts = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    logOutput_->append(QString("[%1] %2").arg(ts, message));
}

void LauncherGUI::onAIToggle() {
    onAISettings();
    onLogMessage(aiEnableCheck_->isChecked() ? "AI aimbot enabled." : "AI aimbot disabled.");
}

void LauncherGUI::onAISettings() {
    AISettings settings = aiModule_->settings();
    settings.enabled = aiEnableCheck_->isChecked();
    settings.smooth = smoothSlider_->value();
    settings.fov = fovSlider_->value();
    settings.keyBind = keyBindCombo_->currentData().toInt();

    aiModule_->setSettings(settings);
    aiConfig_->save(settings);
}
