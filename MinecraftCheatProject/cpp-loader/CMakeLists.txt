cmake_minimum_required(VERSION 3.16)
project(MinecraftCheatLoader VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network Concurrent)
find_package(OpenCV REQUIRED)
find_package(ONNXRuntime REQUIRED)

set(SOURCES
    src/main.cpp
    src/LauncherGUI.cpp
    src/MinecraftLauncher.cpp
    src/VersionManager.cpp
    src/AuthManager.cpp
    src/ConfigManager.cpp
    src/NetworkManager.cpp
    src/utils/FileUtils.cpp
    src/utils/UUIDGenerator.cpp
    src/ai/AIDetector.cpp
    src/ai/ScreenCapture.cpp
    src/ai/AimbotLogic.cpp
    src/ai/AIConfig.cpp
)

set(HEADERS
    src/LauncherGUI.h
    src/MinecraftLauncher.h
    src/VersionManager.h
    src/AuthManager.h
    src/ConfigManager.h
    src/NetworkManager.h
    src/utils/FileUtils.h
    src/utils/UUIDGenerator.h
    src/ai/AIDetector.h
    src/ai/ScreenCapture.h
    src/ai/AimbotLogic.h
    src/ai/AIConfig.h
)

add_executable(minecraft-cheat-loader ${SOURCES} ${HEADERS})

target_include_directories(minecraft-cheat-loader PRIVATE
    src
    ${OpenCV_INCLUDE_DIRS}
    ${ONNXRUNTIME_INCLUDE_DIRS}
)

target_link_libraries(minecraft-cheat-loader PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::Concurrent
    ${OpenCV_LIBS}
    ${ONNXRUNTIME_LIBRARIES}
)

add_custom_command(TARGET minecraft-cheat-loader POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resources/style.qss
        $<TARGET_FILE_DIR:minecraft-cheat-loader>/style.qss
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:minecraft-cheat-loader>/models
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/ai/models/README.md
        $<TARGET_FILE_DIR:minecraft-cheat-loader>/models/README.md
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/src/ai/models/yolov8_player.onnx
        $<TARGET_FILE_DIR:minecraft-cheat-loader>/models/yolov8_player.onnx
)
