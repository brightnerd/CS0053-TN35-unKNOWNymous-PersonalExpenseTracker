#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>

using namespace std;

enum class ExpenseType {
    Monthly = 1,
    Weekly = 2,
    Daily = 3
};

enum class ExpenseCategory {
    Needs = 1,
    Wants = 2,
    Savings = 3
};

struct Expense {
    int id = 0;
    string description;
    double amount = 0.0;
    string date;
    ExpenseCategory category = ExpenseCategory::Needs;
    ExpenseType expenseType = ExpenseType::Monthly;
};

bool saveExpenses(
    const vector<Expense>& expenses,
    const string& filename = "expenses.txt"
);

#endif