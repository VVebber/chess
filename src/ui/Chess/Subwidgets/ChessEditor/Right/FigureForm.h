#ifndef FIGUREFORM_H
#define FIGUREFORM_H

#include <QWidget>
#include <QJsonObject>

class QLabel;
class QSpinBox;
class QComboBox;
class QGridLayout;
class QPushButton;
class QAbstractButton;
class QPaintEvent;

class FigureForm : public QWidget
{
  Q_OBJECT
  struct FigureSettings
  {
      QString playerKey;
      QSpinBox* spinBox;
      QPushButton* updatePos;
      QLabel* posLabel;

      FigureSettings();
  };
public:
  FigureForm(int countPlayer);

  QJsonObject toJson(QJsonObject data);

  void updateForm();
  void updateFormInfo(QJsonObject data);

public slots:
  void updateCountPlayers(int count);

private:
  void setup();
  void setupSettingsForm();
  void setupStyleSheet();

  void chanPos(const QString& newPos, QAbstractButton* btn);
  void connectSpinboxSignals();

  void paintEvent(QPaintEvent* event) override;

private:
  int m_countPlayers;
  QComboBox* m_typeFigure;

  QGridLayout* m_figureCountList;
  QGridLayout* m_startPosList;

  QList<FigureSettings> m_figures;

  friend class RightMenuWidget;
};

#endif // FIGUREFORM_H
