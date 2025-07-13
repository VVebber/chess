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
    src/factory/FiguresFactory.h src/factory/FiguresFactory.cpp

    src/ui/base/BaseWidget.cpp src/ui/base/BaseWidget.h
    src/ui/Chess/ChessMenu.h src/ui/Chess/ChessMenu.cpp
    src/ui/Chess/ChessEditor.h src/ui/Chess/ChessEditor.cpp
    src/ui/Chess/PlayMenu.h src/ui/Chess/PlayMenu.cpp

    src/ui/Chess/Subwidgets/ChessEditor/Left/ChessJsonList.h src/ui/Chess/Subwidgets/ChessEditor/Left/ChessJsonList.cpp
    src/ui/Chess/Subwidgets/ChessEditor/Right/RightMenuWidget.h src/ui/Chess/Subwidgets/ChessEditor/Right/RightMenuWidget.cpp
    src/ui/Chess/Subwidgets/ChessEditor/Right/FigureForm.h      src/ui/Chess/Subwidgets/ChessEditor/Right/FigureForm.cpp
    src/ui/Chess/Subwidgets/ChessEditor/Right/FigureMoveForm.h  src/ui/Chess/Subwidgets/ChessEditor/Right/FigureMoveForm.cpp

    src/models/Move.h src/models/Move.cpp
    src/models/Figure.h src/models/Figure.cpp
    src/models/BoardChess.h src/models/BoardChess.cpp
    src/models/MovePlanner.h src/models/MovePlanner.cpp

    src/managers/GameManager.h src/managers/GameManager.cpp
    src/managers/FiguresManager.h src/managers/FiguresManager.cpp
    src/managers/TextureManager.h src/managers/TextureManager.cpp
    src/managers/BoardViewManager.h src/managers/BoardViewManager.cpp
    src/managers/SwitchEditorButton.h src/managers/SwitchEditorButton.cpp

    src/core/AppVariables.h src/core/AppVariables.cpp
    src/core/ChessInfoJson.h src/core/ChessInfoJson.cpp
    src/core/ChessCoord.h src/core/ChessCoord.cpp
    src/core/EditMode.h src/core/EditMode.cpp

    src/ui/Chess/Forms/BaseForm.h src/ui/Chess/Forms/BaseForm.cpp
    src/ui/Chess/Forms/StepForm.h src/ui/Chess/Forms/StepForm.cpp
    src/ui/Chess/Forms/JumpForm.h src/ui/Chess/Forms/JumpForm.cpp
    src/ui/Chess/Forms/MoveConditionForm.h src/ui/Chess/Forms/MoveConditionForm.cpp
    src/ui/Chess/Forms/InitialConditionsForm.h src/ui/Chess/Forms/InitialConditionsForm.cpp
)

# configure_file(AppSettings.txt ${CMAKE_BINARY_DIR} COPYONLY)
# file(COPY translations/ DESTINATION ${CMAKE_BINARY_DIR}/translations)
file(COPY img/ DESTINATION ${CMAKE_BINARY_DIR}/img)
# file(COPY qml/ DESTINATION ${CMAKE_BINARY_DIR}/qml)

target_link_libraries(QtChess PRIVATE Qt6::Widgets Qt6::Quick Qt6::Sql)
