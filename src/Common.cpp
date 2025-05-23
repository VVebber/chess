#include "Common.h"

#include <QJsonArray>
#include <QPushButton>

QPushButton* setupBtnIcon(const QString& linkImg)
{
  QPixmap pixmap(linkImg);
  QIcon icon(pixmap);

  QPushButton* btn = new QPushButton();
  btn->setIcon(icon);

  return btn;
}

int findIndexInJsonArray(const QJsonArray& array, const QJsonValue& value) {
    for (int i = 0; i < array.size(); ++i) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}
