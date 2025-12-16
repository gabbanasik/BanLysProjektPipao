#include "budgetcontroller.h"

BudgetController::BudgetController(QObject *parent) : QObject{parent} {}

void BudgetController::addInfluence(double amount)
{
    // Dodaj nową kwotę
    m_totalInfluence += amount;

    // Poinformuj wszystkie podłączone widżety (dialogi, analiza) o zmianie
    emit influenceTotalChanged(m_totalInfluence);
}

void BudgetController::addExpense(double amount)
{
    // Dodaj nową kwotę
    m_totalExpense += amount;

    // Poinformuj wszystkie podłączone widżety o zmianie
    emit expenseTotalChanged(m_totalExpense);
}
