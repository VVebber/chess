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
const QString LINC_ING_ARROW_START = "./img/icons/ArrowStart.png";

const QString LINK_IMG_PAWN = "./img/figures/Pawns/1_Pawn.png";
const QString LINK_IMG_KNIGHT = "./img/figures/Knights/1_Knight.png";
const QString LINK_IMG_BISHOP  = "./img/figures/Bishops/1_Bishop.png";
const QString LINK_IMG_KING  = "./img/figures/Kings/1_King.png";
const QString LINK_IMG_QUEEN = "./img/figures/Queens/1_Queen.png";
const QString LINK_IMG_ROOK  = "./img/figures/Rooks/1_Rook.png";

const QString ARROW_SSTART = "ArrowStart";

const QString NAME = "name";

const QString BOARD = "board";
const QString TYPE_CHESS = "typeChess";
const QString DIMENSIONS = "dimensions";
const QString NO_SHOW_CELLS = "noShowCells";

const QString COUNT_PLAYERS = "players";
const QString PLAYER = "Player_%1";

const QString SQUARE = "square";
const QString CIRCLE = "circle";

const QString FIGURES = "figures";
const QString TYPE_FIGURE = "typeFigure";
const QString COUNT_FIGURE = "countFigure";
const QString START_POSITIONS = "startPositions";

const QString MOVE_PATTERNS = "movePatterns";
const QString STROKE_LENGTH = "strokeLength";
const QString IS_CELL_EMPTY = "isCellEmpty";
const QString DIRECTIONS = "directions";


const QString KING = "Король";
const QString PAWN = "Пешка";
const QString BISHOP = "Слон";
const QString ROOK = "Ладья";
const QString QUEEN = "Королева";
const QString KNIGHT = "Конь";

class QLayout;

QPushButton* setupBtnIcon(const QString& linkImg);
int findIndexInJsonArray(const QJsonArray& array, const QJsonValue& value);
void clearLayout(QLayout* layout);
void removeLastFromLayout(QLayout* layout);

// const QString LINK_IMG_ARROW_SHAPES_UP_ = "lc_arrowshapes.corner-right-arrow.svg"

#endif // COMMON_H
