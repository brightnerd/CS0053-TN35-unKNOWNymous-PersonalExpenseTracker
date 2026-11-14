#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

#include "expense.h"

using namespace std;

// Budget allocation
struct Budget {
    double monthlyBudget;

    double needsBudget;
    double wantsBudget;
    double savingsBudget;

    // Spending and contributions
    double needsSpent;
    double wantsSpent;
    double savingsContributed;

    // remaining budget
    double needsRemaining;
    double wantsRemaining;
    double savingsRemaining;

    // Total expenses
    double totalExpenses;
};

// 50/30/20 budget allocation
Budget calculateBudget(double monthlyIncome) {
    Budget budget;

    budget.monthlyBudget = monthlyIncome;

    budget.needsBudget = monthlyIncome * 0.5; // 50% for needs
    budget.wantsBudget = monthlyIncome * 0.3; // 30% for wants
    budget.savingsBudget = monthlyIncome * 0.2; // 20% for savings
    
    budget.needsSpent = 0.0;
    budget.wantsSpent = 0.0;
    budget.savingsContributed = 0.0;

    budget.needsRemaining = budget.needsBudget;
    budget.wantsRemaining = budget.wantsBudget;
    budget.savingsRemaining = budget.savingsBudget;

    budget.totalExpenses = 0.0;
    
    return budget;
}

void updateBudgetSpending(
    Budget& budget,
    const vector<Expense>& expenses,
    const string& yearMonth
) {
    // Reset totals before recalculating
    budget.needsSpent = 0.0;
    budget.wantsSpent = 0.0;
    budget.savingsContributed = 0.0;
    budget.totalExpenses = 0.0;

    // Check only expenses belonging to the selected month
    for (const Expense& expense : expenses) {
        if (expense.date.size() < 7 ||
            expense.date.compare(0, 7, yearMonth) != 0) {
            continue;
        }

        switch (expense.category) {
            case ExpenseCategory::Needs:
                budget.needsSpent += expense.amount;
                break;

            case ExpenseCategory::Wants:
                budget.wantsSpent += expense.amount;
                break;

            case ExpenseCategory::Savings:
                budget.savingsContributed += expense.amount;
                break;
        }
    }

    // Total ordinary expenses exclude savings contributions
    budget.totalExpenses = budget.needsSpent + budget.wantsSpent;

    // Calculate remaining budget
    budget.needsRemaining = budget.needsBudget - budget.needsSpent;
    budget.wantsRemaining = budget.wantsBudget - budget.wantsSpent;
    budget.savingsRemaining = budget.savingsBudget - budget.savingsContributed;
}

// Displays monthly budget summary
void displayBudgetSummary(const Budget& budget, const string& yearMonth) {
    // Displays monetary values with two decimal places
    cout << fixed << setprecision(2);

    cout << "\n========================================\n";
    cout << "     MONTHLY BUDGET SUMMARY\n";
    cout << "========================================\n";

    cout << "Month: " << yearMonth << "\n";
    cout << "Total Monthly Budget: PHP" << budget.monthlyBudget << "\n";

    cout << "\n--- Budget Allocation ---\n";
    cout << "Needs Budget (50%):   PHP " << budget.needsBudget << "\n";
    cout << "Wants Budget (30%):   PHP " << budget.wantsBudget << "\n";
    cout << "Savings Budget (20%): PHP " << budget.savingsBudget << "\n";

    cout << "\n--- Actual Spending ---\n";
    cout << "Needs Spent:          PHP " << budget.needsSpent << "\n";
    cout << "Wants Spent:          PHP " << budget.wantsSpent << "\n";
    cout << "Savings Contributed:  PHP " << budget.savingsContributed << "\n";

    cout << "\n--- Remaining Budget ---\n";
    cout << "Needs Remaining:      PHP " << budget.needsRemaining << "\n";
    cout << "Wants Remaining:      PHP " << budget.wantsRemaining << "\n";
    cout << "Savings Remaining:    PHP " << budget.savingsRemaining << "\n";

    cout << "\n----------------------------------------\n";
    cout << "Total Expenses:       PHP " << budget.totalExpenses << "\n";
    cout << "========================================\n";

    // Restores default stream formatting
    cout.unsetf(ios::floatfield);
    cout << setprecision(6);
}

// Quote CSV text and escape embedded quotation marks.
string quoteCsvField(const string& value) {
    string quoted = "\"";
    for (char character : value) {
        if (character == '"') {
            quoted += '"';
        }
        quoted += character;
    }
    quoted += '"';
    return quoted;
}

// Save the current records. Call after successful add/update/delete operations.
bool saveExpenses(const vector<Expense>& expenses, const string& filename) {
    ofstream file(filename, ios::binary | ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    file << "id,description,amount,date,category,expenseType\n";
    file << setprecision(numeric_limits<double>::max_digits10);

    for (const Expense& expense : expenses) {
        file << expense.id << ','
             << quoteCsvField(expense.description) << ','
             << expense.amount << ','
             << quoteCsvField(expense.date) << ','
             << static_cast<int>(expense.category) << ','
             << static_cast<int>(expense.expenseType) << '\n';
    }

    file.close();
    return !file.fail();
}

// Clear console
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pause until Enter is pressed
void pauseConsole() {
    cout << "\nPress Enter to continue...";
    string line;
    getline(cin, line);
}

// Get and validate user choice
int getChoice(int min, int max) {
    int choice;

    while (true) {
        cout << "Choose an option (" << min << "-" << max << "): ";

        if (cin >> choice && choice >= min && choice <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "Invalid choice. Enter a number from "
             << min << " to " << max << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

 // Display main menu
void showMenu() {
    cout << "\n====================================\n";
    cout << "     PERSONAL EXPENSE TRACKER\n";
    cout << "====================================\n";
    cout << "1. Select Type of Expense\n";
    cout << "2. Add an Expense\n";
    cout << "3. View All Expenses\n";
    cout << "4. Update an Expense\n";
    cout << "5. Delete an Expense\n";
    cout << "6. Show Spending Summary\n";
    cout << "7. About the System\n";
    cout << "8. Exit\n";
    cout << "====================================\n";
    cout << "Enter your choice: ";
}

// Select expense type
void selectExpense(ExpenseType& selectedExpenseType) {
    clearConsole();

    cout << "\n=== Select Expense Type ===\n";
    cout << "1. Monthly Expenses\n";
    cout << "2. Weekly Expenses\n";
    cout << "3. Daily Expenses\n";

    selectedExpenseType = static_cast<ExpenseType>(getChoice(1, 3));

    switch (selectedExpenseType) {
        case ExpenseType::Monthly:
            cout << "\nYou selected Monthly Expenses.\n";
            break;
        case ExpenseType::Weekly:
            cout << "\nYou selected Weekly Expenses.\n";
            break;
        case ExpenseType::Daily:
            cout << "\nYou selected Daily Expenses.\n";
            break;
    }

    pauseConsole();
}


// Choice no. 8: Exit the application  
void showExitScreen() {
    cout << "\n\n";
    cout << "\t  Y O U   H A V E   E X I T E D   T H E   A P P!\n";
    cout << "\t  +---------------------------------------------+\n";
    cout << "\t  |          PERSONAL EXPENSE TRACKER           |\n";
    cout << "\t  |---------------------------------------------|\n";
    cout << "\t  |                   Members:                  |\n";
    cout << "\t  |             Dacunos, Mark Daniel            |\n";
    cout << "\t  |              Machica, Benedict              |\n";
    cout << "\t  |             Segunto, Bienn Kyla             |\n";
    cout << "\t  |         Villarina, Dinah Chrishalei         |\n";
    cout << "\t  +---------------------------------------------+\n\n";
    cout << "\t      T H A N K  Y O U   F O R   U S I N G!!     \n\n";
}


 // Main program
int main() {
    // Pass this collection by reference to the feature functions.
    vector<Expense> expenses;
    ExpenseType selectedExpenseType = ExpenseType::Monthly;
    bool running = true;

    while (running) {
        clearConsole();
        showMenu();

        int choice = getChoice(1, 8);

        switch (choice) {
            case 1:
                selectExpense(selectedExpenseType);
                break;

            case 2:
                clearConsole();
                cout << "\nAdd Expense will be implemented next.\n";
                pauseConsole();
                break;

            case 3:
                clearConsole();
                cout << "\nView All Expenses will be implemented next.\n";
                pauseConsole();
                break;

            case 4:
                clearConsole();
                cout << "\nUpdate Expense will be implemented next.\n";
                pauseConsole();
                break;

            case 5:
                clearConsole();
                cout << "\nDelete Expense will be implemented next.\n";
                pauseConsole();
                break;

            case 6:
                clearConsole();
                cout << "\nSpending Summary will be implemented next.\n";
                pauseConsole();
                break;

            case 7:
                clearConsole();
                cout << "\nAbout the System will be implemented next.\n";
                pauseConsole();
                break;

            case 8:
                clearConsole();
                showExitScreen();
                running = false;
                break;
        }
    }

    return 0;
}