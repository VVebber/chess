#ifndef COMMON_H
#define COMMON_H

#include <QString>

class QJsonValue;
class QJsonArray;
class QPushButton;

const QString WIDGET_MAIN_MENU = "main menu";

const QString WIDGET_CHESS_GAME = "chess game menu";
const QString WIDGET_SUDOKU_GAME = "sudoku game menu";

const QString WIDGET_CHESS_EDITOR = "chess editor";

const QString LINK_IMG_CHESS_MENU = "./img/ChessMenu.jpeg";
const QString LINK_IMG_SUDOKU_MENU = "./img/SudokeMenu.jpeg";

const QString LINK_IMG_DELETE_1 = "./img/icons/delete_1.png";
const QString LINK_IMG_ADD_1 = "./img/icons/add_1.png";
const QString LINK_IMG_JOIN_1 = "./img/icons/join_1.png";

const QString LINK_IMG_SQUARE = "./img/icons/square.png";
const QString LINK_IMG_CIRCLE = "./img/icons/circle.png";
const QString LINK_IMG_TRIANGLE = "./img/icons/triangle.png";

const QString LINK_PAWN = "./img/figures/Pawns/1_Pawn.png";

const QString NAME = "name";

const QString BOARD = "board";
const QString TYPE_CHESS = "typeChess";
const QString DIMENSIONS = "dimensions";
const QString NO_SHOW_CELLS = "noShowCells";

const QString COUNT_PLAYERS = "players";

const QString SQUARE = "square";
const QString CIRCLE = "circle";

const QString FIGURES = "figures";
const QString TYPE_FIGURE = "typeFigure";
const QString COUNT_FIGURE = "countFigure";
const QString START_POSITIONS = "startPositions";

const QString KING = "king";
const QString PAWN = "Пешка";

QPushButton* setupBtnIcon(const QString& linkImg);
int findIndexInJsonArray(const QJsonArray& array, const QJsonValue& value);

// const QString LINK_IMG_ARROW_SHAPES_UP_ = "lc_arrowshapes.corner-right-arrow.svg"

#endif // COMMON_H
