#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

// Values match the existing Select Expense Type menu.
enum class ExpenseType {
    Monthly = 1,
    Weekly = 2,
    Daily = 3
};

// Categories used by the group's 50/30/20 budget calculator.
enum class ExpenseCategory {
    Needs = 1,
    Wants = 2,
    Savings = 3
};

// Shared expense structure.
struct Expense {
    int id = 0;
    std::string description;
    double amount = 0.0;
    std::string date;

    ExpenseCategory category = ExpenseCategory::Needs;
    ExpenseType expenseType = ExpenseType::Monthly;
};

// Saves the complete collection of expenses.
bool saveExpenses(
    const std::vector<Expense>& expenses,
    const std::string& filename = "expenses.txt"
);

#endif
