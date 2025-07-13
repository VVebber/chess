#include "PlayMenu.h"
#include "../../managers/BoardViewManager.h"
#include "../../Common.h"

#include <QKeyEvent>
#include <QHBoxLayout>
#include <QStackedLayout>

PlayMenu::PlayMenu(QWidget* parent) : BaseWidget(parent),
  m_elapsedSeconds(0), m_isPaused(false)
{
  resize(1280, 720);

  m_display = new QGraphicsView();
  m_display->setFixedSize(550, 550);
  m_display->setScene(BoardViewManager::getInstance().getScene());

  m_timerLabel = new QLabel("00:00");
  m_timerLabel->setStyleSheet("font-size: 18px; color: white;");

  m_moveLog = new QListWidget();
  m_moveLog->setFixedWidth(200);

  m_timer = new QTimer();
  connect(m_timer, &QTimer::timeout, this, &PlayMenu::updateTimer);
  m_timer->start(1000);

  setupLayout();
  setupPauseOverlay();
}

void PlayMenu::setupLayout()
{
  QVBoxLayout* sideLayout = new QVBoxLayout;
  sideLayout->addWidget(m_timerLabel);
  sideLayout->addWidget(m_display);
  // sideLayout->addWidget(new QLabel("Ходы:"));
  // sideLayout->addWidget(m_moveLog);
  sideLayout->addStretch();

  QVBoxLayout* centeredSideLayout = new QVBoxLayout;
  centeredSideLayout->addStretch();
  centeredSideLayout->addLayout(sideLayout);
  centeredSideLayout->addStretch();

  QHBoxLayout* mainLayout = new QHBoxLayout(this);
  // mainLayout->addWidget(m_display);
  mainLayout->addLayout(centeredSideLayout);  // <- Центрирование по вертикали

  setLayout(mainLayout);

}

void PlayMenu::setupPauseOverlay()
{
  m_pauseOverlay = new QWidget(this);
  m_pauseOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 180);");
  m_pauseOverlay->hide();

  QVBoxLayout* pauseLayout = new QVBoxLayout(m_pauseOverlay);
  QLabel* pauseTitle = new QLabel("Пауза");
  pauseTitle->setStyleSheet("font-size: 24px; color: white;");
  pauseTitle->setAlignment(Qt::AlignCenter);

  auto buttonStyle = R"(
      QPushButton {
        background-color: #2c3e50;
        border: 2px solid #a67c52;
        border-radius: 6px;
        color: white;
        padding: 6px 12px;
        font-size: 16px;
        font-weight: bold;
      }
      QPushButton:hover {
        background-color: #34495e;
        border-color: #d4a373;
      }
    )";

  m_btnContinue = new QPushButton("Продолжить");
  m_btnContinue->setStyleSheet(buttonStyle);

  m_btnRestart = new QPushButton("Начать заново");
  m_btnRestart->setStyleSheet(buttonStyle);

  m_btnExit = new QPushButton("Выход");
  m_btnExit->setStyleSheet(buttonStyle);
  m_btnExit->setObjectName(WIDGET_CHESS_GAME);

  pauseLayout->addWidget(pauseTitle);
  pauseLayout->addWidget(m_btnContinue);
  pauseLayout->addWidget(m_btnRestart);
  pauseLayout->addWidget(m_btnExit);
  pauseLayout->setAlignment(Qt::AlignCenter);

  m_pauseOverlay->setLayout(pauseLayout);
  m_pauseOverlay->resize(size());

  connect(m_btnContinue, &QPushButton::clicked, this, &PlayMenu::togglePause);
  connect(m_btnRestart, &QPushButton::clicked, this, &PlayMenu::startNewGame);
  connect(m_btnExit, &QPushButton::clicked, this, &BaseWidget::onSetWidgetClicked);
}

void PlayMenu::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) {
    togglePause();
  }
}

void PlayMenu::togglePause()
{
  m_isPaused = !m_isPaused;
  m_pauseOverlay->setVisible(m_isPaused);
  if (m_isPaused) {
    m_timer->stop();
  } else {
    m_timer->start(1000);
  }
}

void PlayMenu::updateTimer()
{
  ++m_elapsedSeconds;
  int minutes = m_elapsedSeconds / 60;
  int seconds = m_elapsedSeconds % 60;
  m_timerLabel->setText(QString("%1:%2").arg(minutes, 2, 10, QLatin1Char('0'))
                        .arg(seconds, 2, 10, QLatin1Char('0')));
}

void PlayMenu::startNewGame()
{
  m_elapsedSeconds = 0;
  m_timerLabel->setText("00:00");
  m_moveLog->clear();
  // Здесь можно добавить: очистку доски, перезапуск сцены и т.д.
  togglePause(); // Скрыть меню
}
