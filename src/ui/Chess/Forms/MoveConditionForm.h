#ifndef MOVECONDITIONFORM_H
#define MOVECONDITIONFORM_H

#include "BaseForm.h"
#include <QList>

class QComboBox;
class QVBoxLayout;

class MoveConditionForm : public BaseForm
{
    Q_OBJECT

    struct MoveConditionWidgets
    {
        QComboBox* direction;
        QComboBox* figureType;
        QComboBox* condition;
        QComboBox* event;

        MoveConditionWidgets();

        bool operator==(const MoveConditionWidgets& other) const {
            return direction == other.direction;
        }
    };

public:
    MoveConditionForm();

    QJsonObject toJson(QJsonObject data) override;

public slots:
    void updateForm() override;
    void onAddCondition();

private:
    void setup();
    QWidget* createConditionWidget();

private:
    QVBoxLayout* m_listEventWidget;
    QComboBox* m_playersList;

    QList<MoveConditionWidgets> m_listEvent;
};

#endif // MOVECONDITIONFORM_H
