#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

// Values match the existing Select Expense Type menu.
enum class ExpenseType { Monthly = 1, Weekly = 2, Daily = 3 };

// Categories used by the group's 50/30/20 budget calculator.
enum class ExpenseCategory { Needs = 1, Wants = 2, Savings = 3 };

// One record. Add/update and file-loading functions must validate its values.
struct Expense {
    int id = 0;              // Assign a unique positive ID when adding.
    std::string description; // Required, for example "Lunch".
    double amount = 0.0; // Must be positive; matches Budget's double fields.
    std::string date;    // Required calendar date in YYYY-MM-DD format.
    ExpenseCategory category = ExpenseCategory::Needs;
    ExpenseType expenseType = ExpenseType::Monthly;
};

// Writes the complete collection to CSV; returns false if opening/writing fails.
bool saveExpenses(const std::vector<Expense>& expenses,
                  const std::string& filename = "expenses.txt");

#endif
