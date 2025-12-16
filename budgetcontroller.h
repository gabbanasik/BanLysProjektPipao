#ifndef BUDGETCONTROLLER_H
#define BUDGETCONTROLLER_H

#include <QObject>

class BudgetController : public QObject
{
    Q_OBJECT
public:
    explicit BudgetController(QObject *parent = nullptr);

    // Metody do modyfikacji sum
    void addInfluence(double amount);
    void addExpense(double amount);

    // Metody do pobierania aktualnych sum
    double getTotalInfluence() const { return m_totalInfluence; }
    double getTotalExpense() const { return m_totalExpense; }

signals:
    // Sygnały wysyłane po zmianie sumy. UI nasłuchuje na te sygnały.
    void influenceTotalChanged(double newTotal);
    void expenseTotalChanged(double newTotal);

private:
    double m_totalInfluence = 0.0;
    double m_totalExpense = 0.0;
};

#endif // BUDGETCONTROLLER_H
