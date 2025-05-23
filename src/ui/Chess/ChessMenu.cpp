#include "ChessMenu.h"
#include "../../Common.h"

#include <QLayout>
#include <QPushButton>
#include <QLabel>

ChessMenu::ChessMenu()
{
  setup();
}

void ChessMenu::setup()
{
  QWidget* mainWidget = new QWidget(this);

  QGridLayout* layout = new QGridLayout;
  layout->addWidget(setupBtn(), 0, 0, Qt::AlignLeft | Qt::AlignHCenter);

  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size());
}

QWidget* ChessMenu::setupBtn()
{
  QWidget* mainWidget = new QWidget;

  QPushButton* chessEditor = new QPushButton("Редактировать доску");
  chessEditor->setObjectName(WIDGET_CHESS_EDITOR);

  QHBoxLayout* btnBox = new QHBoxLayout();
  btnBox->addWidget(chessEditor);

  mainWidget->setLayout(btnBox);

  connect(chessEditor, &QPushButton::clicked, this, &BaseWidget::onSetWidgetClicked);

  return mainWidget;
}
