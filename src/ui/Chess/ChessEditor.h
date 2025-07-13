#ifndef CHESSEDITOR_H
#define CHESSEDITOR_H

#include "../base/BaseWidget.h"

class FigureForm;
class FigureMoveForm;

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
  ChessEditor(QWidget* parent = nullptr);

signals:
  void updateScheneJson(QJsonObject data);

public slots:
  void toggleCellState(const QString cell);

private slots:
  void updateFormInfo();

private:
  void setup();
  void setupStyleSheet();

  QWidget* initTopToolbar();

  QWidget* initCenterSidebar();
  QWidget* initLeftSidebar();

  bool toggleCellInArray(QJsonObject& boardObj, const QString& arrayKey,
                         const QString& cell);

private:
  QGraphicsView* m_display;

  CellType m_currentType;
  QList<FigureForm*> m_figuresListObject;
};




#endif // CHESSEDITOR_H
