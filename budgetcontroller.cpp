#include "budgetcontroller.h"

BudgetController::BudgetController(QObject *parent) : QObject{parent} {}

void BudgetController::addInfluence(double amount)
{
    m_totalInfluence += amount;
    emit influenceTotalChanged(m_totalInfluence);
}

void BudgetController::addExpense(double amount)
{
    m_totalExpense += amount;
    emit expenseTotalChanged(m_totalExpense);
}
