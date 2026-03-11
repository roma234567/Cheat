#include <QApplication>
#include <QMessageBox>
#include <QIcon>

#include "LauncherGUI.h"

int main(int argc, char* argv[]) {
    try {
        QApplication app(argc, argv);
        app.setApplicationName("Minecraft Cheat Loader");
        app.setOrganizationName("MinecraftCheatProject");

        LauncherGUI window;
        window.show();

        return app.exec();
    } catch (const std::exception& ex) {
        QMessageBox::critical(nullptr, "Fatal error", QString("Unhandled exception: %1").arg(ex.what()));
    } catch (...) {
        QMessageBox::critical(nullptr, "Fatal error", "Unknown fatal error occurred.");
    }

    return 1;
}
