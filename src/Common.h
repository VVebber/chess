#ifndef COMMON_H
#define COMMON_H

#include <QString>

class QJsonValue;
class QJsonArray;
class QPushButton;

const QString WIDGET_MAIN_MENU       = QStringLiteral("mainMenu");

const QString WIDGET_CHESS_GAME      = QStringLiteral("chessGameMenu");
const QString WIDGET_SUDOKU_GAME     = QStringLiteral("sudokuGameMenu");

const QString WIDGET_CHESS_EDITOR    = QStringLiteral("chessEditor");
const QString WIDGET_PLAY_MENU       = QStringLiteral("playMenu");

const QString FIGURE_FORM            = QStringLiteral("figureForm");
const QString FIGURE_MOVE_FORM       = QStringLiteral("figureMoveForm");
const QString RIGHT_MENU_WIDGET      = QStringLiteral("rightMenuWidget");

const QString LINK_IMG_CHESS_MENU    = QStringLiteral("./img/ChessMenu.jpeg");
const QString LINK_IMG_SUDOKU_MENU   = QStringLiteral("./img/SudokuMenu.jpeg");

const QString LINK_IMG_DELETE_1      = QStringLiteral("./img/icons/delete_1.png");
const QString LINK_IMG_ADD_1         = QStringLiteral("./img/icons/add_1.png");
const QString LINK_IMG_JOIN_1        = QStringLiteral("./img/icons/join_1.png");

const QString LINK_IMG_SQUARE        = QStringLiteral("./img/icons/square.png");
const QString LINK_IMG_CIRCLE        = QStringLiteral("./img/icons/circle.png");
const QString LINK_IMG_TRIANGLE      = QStringLiteral("./img/icons/triangle.png");
const QString LINK_IMG_ARROW_START   = QStringLiteral("./img/icons/ArrowStart.png");

const QString LINK_IMG_PAWN          = QStringLiteral("./img/figures/Pawns/1_Pawn.png");
const QString LINK_IMG_KNIGHT        = QStringLiteral("./img/figures/Knights/1_Knight.png");
const QString LINK_IMG_BISHOP        = QStringLiteral("./img/figures/Bishops/1_Bishop.png");
const QString LINK_IMG_KING          = QStringLiteral("./img/figures/Kings/1_King.png");
const QString LINK_IMG_QUEEN         = QStringLiteral("./img/figures/Queens/1_Queen.png");
const QString LINK_IMG_ROOK          = QStringLiteral("./img/figures/Rooks/1_Rook.png");

const QString ARROW_START            = QStringLiteral("ArrowStart");

const QString NAME                   = QStringLiteral("name");

const QString BOARD                  = QStringLiteral("board");
const QString TYPE_CHESS             = QStringLiteral("typeChess");
const QString DIMENSIONS             = QStringLiteral("dimensions");
const QString NO_SHOW_CELLS          = QStringLiteral("noShowCells");

const QString COUNT_PLAYERS          = QStringLiteral("players");
const QString PLAYER_EN              = QStringLiteral("Player_%1");
const QString PLAYER_RU              = QStringLiteral("Игрок %1");

const QString SQUARE                 = QStringLiteral("square");
const QString CIRCLE                 = QStringLiteral("circle");

const QString FIGURES                = QStringLiteral("figures");
const QString TYPE_FIGURE            = QStringLiteral("typeFigure");
const QString COUNT_FIGURE           = QStringLiteral("countFigure");
const QString START_POSITIONS        = QStringLiteral("startPositions");

const QString INITIAL_CONDIYIONS     = QStringLiteral("initialConditions");
const QString MOVE_PATTERNS          = QStringLiteral("movePatterns");
const QString STROKE_LENGTH          = QStringLiteral("strokeLength");
const QString MOVE_RULES             = QStringLiteral("moveRules");
const QString IS_CELL_EMPTY          = QStringLiteral("isCellEmpty");
const QString DIRECTIONS             = QStringLiteral("directions");
const QString STEPS                  = QStringLiteral("steps");
const QString JUMPS                  = QStringLiteral("jumps");

// Figure names (Russian, если нужны английские — могу сделать)
const QString KING                   = QStringLiteral("Король");
const QString PAWN                   = QStringLiteral("Пешка");
const QString BISHOP                 = QStringLiteral("Слон");
const QString ROOK                   = QStringLiteral("Ладья");
const QString QUEEN                  = QStringLiteral("Королева");
const QString KNIGHT                 = QStringLiteral("Конь");

// Groups (опечатки исправлены)
const QString ENEMIES                = QStringLiteral("enemies");
const QString ALLIES                 = QStringLiteral("allies");
const QString ALL                    = QStringLiteral("all");

// Conditions (condition)
const QString CONDITION                  = QStringLiteral("condition");
inline const QString CONDITION_HAS_PIECE = QStringLiteral("hasPiece");

// Events (event)
const QString ACTION                      = QStringLiteral("action");
const QString EVENT_N                     = QStringLiteral("evetn_%0");
inline const QString EVENT_CANCEL_MOVE    = QStringLiteral("cancelMove");
inline const QString EVENT_ADD_MOVE       = QStringLiteral("addMove");

// initial conditions

class QLayout;

QPushButton* setupBtnIcon(const QString& linkImg);
int findIndexInJsonArray(const QJsonArray& array, const QJsonValue& value);
void clearLayout(QLayout* layout);
void removeLastFromLayout(QLayout* layout);

// const QString LINK_IMG_ARROW_SHAPES_UP_ = "lc_arrowshapes.corner-right-arrow.svg"

#endif // COMMON_H
