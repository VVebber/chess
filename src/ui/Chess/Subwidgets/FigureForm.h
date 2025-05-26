#ifndef FIGUREFORM_H
#define FIGUREFORM_H

#include "../../base/BaseWidget.h"

class QLabel;
class QSpinBox;
class QComboBox;
class QGridLayout;
class QPushButton;
class QAbstractButton;

class FigureForm : public BaseWidget
{
  Q_OBJECT
public:
  FigureForm(QJsonObject data = QJsonObject());

  QJsonObject toJson(QJsonObject data);

  void updateForm(QJsonObject data = QJsonObject());

private:
  void setup();

  void setupCountFigure(QJsonObject data = QJsonObject());
  void setupStartPosList(QJsonObject data = QJsonObject());
  void chanPos(const QString& newPos, QAbstractButton* btn);
  void connectSpinboxSignals();

private:
  int m_countPlayers;

  QComboBox* m_typeFigure;

  QGridLayout* m_figureCount;
  QGridLayout* m_startPosList;

  QJsonObject* m_figureInfo;

  QMap<QString, QLabel*> m_poslabels;
  QMap<QString, QSpinBox*> m_spinbox;
  QMap<QPushButton*, QLabel*> m_updatePos;

  friend class ChessEditor;
};

#endif // FIGUREFORM_H
