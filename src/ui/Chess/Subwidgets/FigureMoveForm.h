#ifndef FIGUREMOVEFORM_H
#define FIGUREMOVEFORM_H

#include "../../base/BaseWidget.h"

#include <QJsonArray>

class QSpinBox;
class QCheckBox;
class QComboBox;
class QGridLayout;

class FigureMoveForm : public BaseWidget
{
  Q_OBJECT
public:
  FigureMoveForm();

  QJsonArray toJson();

public slots:
  void  updateJson();

signals:
  void update(QJsonObject data);

private:
  void setup();

  void initDirectionsGrid();
  QWidget* directionsGrid();
  QCheckBox* checkBoxWithImage(int rotate = 0);

  QWidget* initFirstMoveForm();
  QWidget* initCellHasEnemyForm();
  QWidget* initTransformationForm();
  QWidget* initInitialConditionsForm();

private:
  int m_previousId;
  QComboBox* m_listFigure;

  QJsonArray m_infoFigures;
  QJsonObject m_infoMovePatterns;

  QSpinBox*m_firstMove;

  QGridLayout* m_directionsGrid;

  QMap<QString, std::function<QJsonArray()>> m_jsonDirection;
};

/*
 идея: сделать список QVariant для переменных
 QMap<QVariant, QString> m_..;
*/
#endif // FIGUREMOVEFORM_H
