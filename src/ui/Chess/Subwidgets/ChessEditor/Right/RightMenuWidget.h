#ifndef RIGHTMENUWIDGET_H
#define RIGHTMENUWIDGET_H

#include "../../../../../core/AppVariables.h"

#include <QWidget>

class FigureForm;

class QSpinBox;
class QLineEdit;
class QHBoxLayout;
class QVBoxLayout;
class QToolButton;
class QButtonGroup;
class QAbstractButton;

class RightMenuWidget : public QWidget
{
  Q_OBJECT
public:
  RightMenuWidget();

  void updatePosFigure(const QString& pos, QAbstractButton* btn);

public:
  void updateFormInfo(QJsonObject data);

private:
  void setup();
  void setupVariabels();
  void setupStyleSheet();

  QHBoxLayout* initPlayerCountRow();
  QHBoxLayout* initModeSwitchFigure();
  QToolButton* initFiguresToolButton();
  QWidget*     initFiguresFormList();
  QWidget*     initFiguresWidget();

private slots:
  void onClickedAddFigureForm();
  void onClickedSaveJson();
  void onClickedSwich();


signals:
  void updateScene();
  void updateScheneJson(QJsonObject data);

private:
  QLineEdit* m_dimensions;
  QLineEdit* m_nameChess;

  QSpinBox*  m_countPlayers;

  QButtonGroup* m_btnSwich;

  QVBoxLayout* m_figuresFormList;
  QList<FigureForm*> m_figuresListObject;

  AppVariables m_valiabeles;
};

#endif // RIGHTMENUWIDGET_H
