cmake_minimum_required(VERSION 3.5)

project(QtChess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED Widgets COMPONENTS Quick Sql )

add_executable(QtChess
    src/main.cpp

    src/MainWindow.cpp src/MainWindow.h

    src/Common.h src/Common.cpp
    src/ui/MainMenu.cpp src/ui/MainMenu.h

    src/factory/WidgetFactory.h src/factory/WidgetFactory.cpp
    src/ui/base/BaseWidget.cpp src/ui/base/BaseWidget.h
    src/ui/Chess/ChessMenu.h src/ui/Chess/ChessMenu.cpp
    src/ui/Chess/ChessEditor.h src/ui/Chess/ChessEditor.cpp

    src/models/Figure.h src/models/Figure.cpp
    src/models/BoardChess.h src/models/BoardChess.cpp

    src/managers/ChessBoardManager.h src/managers/ChessBoardManager.cpp
    src/managers/FiguresManager.h src/managers/FiguresManager.cpp
    src/managers/TextureManager.h src/managers/TextureManager.cpp
)

# configure_file(AppSettings.txt ${CMAKE_BINARY_DIR} COPYONLY)
# file(COPY translations/ DESTINATION ${CMAKE_BINARY_DIR}/translations)
file(COPY img/ DESTINATION ${CMAKE_BINARY_DIR}/img)
# file(COPY qml/ DESTINATION ${CMAKE_BINARY_DIR}/qml)

target_link_libraries(QtChess PRIVATE Qt6::Widgets Qt6::Quick Qt6::Sql)
