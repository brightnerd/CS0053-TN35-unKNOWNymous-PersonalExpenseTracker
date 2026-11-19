#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "expense.h"

using namespace std;

// ============================================================
// FILES
// ============================================================

const string EXPENSES_FILE = "expenses.txt";
const string INCOME_FILE = "monthly_income.txt";

// ============================================================
// CONSOLE UTILITIES
// ============================================================

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseConsole() {
    cout << "\nPress Enter to continue...";
    string line;
    getline(cin, line);
}

void showExitScreen() {
    cout << "\n\n";
    cout << "\t  Y O U   H A V E   E X I T E D   T H E   A P P!\n";
    cout << "\t  +---------------------------------------------+\n";
    cout << "\t  |          PERSONAL EXPENSE TRACKER           |\n";
    cout << "\t  |---------------------------------------------|\n";
    cout << "\t  |                  Members:                   |\n";
    cout << "\t  |           Dacunos, Mark Daniel              |\n";
    cout << "\t  |            Machica, Benedict                |\n";
    cout << "\t  |           Segunto, Bienn Kyla               |\n";
    cout << "\t  |        Villarina, Dinah Chrishalei          |\n";
    cout << "\t  +---------------------------------------------+\n\n";
    cout << "\t       T H A N K  Y O U  F O R  U S I N G!\n\n";
}

// ============================================================
// INPUT VALIDATION
// ============================================================

int getChoice(int minValue, int maxValue) {
    int choice;

    while (true) {
        cout << "Enter choice (" << minValue << "-" << maxValue << "): ";

        if (cin >> choice && choice >= minValue && choice <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "Invalid choice. Please enter a number from "
             << minValue << " to " << maxValue << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int readPositiveInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Please enter a positive whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readPositiveAmount(const string& prompt) {
    double amount;

    while (true) {
        cout << prompt;

        if (cin >> amount && isfinite(amount) && amount > 0.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return amount;
        }

        cout << "Please enter a valid positive amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readRequiredText(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (value.find_first_not_of(" \t\r\n") != string::npos) {
            return value;
        }

        cout << "This field cannot be empty.\n";
    }
}

string lowercaseText(string value) {
    for (char& character : value) {
        character = static_cast<char>(
            tolower(static_cast<unsigned char>(character))
        );
    }
    return value;
}

// ============================================================
// DATE VALIDATION
// ============================================================

bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (size_t i = 0; i < date.size(); ++i) {
        if (i != 4 && i != 7 &&
            !isdigit(static_cast<unsigned char>(date[i]))) {
            return false;
        }
    }

    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));

    if (year < 1 || month < 1 || month > 12) {
        return false;
    }

    const int daysInMonth[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int maxDay = daysInMonth[month - 1];
    bool leapYear = (year % 400 == 0) ||
                    (year % 4 == 0 && year % 100 != 0);

    if (month == 2 && leapYear) {
        maxDay = 29;
    }

    return day >= 1 && day <= maxDay;
}

bool isValidYearMonth(const string& yearMonth) {
    if (yearMonth.size() != 7 || yearMonth[4] != '-') {
        return false;
    }

    for (size_t i = 0; i < yearMonth.size(); ++i) {
        if (i != 4 &&
            !isdigit(static_cast<unsigned char>(yearMonth[i]))) {
            return false;
        }
    }

    int year = stoi(yearMonth.substr(0, 4));
    int month = stoi(yearMonth.substr(5, 2));

    return year >= 1 && month >= 1 && month <= 12;
}

string readYearMonth(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (isValidYearMonth(value)) {
            return value;
        }

        cout << "Enter a valid month in YYYY-MM format.\n";
    }
}

string readValidDate(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (isValidDate(value)) {
            return value;
        }

        cout << "Enter a valid date in YYYY-MM-DD format.\n";
    }
}

// ============================================================
// EXPENSE TYPE AND CATEGORY DISPLAY
// ============================================================

const char* categoryName(ExpenseCategory category) {
    switch (category) {
        case ExpenseCategory::Needs: return "Needs";
        case ExpenseCategory::Wants: return "Wants";
        case ExpenseCategory::Savings: return "Savings";
    }
    return "Unknown";
}

const char* expenseTypeName(ExpenseType type) {
    switch (type) {
        case ExpenseType::Monthly: return "Monthly";
        case ExpenseType::Weekly: return "Weekly";
        case ExpenseType::Daily: return "Daily";
    }
    return "Unknown";
}

void selectExpenseType(ExpenseType& selectedType) {
    clearConsole();

    cout << "\n========== SELECT EXPENSE TYPE ==========\n";
    cout << "1. Monthly Expenses\n";
    cout << "2. Weekly Expenses\n";
    cout << "3. Daily Expenses\n";
    cout << "=========================================\n";

    selectedType = static_cast<ExpenseType>(getChoice(1, 3));

    cout << "\nSelected: " << expenseTypeName(selectedType)
         << " Expenses.\n";

    pauseConsole();
}

// ============================================================
// CSV UTILITIES
// ============================================================

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

vector<string> parseCsvRow(const string& row) {
    vector<string> fields;
    string field;
    bool insideQuotes = false;

    for (size_t i = 0; i < row.size(); ++i) {
        char character = row[i];

        if (character == '"') {
            if (insideQuotes && i + 1 < row.size() &&
                row[i + 1] == '"') {
                field += '"';
                ++i;
            } else {
                insideQuotes = !insideQuotes;
            }
        } else if (character == ',' && !insideQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += character;
        }
    }

    fields.push_back(field);
    return fields;
}

// ============================================================
// EXPENSE STORAGE
// ============================================================

int findExpenseIndexById(const vector<Expense>& expenses, int id) {
    for (size_t i = 0; i < expenses.size(); ++i) {
        if (expenses[i].id == id) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int nextExpenseId(const vector<Expense>& expenses) {
    int largestId = 0;

    for (const Expense& expense : expenses) {
        largestId = max(largestId, expense.id);
    }

    return largestId + 1;
}

bool saveExpenses(const vector<Expense>& expenses,
                  const string& filename) {
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

bool loadExpenses(vector<Expense>& expenses,
                  const string& filename) {
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        return true; // No file is normal on the first run.
    }

    string row;
    getline(file, row); // Skip CSV header.

    while (getline(file, row)) {
        if (row.empty()) {
            continue;
        }

        vector<string> fields = parseCsvRow(row);

        if (fields.size() != 6) {
            continue;
        }

        try {
            Expense expense;
            expense.id = stoi(fields[0]);
            expense.description = fields[1];
            expense.amount = stod(fields[2]);
            expense.date = fields[3];

            int categoryValue = stoi(fields[4]);
            int typeValue = stoi(fields[5]);

            if (expense.id <= 0 ||
                expense.description.empty() ||
                !isfinite(expense.amount) ||
                expense.amount <= 0.0 ||
                !isValidDate(expense.date) ||
                categoryValue < 1 || categoryValue > 3 ||
                typeValue < 1 || typeValue > 3 ||
                findExpenseIndexById(expenses, expense.id) != -1) {
                continue;
            }

            expense.category =
                static_cast<ExpenseCategory>(categoryValue);
            expense.expenseType =
                static_cast<ExpenseType>(typeValue);

            expenses.push_back(expense);
        } catch (...) {
            // Ignore malformed records and continue loading.
        }
    }

    return !file.bad();
}

void displayExpense(const Expense& expense) {
    cout << "\nID: " << expense.id
         << "\nDescription: " << expense.description
         << "\nAmount: PHP " << fixed << setprecision(2)
         << expense.amount
         << "\nDate: " << expense.date
         << "\nCategory: " << categoryName(expense.category)
         << "\nExpense type: " << expenseTypeName(expense.expenseType)
         << "\n";

    cout.unsetf(ios::floatfield);
    cout << setprecision(6);
}

void addExpense(vector<Expense>& expenses, ExpenseType selectedType) {
    Expense expense;

    expense.id = nextExpenseId(expenses);
    expense.description = readRequiredText("Description: ");
    expense.amount = readPositiveAmount("Amount: PHP ");
    expense.date = readValidDate("Date (YYYY-MM-DD): ");

    cout << "\nSelect category:\n";
    cout << "1. Needs\n";
    cout << "2. Wants\n";
    cout << "3. Savings contribution\n";

    expense.category =
        static_cast<ExpenseCategory>(getChoice(1, 3));
    expense.expenseType = selectedType;

    expenses.push_back(expense);

    if (saveExpenses(expenses, EXPENSES_FILE)) {
        cout << "\nExpense added and saved with ID "
             << expense.id << ".\n";
    } else {
        expenses.pop_back();
        cout << "\nCould not save the expense. No record was added.\n";
    }
}

void viewExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses have been recorded.\n";
        return;
    }

    cout << "\n========== ALL EXPENSES ==========\n";

    for (const Expense& expense : expenses) {
        displayExpense(expense);
    }
}

void searchExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "There are no expenses to search.\n";
        return;
    }

    cout << "\nSearch by:\n";
    cout << "1. Expense ID\n";
    cout << "2. Description\n";

    int method = getChoice(1, 2);

    if (method == 1) {
        int id = readPositiveInt("Enter expense ID: ");
        int index = findExpenseIndexById(expenses, id);

        if (index == -1) {
            cout << "Expense not found.\n";
        } else {
            displayExpense(expenses[index]);
        }
        return;
    }

    string query = lowercaseText(
        readRequiredText("Enter description to search: ")
    );

    bool found = false;

    for (const Expense& expense : expenses) {
        if (lowercaseText(expense.description).find(query) != string::npos) {
            displayExpense(expense);
            found = true;
        }
    }

    if (!found) {
        cout << "No matching expenses found.\n";
    }
}

void updateExpense(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "There are no expenses to update.\n";
        return;
    }

    int id = readPositiveInt("Enter the expense ID to update: ");
    int index = findExpenseIndexById(expenses, id);

    if (index == -1) {
        cout << "Expense not found. No changes were made.\n";
        return;
    }

    cout << "\nCurrent expense:";
    displayExpense(expenses[index]);

    Expense original = expenses[index];
    Expense updated = original;

    cout << "\nEnter updated details:\n";
    updated.description = readRequiredText("Description: ");
    updated.amount = readPositiveAmount("Amount: PHP ");
    updated.date = readValidDate("Date (YYYY-MM-DD): ");

    cout << "\nCategory:\n";
    cout << "1. Needs\n2. Wants\n3. Savings contribution\n";
    updated.category =
        static_cast<ExpenseCategory>(getChoice(1, 3));

    cout << "\nExpense type:\n";
    cout << "1. Monthly\n2. Weekly\n3. Daily\n";
    updated.expenseType =
        static_cast<ExpenseType>(getChoice(1, 3));

    updated.id = original.id;
    expenses[index] = updated;

    if (saveExpenses(expenses, EXPENSES_FILE)) {
        cout << "Expense updated and saved.\n";
    } else {
        expenses[index] = original;
        cout << "Could not save the update. Original record restored.\n";
    }
}

void deleteExpense(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "There are no expenses to delete.\n";
        return;
    }

    int id = readPositiveInt("Enter the expense ID to delete: ");
    int index = findExpenseIndexById(expenses, id);

    if (index == -1) {
        cout << "Expense not found. No changes were made.\n";
        return;
    }

    cout << "\nExpense selected for deletion:";
    displayExpense(expenses[index]);

    string confirmation;
    cout << "Delete this expense? Enter Y to confirm: ";
    getline(cin, confirmation);

    if (lowercaseText(confirmation) != "y") {
        cout << "Deletion cancelled.\n";
        return;
    }

    Expense deletedExpense = expenses[index];
    expenses.erase(expenses.begin() + index);

    if (saveExpenses(expenses, EXPENSES_FILE)) {
        cout << "Expense deleted and saved.\n";
    } else {
        expenses.insert(expenses.begin() + index, deletedExpense);
        cout << "Could not save deletion. Original record restored.\n";
    }
}

// ============================================================
// MONTHLY INCOME STORAGE
// ============================================================

bool saveMonthlyIncomes(const map<string, double>& monthlyIncomes) {
    ofstream file(INCOME_FILE, ios::trunc);

    if (!file.is_open()) {
        return false;
    }

    file << setprecision(numeric_limits<double>::max_digits10);

    for (const auto& record : monthlyIncomes) {
        file << record.first << ',' << record.second << '\n';
    }

    file.close();
    return !file.fail();
}

bool loadMonthlyIncomes(map<string, double>& monthlyIncomes) {
    ifstream file(INCOME_FILE);

    if (!file.is_open()) {
        return true;
    }

    string row;

    while (getline(file, row)) {
        size_t comma = row.find(',');

        if (comma == string::npos) {
            continue;
        }

        string yearMonth = row.substr(0, comma);
        string amountText = row.substr(comma + 1);

        try {
            double amount = stod(amountText);

            if (isValidYearMonth(yearMonth) &&
                isfinite(amount) && amount > 0.0) {
                monthlyIncomes[yearMonth] = amount;
            }
        } catch (...) {
            // Ignore malformed income records.
        }
    }

    return !file.bad();
}

void setMonthlyIncome(map<string, double>& monthlyIncomes) {
    string yearMonth = readYearMonth("Enter month (YYYY-MM): ");
    double income = readPositiveAmount("Enter monthly income: PHP ");

    double previousIncome = 0.0;
    bool hadPrevious = monthlyIncomes.count(yearMonth) > 0;

    if (hadPrevious) {
        previousIncome = monthlyIncomes[yearMonth];
    }

    monthlyIncomes[yearMonth] = income;

    if (saveMonthlyIncomes(monthlyIncomes)) {
        cout << "Monthly income saved for " << yearMonth << ".\n";
    } else {
        if (hadPrevious) {
            monthlyIncomes[yearMonth] = previousIncome;
        } else {
            monthlyIncomes.erase(yearMonth);
        }
        cout << "Could not save the monthly income file.\n";
    }
}

// ============================================================
// 50/30/20 BUDGET CALCULATOR
// ============================================================

struct Budget {
    double monthlyBudget = 0.0;

    double needsBudget = 0.0;
    double wantsBudget = 0.0;
    double savingsBudget = 0.0;

    double needsSpent = 0.0;
    double wantsSpent = 0.0;
    double savingsContributed = 0.0;

    double needsRemaining = 0.0;
    double wantsRemaining = 0.0;
    double savingsRemaining = 0.0;

    double totalExpenses = 0.0;
};

Budget calculateBudget(double monthlyIncome) {
    Budget budget;

    budget.monthlyBudget = monthlyIncome;
    budget.needsBudget = monthlyIncome * 0.50;
    budget.wantsBudget = monthlyIncome * 0.30;
    budget.savingsBudget = monthlyIncome * 0.20;

    budget.needsRemaining = budget.needsBudget;
    budget.wantsRemaining = budget.wantsBudget;
    budget.savingsRemaining = budget.savingsBudget;

    return budget;
}

void updateBudgetSpending(
    Budget& budget,
    const vector<Expense>& expenses,
    const string& yearMonth
) {
    budget.needsSpent = 0.0;
    budget.wantsSpent = 0.0;
    budget.savingsContributed = 0.0;
    budget.totalExpenses = 0.0;

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

    budget.totalExpenses = budget.needsSpent + budget.wantsSpent;

    budget.needsRemaining = budget.needsBudget - budget.needsSpent;
    budget.wantsRemaining = budget.wantsBudget - budget.wantsSpent;
    budget.savingsRemaining =
        budget.savingsBudget - budget.savingsContributed;
}

void displayBudgetSummary(const Budget& budget, const string& yearMonth) {
    ios::fmtflags oldFlags = cout.flags();
    streamsize oldPrecision = cout.precision();

    cout << fixed << setprecision(2);

    cout << "\n========================================\n";
    cout << "          50/30/20 SPENDING SUMMARY\n";
    cout << "========================================\n";
    cout << "Month: " << yearMonth << '\n';
    cout << "Monthly Income:       PHP " << budget.monthlyBudget << '\n';

    cout << "\n--- Budget Allocation ---\n";
    cout << "Needs Budget (50%):   PHP " << budget.needsBudget << '\n';
    cout << "Wants Budget (30%):   PHP " << budget.wantsBudget << '\n';
    cout << "Savings Budget (20%): PHP " << budget.savingsBudget << '\n';

    cout << "\n--- Actual Spending ---\n";
    cout << "Needs Spent:          PHP " << budget.needsSpent << '\n';
    cout << "Wants Spent:          PHP " << budget.wantsSpent << '\n';
    cout << "Savings Contributed:  PHP "
         << budget.savingsContributed << '\n';

    cout << "\n--- Remaining Budget ---\n";
    cout << "Needs Remaining:      PHP " << budget.needsRemaining << '\n';
    cout << "Wants Remaining:      PHP " << budget.wantsRemaining << '\n';
    cout << "Savings Remaining:    PHP "
         << budget.savingsRemaining << '\n';

    cout << "\n----------------------------------------\n";
    cout << "Total Expenses:       PHP " << budget.totalExpenses << '\n';
    cout << "========================================\n";

    cout.flags(oldFlags);
    cout.precision(oldPrecision);
}

void showBudgetSummaryMenu(
    const vector<Expense>& expenses,
    const map<string, double>& monthlyIncomes
) {
    string yearMonth = readYearMonth(
        "Enter month for budget summary (YYYY-MM): "
    );

    auto incomeRecord = monthlyIncomes.find(yearMonth);

    if (incomeRecord == monthlyIncomes.end()) {
        cout << "No monthly income has been set for "
             << yearMonth << ".\n";
        cout << "Please set the monthly income first.\n";
        return;
    }

    Budget budget = calculateBudget(incomeRecord->second);
    updateBudgetSpending(budget, expenses, yearMonth);
    displayBudgetSummary(budget, yearMonth);
}

// ============================================================
// MENU AND GENERAL FUNCTIONS
// ============================================================

void showAbout() {
cout << "\n";
    cout << "============================================\n";
    cout << "             ABOUT THE SYSTEM               \n";
    cout << "============================================\n";

    cout << "\n          [ SYSTEM INFORMATION ]      \n";
    cout << "Personal Expense Tracker (PET) is a C++ console\n";
    cout << "application that helps users record, organize,\n";
    cout << "and monitor their personal expenses and income.\n";

    cout << "\n       [ FREQUENTLY ASKED QUESTIONS ]      \n";

    cout << "\n1. What is the 50/30/20 Budgeting Rule?\n";
    cout << "   Needs   - 50% for essential expenses.\n";
    cout << "   Wants   - 30% for non-essential expenses.\n";
    cout << "   Savings - 20% for future financial goals.\n";

    cout << "\n2. What are the available expense types?\n";
    cout << "   Monthly, Weekly, and Daily.\n";

    cout << "\n3. Can I edit or delete an expense?\n";
    cout << "   Yes! You can search, update, and delete\n";
    cout << "   existing expense records.\n";

    cout << "\n4. Will my records be saved?\n";
    cout << "   Yes! Records are stored locally in text files.\n";

    cout << "\n5. Does PET connect to my bank account?\n";
    cout << "   No. All transactions must be entered manually.\n";

    cout << "\n============================================\n";
    cout << "             QUICK USER TUTORIAL             \n";
    cout << "============================================\n";

    cout << "\n     [ HOW TO USE THE 11 MENU CHOICES ]\n";

    cout << "\n[1] Select Type of Expense\n";
    cout << "    Choose Monthly, Weekly, or Daily.\n";
    cout << "    Do this before adding an expense.\n";

    cout << "\n[2] Set Monthly Income\n";
    cout << "    Enter your monthly income and the month\n";
    cout << "    it belongs to (YYYY-MM).\n";

    cout << "\n[3] Add an Expense\n";
    cout << "    Enter the description, amount, date,\n";
    cout << "    and budget category (Needs, Wants, Savings).\n";

    cout << "\n[4] View All Expenses\n";
    cout << "    Display all recorded expense transactions.\n";

    cout << "\n[5] Search an Expense\n";
    cout << "    Find an expense using its ID or description.\n";

    cout << "\n[6] Update an Expense\n";
    cout << "    Select an existing expense ID and modify\n";
    cout << "    its information.\n";

    cout << "\n[7] Delete an Expense\n";
    cout << "    Select an expense ID and confirm deletion.\n";

    cout << "\n[8] Show Spending Summary\n";
    cout << "    Enter the month you want to review.\n";
    cout << "    Check your budget allocation, actual spending,\n";
    cout << "    and remaining balance.\n";

    cout << "\n[9] Save Data\n";
    cout << "    Save your expense records and monthly income.\n";

    cout << "\n[10] About the System\n";
    cout << "     View system information and this tutorial.\n";

    cout << "\n[0] Exit\n";
    cout << "    Save outstanding changes and close PET.\n";

    cout << "\n============================================\n";
    cout << "             IMPORTANT REMINDERS             \n";
    cout << "============================================\n";
    cout << "- Enter valid amounts and dates.\n";
    cout << "- Use YYYY-MM-DD for expense dates.\n";
    cout << "- Use YYYY-MM for monthly income.\n";
    cout << "- Always check your spending summary.\n";
    cout << "- Save your data before exiting.\n";

    cout << "\n============================================\n";
    cout << "       THANK YOU FOR USING PET! <3           \n";
    cout << "============================================\n";
}

void showMenu() {
    cout << "\n====================================\n";
    cout << "       PERSONAL EXPENSE TRACKER\n";
    cout << "====================================\n";
    cout << "1. Select Type of Expense\n";
    cout << "2. Set Monthly Income\n";
    cout << "3. Add an Expense\n";
    cout << "4. View All Expenses\n";
    cout << "5. Search an Expense\n";
    cout << "6. Update an Expense\n";
    cout << "7. Delete an Expense\n";
    cout << "8. Show Spending Summary\n";
    cout << "9. Save Data\n";
    cout << "10. About the System\n";
    cout << "0. Exit\n";
    cout << "====================================\n";
}

bool saveAllData(
    const vector<Expense>& expenses,
    const map<string, double>& monthlyIncomes
) {
    bool expensesSaved = saveExpenses(expenses, EXPENSES_FILE);
    bool incomesSaved = saveMonthlyIncomes(monthlyIncomes);

    return expensesSaved && incomesSaved;
}

// ============================================================
// MAIN PROGRAM
// ============================================================

int main() {
    vector<Expense> expenses;
    map<string, double> monthlyIncomes;

    // Monthly is the default expense type until the user selects another.
    ExpenseType selectedExpenseType = ExpenseType::Monthly;

    if (!loadExpenses(expenses, EXPENSES_FILE)) {
        cout << "Warning: Could not completely read the expense file.\n";
    }

    if (!loadMonthlyIncomes(monthlyIncomes)) {
        cout << "Warning: Could not completely read the income file.\n";
    }

    bool running = true;

    while (running) {
        clearConsole();
        showMenu();

        int choice = getChoice(0, 10);

        switch (choice) {
            case 1:
                selectExpenseType(selectedExpenseType);
                break;

            case 2:
                clearConsole();
                setMonthlyIncome(monthlyIncomes);
                pauseConsole();
                break;

            case 3:
                clearConsole();
                cout << "\n========== ADD EXPENSE ==========\n";
                cout << "Selected expense type: "
                     << expenseTypeName(selectedExpenseType) << "\n\n";
                addExpense(expenses, selectedExpenseType);
                pauseConsole();
                break;

            case 4:
                clearConsole();
                viewExpenses(expenses);
                pauseConsole();
                break;

            case 5:
                clearConsole();
                searchExpenses(expenses);
                pauseConsole();
                break;

            case 6:
                clearConsole();
                updateExpense(expenses);
                pauseConsole();
                break;

            case 7:
                clearConsole();
                deleteExpense(expenses);
                pauseConsole();
                break;

            case 8:
                clearConsole();
                showBudgetSummaryMenu(expenses, monthlyIncomes);
                pauseConsole();
                break;

            case 9:
                clearConsole();
                if (saveAllData(expenses, monthlyIncomes)) {
                    cout << "All data saved successfully.\n";
                } else {
                    cout << "There was a problem saving one or more files.\n";
                }
                pauseConsole();
                break;

            case 10:
                clearConsole();
                showAbout();
                pauseConsole();
                break;

            case 0:
                clearConsole();
                if (!saveAllData(expenses, monthlyIncomes)) {
                    cout << "Warning: Some data could not be saved.\n";
                }
                showExitScreen();
                running = false;
                break;
        }
    }

    return 0;
}
