#include "ChessMenu.h"
#include "../../Common.h"
#include "../../managers/ChessBoardManager.h"

#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QGraphicsView>

ChessMenu::ChessMenu()
{
  resize(1280,720);
  setObjectName(WIDGET_CHESS_GAME);
  m_display = new QGraphicsView;
  m_display->setFixedSize(550, 550);
  m_display->setScene(ChessBoardManager::getInstance().getChessBoard());

  setup();
  setupStyleSheet();
}

void ChessMenu::setup()
{
  QWidget* mainWidget = new QWidget();

  QGridLayout* layout = new QGridLayout(mainWidget);

  layout->addWidget(m_display, 0, 0, Qt::AlignRight);
  layout->addWidget(setupBtn(), 0, 1, Qt::AlignRight);


  mainWidget->setLayout(layout);
  mainWidget->adjustSize();
  mainWidget->setFixedSize(mainWidget->size() * 1.2);

  QHBoxLayout* box = new QHBoxLayout(this);
  box->addWidget(mainWidget, Qt::AlignCenter);

}

QWidget* ChessMenu::setupBtn()
{
  QWidget* mainWidget = new QWidget;

  QPushButton* chessEditor = new QPushButton("Редактировать доску");
  chessEditor->setObjectName(WIDGET_CHESS_EDITOR);

  QPushButton* startGame = new QPushButton("Начать играть");
  QPushButton* chessProblems = new QPushButton("Задачи");
  QPushButton* settings = new QPushButton("Настройки");
  QPushButton* exit = new QPushButton("выйти");


  QVBoxLayout* btnBox = new QVBoxLayout();
  btnBox->setSpacing(12);
  btnBox->addWidget(startGame);
  btnBox->addWidget(chessProblems);
  btnBox->addWidget(settings);
  btnBox->addWidget(chessEditor);
  btnBox->addWidget(exit);

  mainWidget->setLayout(btnBox);

  connect(chessEditor, &QPushButton::clicked, this, &BaseWidget::onSetWidgetClicked);

  return mainWidget;
}

void ChessMenu::setupStyleSheet()
{
  setStyleSheet(QString(R"(
    QPushButton {
      background-color: #b97a56; color: #fffaf0;
      border: 2px solid #5a3b2e;
      border-radius: 10px;
      padding: 8px 20px;
      font: bold 16px "Segoe UI";
    }

    QPushButton:hover {
     background-color: #d6a878;
        color: white;
    }

    QPushButton:pressed {
        background-color: #a9654b; /* Чуть темнее при нажатии */
        color: #fffaf0;
    }

    QGraphicsView {
        border: 4px solid #8b5a2b;
        border-radius: 4px;
    }
)"));
}
