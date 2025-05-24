#ifndef CHESSEDITOR_H
#define CHESSEDITOR_H

#include "../base/BaseWidget.h"

class FigureForm;

class QSpinBox;
class QLineEdit;
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
  void update(QJsonObject data);

public slots:
  void toggleCellState(const QString cell);

private slots:
  void onClickedAddFigureForm();

private:
  void setup();

  QWidget* initTopToolbar();
  QWidget* initRightSidebar();
  QWidget* initCenterSidebar();
  QWidget* initLeftSidebar();

  void setupFigureForm();

  bool toggleCellInArray(QJsonObject& boardObj, const QString& arrayKey,
                                                const QString& cell);

  void save();

private:
  QGraphicsView* m_display;
  QJsonObject m_infoBoard;

  QLineEdit* m_nameBoard;
  QLineEdit* m_dimensions;
  QSpinBox* m_countPlayers;
  QVBoxLayout* m_figuresListWidget;
  QButtonGroup* m_btnGroup;

  CellType m_currentType;

  QList<FigureForm*> m_figuresListObject;
  QMap<int, FigureForm*> m_updatePos;
};

#endif // CHESSEDITOR_H
