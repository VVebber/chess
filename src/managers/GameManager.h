#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QString>
#include <QStringList>

class Figure;

class GameManager {
public:
    static GameManager& instance();

    bool isCheckShah(Figure* figure);
    bool isCheckFromFigure(Figure* figure,   QList<Figure*> m_figures);
    void findFriendlyFiguresInCheckCells(const QList<QString>& checkCells, Figure* king, const QList<Figure*>& allFigures);

    bool isCurrentPlayer(const QString& moveKey) const;
    void nextTurn();

    void initPlayer(const int& player);
    void clear();

private:
    GameManager();
    QList<Figure*> m_friendFigures;

    QStringList m_players;
    int m_countMove = 0;
};


#endif // GAMEMANAGER_H
