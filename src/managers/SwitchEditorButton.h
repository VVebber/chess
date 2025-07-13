#ifndef SWITCHEDITORBUTTON_H
#define SWITCHEDITORBUTTON_H

#include <QObject>

class QPushButton;
class QButtonGroup;
class QAbstractButton;

class SwitchEditorButton : public QObject
{
  Q_OBJECT

public:
  static SwitchEditorButton& instance();

  void addButton(QPushButton* btn, int id = -1);
  void removeButton(QPushButton* btn);
  void clear();
  bool contains(QPushButton* btn) const;
  QList<QAbstractButton*> buttons() const;

  QButtonGroup* buttonGroup() const;

  QAbstractButton* button(int id) const;
  QPushButton* buttonAsPushButton(int id) const;

  int checkedId() const;

signals:
  void buttonAdded(QPushButton* btn);
  void buttonRemoved(QPushButton* btn);

private:
  explicit SwitchEditorButton();
  Q_DISABLE_COPY(SwitchEditorButton)

  QButtonGroup* m_group;
};

#endif // SWITCHEDITORBUTTON_H
