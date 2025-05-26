#include "Common.h"

#include <QLayout>
#include <QWidget>
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

void clearLayout(QLayout* layout)
{
  if (!layout)
    return;

  while (QLayoutItem* item = layout->takeAt(0)) {
    if (QWidget* widget = item->widget()) {
      widget->deleteLater();  // корректно удаляет виджет
    }
    if (QLayout* childLayout = item->layout()) {
      clearLayout(childLayout);  // рекурсивно очищает вложенные layout'ы
    }
    delete item;
  }
}

void removeLastFromLayout(QLayout* layout)
{
    if (!layout || layout->count() == 0)
        return;

    QLayoutItem* item = layout->takeAt(layout->count() - 1);
    if (QWidget* widget = item->widget()) {
        widget->deleteLater();
    }
    else if (QLayout* childLayout = item->layout()) {
        clearLayout(childLayout);
        delete childLayout;
        return;
    }
    delete item;
}

