#ifndef MOVE_H
#define MOVE_H

#include <QColor>

struct Move {
    int x;
    int y;
    QColor color;
    QString direction;
};

#endif // MOVE_H
