#ifndef FIGUREFORM_H
#define FIGUREFORM_H

#include <QWidget>

class QLabel;
class QSpinBox;
class QComboBox;
class QGridLayout;
class QPushButton;
class QAbstractButton;

class FigureForm : public QWidget
{
  Q_OBJECT
public:
  FigureForm(int countPlayers);

  QJsonObject toJson();

private:
  void setup();

  void setupCountFigure();
  void setupStartPosList();
  void chanPos(const QString& newPos, QAbstractButton* btn);

private:
  static int m_countPlauers;

  QComboBox* m_typeFigure;

  QGridLayout* m_figureCount;
  QGridLayout* m_startPosList;

  QMap<QString, QLabel*> m_poslabels;
  QMap<QString, QSpinBox*> m_spinbox;
  QMap<QPushButton*, QLabel*> m_updatePos;

  friend class ChessEditor;
};

#endif // FIGUREFORM_H
