#include "MainMenu.h"
#include "../Common.h"

#include <QLabel>
#include <QLayout>
#include <QPushButton>

MainMenu::MainMenu()
{
  setup();
}

void MainMenu::setup()
{
  QWidget* mainWidget = new QWidget();

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(setupGameFormStart(WIDGET_CHESS_GAME, LINK_IMG_CHESS_MENU), 0, 0);
  layout->addWidget(setupGameFormStart(WIDGET_SUDOKU_GAME, LINK_IMG_SUDOKU_MENU), 0, 1);

  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());

  QHBoxLayout* box = new QHBoxLayout(this);
  box->addWidget(mainWidget, Qt::AlignCenter);
}

QWidget* MainMenu::setupGameFormStart(QString name, QString link)
{
  QWidget* mainWidegt = new QWidget;

  QPushButton* btnStartGame = new QPushButton("начать");
  btnStartGame->setObjectName(name);

  QVBoxLayout* box = new QVBoxLayout;
  box->addWidget(setupImage(link));
  box->addWidget(btnStartGame);

  mainWidegt->setLayout(box);
  connect(btnStartGame, &QPushButton::clicked, this, &BaseWidget::onSetWidgetClicked);
  return mainWidegt;
}

QLabel* MainMenu::setupImage(QString link)
{
  QImage* imageAvatar = new QImage;
  if (!imageAvatar->load(link))
  {
      qDebug() << "Ошибка загрузки изображения:" << link;
  }

  QLabel* lablelAvatar = new QLabel;
  lablelAvatar->setObjectName("avatar");
  lablelAvatar->setScaledContents(true);
  lablelAvatar->setFixedSize(200,200);
  lablelAvatar->setPixmap(QPixmap::fromImage(*imageAvatar));

  return lablelAvatar;
}

