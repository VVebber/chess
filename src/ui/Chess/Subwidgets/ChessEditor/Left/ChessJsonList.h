#ifndef CHESSJSONLIST_H
#define CHESSJSONLIST_H

#include <QWidget>

class QVBoxLayout;

class ChessJsonList : public QWidget
{
  Q_OBJECT
public:
  ChessJsonList();

private:
  void setup();
  void initFiles();
  void setupStyleSheet();

signals:
  void updateFormInfo();

private:
  QVBoxLayout* m_jsonListLayout;

};

#endif // CHESSJSONLIST_H
