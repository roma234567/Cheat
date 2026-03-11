#include "AimbotLogic.h"

#include <QtMath>
#include <cmath>
#include <limits>

#ifdef _WIN32
#include <Windows.h>
#endif

AimbotLogic::AimbotLogic() {
    capture_.initialize();
}

void AimbotLogic::setSettings(const AISettings& settings) {
    settings_ = settings;
}

AISettings AimbotLogic::settings() const {
    return settings_;
}

bool AimbotLogic::loadModel(const QString& modelPath) {
    settings_.modelPath = modelPath;
    return detector_.loadModel(modelPath);
}

void AimbotLogic::processFrameAndAim() {
    if (!settings_.enabled) {
        return;
    }

#ifdef _WIN32
    if ((GetAsyncKeyState(settings_.keyBind) & 0x8000) == 0) {
        return;
    }
#endif

    const QImage frame = capture_.captureFrame();
    if (frame.isNull()) {
        return;
    }

    const auto targets = detector_.detectPlayers(frame);
    bool ok = false;
    const auto best = chooseBestTarget(targets, frame.size(), &ok);
    if (!ok) {
        return;
    }

    const QPointF targetCenter(best.x + best.width / 2.0f, best.y + best.height * 0.25f);
    smoothAimTo(targetCenter, frame.size());

#ifdef _WIN32
    if (settings_.autoShoot) {
        INPUT click[2]{};
        click[0].type = INPUT_MOUSE;
        click[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        click[1].type = INPUT_MOUSE;
        click[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(2, click, sizeof(INPUT));
    }
#endif
}

DetectionTarget AimbotLogic::chooseBestTarget(const QVector<DetectionTarget>& targets, const QSize& frameSize, bool* ok) const {
    if (targets.isEmpty()) {
        if (ok) *ok = false;
        return {};
    }

    const QPointF center(frameSize.width() / 2.0, frameSize.height() / 2.0);
    const float maxRadius = static_cast<float>(settings_.fov) / 2.0f;

    float bestDist = std::numeric_limits<float>::max();
    DetectionTarget best{};
    bool found = false;

    for (const auto& t : targets) {
        const QPointF tc(t.x + t.width / 2.0f, t.y + t.height / 2.0f);
        const float dist = std::hypot(tc.x() - center.x(), tc.y() - center.y());
        if (dist <= maxRadius && dist < bestDist) {
            bestDist = dist;
            best = t;
            found = true;
        }
    }

    if (ok) *ok = found;
    return best;
}

void AimbotLogic::smoothAimTo(const QPointF& target, const QSize& frameSize) const {
#ifdef _WIN32
    const QPointF center(frameSize.width() / 2.0, frameSize.height() / 2.0);
    const QPointF delta = target - center;

    const double smoothFactor = qMax(1, settings_.smooth);
    const LONG moveX = static_cast<LONG>(delta.x() / smoothFactor);
    const LONG moveY = static_cast<LONG>(delta.y() / smoothFactor);

    INPUT input{};
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MOVE;
    input.mi.dx = moveX;
    input.mi.dy = moveY;
    SendInput(1, &input, sizeof(INPUT));
#else
    Q_UNUSED(target);
    Q_UNUSED(frameSize);
#endif
}
