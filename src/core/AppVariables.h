// AppVariables.h
#ifndef APPVARIABLES_H
#define APPVARIABLES_H

#include <QString>
#include <QWidget>
#include <QVariant>
#include <QMultiMap>

class AppVariables
{

public:
  AppVariables();

  void addVariabel(const QString &key, const QVariant &value) {
    m_variables.insert(key, value);
  }

  void addWidget(const QString &key, QWidget* value) {
    m_widgets.insert(key, value);
  }

  QVariant getVariabel(const QString &key, const QVariant &defaultValue = QVariant()) const {
    return m_variables.value(key, defaultValue);
  }

  QWidget* getWidget(const QString &key, QWidget* defaultWidget = nullptr) const {
      return m_widgets.value(key, defaultWidget);
  }

  bool containsVariabel(const QString &key) const {
    return m_variables.contains(key);
  }

  bool containsWidget(const QString &key) const {
    return m_widgets.contains(key);
  }

  void removeVariabel(const QString &key) {
    m_variables.remove(key);
  }

  void removeWidget(const QString &key) {
    m_widgets.remove(key);
  }

  void clearVariabel() {
    m_variables.clear();
  }

  void clearWidget() {
    m_widgets.clear();
  }

private:
  QMultiMap<QString, QVariant> m_variables;
  QMultiMap<QString, QWidget*> m_widgets;
};

#endif // APPVARIABLES_H
