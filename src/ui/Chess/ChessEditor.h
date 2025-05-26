#ifndef CHESSEDITOR_H
#define CHESSEDITOR_H

#include "../base/BaseWidget.h"

class FigureForm;
class FigureMoveForm;

class QSpinBox;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
class QButtonGroup;
class QGraphicsView;

class ChessEditor : public BaseWidget
{
  Q_OBJECT

  enum class CellType {
    None,
    NoShow,
    Special,
    Wrap
  };

public:
  ChessEditor();

signals:
  void updateChess(QJsonObject data);

public slots:
  void toggleCellState(const QString cell);
  void onUpdateCountPlayers(int count);

  void onSaveToFileClicked();

private slots:
  void onClickedAddFigureForm();
  void updateInfoForm();

private:
  void setup();

  QWidget* initTopToolbar();
  QWidget* initRightSidebar();
  QWidget* initCenterSidebar();
  QWidget* initLeftSidebar();
  QHBoxLayout* initModeSwitchFigure();
  QWidget* initFiguresFormList();

  bool toggleCellInArray(QJsonObject& boardObj, const QString& arrayKey,
                         const QString& cell);

  void save();

private:
  QGraphicsView* m_display;

  QLineEdit* m_nameChess;
  QLineEdit* m_dimensions;

  QVBoxLayout* m_figuresFormList;

  FigureMoveForm* m_figureMoveForm;

  QButtonGroup* m_btnGroup;

  CellType m_currentType;

  QList<FigureForm*> m_figuresListObject;
  QMap<int, FigureForm*> m_updatePos;
};

#endif // CHESSEDITOR_H
