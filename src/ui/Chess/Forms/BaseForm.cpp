#include "BaseForm.h"

int BaseForm::m_countPlayers = 0;

BaseForm::BaseForm()
{

}

BaseForm::~BaseForm()
{

}

void BaseForm::setCountPlayer(int count)
{
  m_countPlayers = count;
}

