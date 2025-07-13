#ifndef PLAYMENU_H
#define PLAYMENU_H

#include <QWidget>
#include <QGraphicsView>
#include <QTimer>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "../base/BaseWidget.h"

class PlayMenu : public BaseWidget
{
    Q_OBJECT

public:
    PlayMenu(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateTimer();
    void togglePause();
    void startNewGame();

private:
    void setupLayout();
    void setupPauseOverlay();

    QGraphicsView* m_display;
    QTimer* m_timer;
    QLabel* m_timerLabel;
    QListWidget* m_moveLog;

    QWidget* m_pauseOverlay;
    QPushButton* m_btnContinue;
    QPushButton* m_btnRestart;
    QPushButton* m_btnExit;

    int m_elapsedSeconds;
    bool m_isPaused;
};

#endif // PLAYMENU_H
