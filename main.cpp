#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
<<<<<<< Updated upstream
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
=======
#include <map>
#include <string>
#include <vector>
>>>>>>> Stashed changes

#include "expense.h"

using namespace std;

<<<<<<< Updated upstream
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
    cout << "        SPENDING SUMMARY\n";
    cout << "========================================\n";

    cout << "Month: " << yearMonth << "\n";
    cout << "Monthly Income:       PHP " << budget.monthlyBudget << "\n";

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
=======
const string EXPENSES_FILE = "expenses.txt";
const string INCOME_FILE = "monthly_income.txt";
>>>>>>> Stashed changes

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

<<<<<<< Updated upstream
// Sets or updates income for the selected month
void setMonthlyIncome(map<string, double>& monthlyIncomes) {

    string yearMonth;

    cout << "\nEnter the month (YYYY-MM): ";
    getline(cin, yearMonth);

    // Validate month format
    bool validMonth = yearMonth.size() == 7 &&
                      yearMonth[4] == '-';

    if (validMonth) {
        for (int i = 0; i < 7; i++) {
            if (i != 4 && (yearMonth[i] < '0' ||
                           yearMonth[i] > '9')) {
                validMonth = false;
                break;
            }
        }
    }

    if (validMonth) {
        int month = stoi(yearMonth.substr(5, 2));

        if (month < 1 || month > 12) {
            validMonth = false;
        }
    }

    // Stop if the month is invalid
    if (!validMonth) {
        cout << "Invalid month. Use YYYY-MM format.\n";
        return;
    }

    double income;

    cout << "Enter monthly income: PHP ";
    
    if (!(cin >> income) || income <= 0) {
        cout << "Invalid income. Please enter a positive number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    monthlyIncomes[yearMonth] = income;

    cout << "Monthly income for " << yearMonth 
         << " has been saved: PHP " 
         << fixed << setprecision(2) << income << "\n";

    cout.unsetf(ios::floatfield);
    cout << setprecision(6);
}

// Handles the monthly budget summary menu
void showBudgetSummaryMenu(
    const vector<Expense>& expenses,
    const map<string, double>& monthlyIncomes
) {
    string yearMonth;

    while (true) {
        cout << "\nEnter the month for the budget summary (YYYY-MM): ";
        getline(cin, yearMonth);

        bool validMonth = yearMonth.size() == 7 &&
                          yearMonth[4] == '-';

        if (validMonth) {
            for (int i = 0; i < 7; i++) {
                if (i != 4 && (yearMonth[i] < '0' ||
                               yearMonth[i] > '9')) {
                    validMonth = false;
                    break;
                }
            }
        }

        if (validMonth) {
            int month = stoi(yearMonth.substr(5, 2));

            if (month >= 1 && month <= 12) {
                break;
            }
        }

        cout << "Invalid month. Use YYYY-MM format.\n";
    }

    // Retrieve the income saved for the selected month
    auto incomeRecord = monthlyIncomes.find(yearMonth);

    if (incomeRecord == monthlyIncomes.end()) {
        cout << "\nNo monthly income has been set for "
             << yearMonth << ".\n";
        cout << "Please set the monthly income first.\n";
        pauseConsole();
        return;
    }

    double monthlyIncome = incomeRecord->second;

    // Calculate and display budget summary
    Budget budget = calculateBudget(monthlyIncome);

    updateBudgetSpending(budget, expenses, yearMonth);

    displayBudgetSummary(budget, yearMonth);

    pauseConsole();
}

// Get and validate user choice
int getChoice(int min, int max) {
=======
// Get and validate a menu choice
int getChoice(int minValue, int maxValue) {
>>>>>>> Stashed changes
    int choice;

    while (true) {
        cout << "Enter choice (" << minValue << "-" << maxValue << "): ";

        if (cin >> choice &&
            choice >= minValue &&
            choice <= maxValue) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "Invalid choice. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a positive integer
int readPositiveInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;

        if (cin >> value && value > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Enter a positive whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read a positive amount
double readPositiveAmount(const string& prompt) {
    double amount;

    while (true) {
        cout << prompt;

        if (cin >> amount && isfinite(amount) && amount > 0.0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return amount;
        }

        cout << "Enter a positive amount.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Read non-empty text
string readRequiredText(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (!value.empty()) {
            return value;
        }

        cout << "This field cannot be empty.\n";
    }
}

// Validate a calendar date in YYYY-MM-DD format
bool isValidDate(const string& date) {
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
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

// Validate a month in YYYY-MM format
bool isValidYearMonth(const string& yearMonth) {
    if (yearMonth.size() != 7 || yearMonth[4] != '-') {
        return false;
    }

    for (int i = 0; i < 7; ++i) {
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
    string yearMonth;

    while (true) {
        cout << prompt;
        getline(cin, yearMonth);

        if (isValidYearMonth(yearMonth)) {
            return yearMonth;
        }

        cout << "Enter a valid month in YYYY-MM format.\n";
    }
}

string readValidDate(const string& prompt) {
    string date;

    while (true) {
        cout << prompt;
        getline(cin, date);

        if (isValidDate(date)) {
            return date;
        }

        cout << "Enter a valid date in YYYY-MM-DD format.\n";
    }
}

string lowercaseText(string text) {
    for (char& character : text) {
        character = static_cast<char>(
            tolower(static_cast<unsigned char>(character))
        );
    }

    return text;
}

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

int findExpenseIndexById(const vector<Expense>& expenses, int id) {
    for (size_t i = 0; i < expenses.size(); ++i) {
        if (expenses[i].id == id) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void displayExpense(const Expense& expense) {
    cout << "\nID: " << expense.id
         << "\nDescription: " << expense.description
         << "\nAmount: PHP " << fixed << setprecision(2) << expense.amount
         << "\nDate: " << expense.date
         << "\nCategory: " << categoryName(expense.category)
         << "\nExpense type: " << expenseTypeName(expense.expenseType)
         << "\n";

    cout.unsetf(ios::floatfield);
    cout << setprecision(6);
}

// Quote CSV text and escape embedded quotation marks
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

// Split one CSV row while respecting quoted fields
vector<string> parseCsvRow(const string& row) {
    vector<string> fields;
    string field;
    bool insideQuotes = false;

    for (size_t i = 0; i < row.size(); ++i) {
        char character = row[i];

        if (character == '"') {
            if (insideQuotes &&
                i + 1 < row.size() &&
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

// Save the complete expense list
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

// Load saved expenses. A missing file is okay on the first run.
bool loadExpenses(vector<Expense>& expenses, const string& filename) {
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        return true;
    }

    string row;
    getline(file, row); // Skip the CSV header.

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
            // Skip malformed rows.
        }
    }

    return !file.bad();
}

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
                isfinite(amount) &&
                amount > 0.0) {
                monthlyIncomes[yearMonth] = amount;
            }
        } catch (...) {
            // Skip malformed rows.
        }
    }

    return !file.bad();
}

void setMonthlyIncome(map<string, double>& monthlyIncomes) {
    string yearMonth = readYearMonth("Enter month (YYYY-MM): ");
    double income = readPositiveAmount("Enter monthly income: PHP ");

    monthlyIncomes[yearMonth] = income;

    if (saveMonthlyIncomes(monthlyIncomes)) {
        cout << "Income saved for " << yearMonth << ".\n";
    } else {
        cout << "Could not save the income file.\n";
    }
}

void selectExpenseType(ExpenseType& selectedType) {
    cout << "\nSelect expense type:\n";
    cout << "1. Monthly\n";
    cout << "2. Weekly\n";
    cout << "3. Daily\n";

    selectedType = static_cast<ExpenseType>(getChoice(1, 3));

    cout << "Selected: " << expenseTypeName(selectedType) << "\n";
}

int nextExpenseId(const vector<Expense>& expenses) {
    int largestId = 0;

    for (const Expense& expense : expenses) {
        if (expense.id > largestId) {
            largestId = expense.id;
        }
    }

    return largestId + 1;
}

void addExpense(
    vector<Expense>& expenses,
    ExpenseType selectedType
) {
    Expense expense;
    expense.id = nextExpenseId(expenses);
    expense.description = readRequiredText("Description: ");
    expense.amount = readPositiveAmount("Amount: PHP ");
    expense.date = readValidDate("Date (YYYY-MM-DD): ");

    cout << "\nCategory:\n";
    cout << "1. Needs\n";
    cout << "2. Wants\n";
    cout << "3. Savings contribution\n";

    expense.category =
        static_cast<ExpenseCategory>(getChoice(1, 3));
    expense.expenseType = selectedType;

    expenses.push_back(expense);

    if (saveExpenses(expenses, EXPENSES_FILE)) {
        cout << "Expense added and saved with ID "
             << expense.id << ".\n";
    } else {
        expenses.pop_back();
        cout << "Could not save the expense. It was not added.\n";
    }
}

void viewExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "No expenses have been recorded.\n";
        return;
    }

    cout << "\n=== All Expenses ===\n";

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
    cout << "1. ID\n";
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

    string query = readRequiredText("Enter description text: ");
    string searchText = lowercaseText(query);
    bool found = false;

    for (const Expense& expense : expenses) {
        if (lowercaseText(expense.description).find(searchText)
            != string::npos) {
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

    int id = readPositiveInt("Enter the ID to update: ");
    int index = findExpenseIndexById(expenses, id);

    if (index == -1) {
        cout << "Expense not found. No changes were made.\n";
        return;
    }

    cout << "\nCurrent expense:";
    displayExpense(expenses[index]);

    Expense original = expenses[index];
    Expense updated = original;

    cout << "\nEnter the updated details:\n";
    updated.description = readRequiredText("Description: ");
    updated.amount = readPositiveAmount("Amount: PHP ");
    updated.date = readValidDate("Date (YYYY-MM-DD): ");

    cout << "\nCategory:\n";
    cout << "1. Needs\n";
    cout << "2. Wants\n";
    cout << "3. Savings contribution\n";

    updated.category =
        static_cast<ExpenseCategory>(getChoice(1, 3));

    cout << "\nExpense type:\n";
    cout << "1. Monthly\n";
    cout << "2. Weekly\n";
    cout << "3. Daily\n";

    updated.expenseType =
        static_cast<ExpenseType>(getChoice(1, 3));

    updated.id = original.id;
    expenses[index] = updated;

    if (saveExpenses(expenses, EXPENSES_FILE)) {
        cout << "Expense updated and saved.\n";
    } else {
        expenses[index] = original;
        cout << "Could not save the update. The original record was restored.\n";
    }
}

void deleteExpense(vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "There are no expenses to delete.\n";
        return;
    }

    int id = readPositiveInt("Enter the ID to delete: ");
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
        cout << "Could not save the deletion. The record was restored.\n";
    }
}

void showBudgetSummary(
    const vector<Expense>& expenses,
    const map<string, double>& monthlyIncomes
) {
    string yearMonth = readYearMonth("Enter month for summary (YYYY-MM): ");

    auto incomeRecord = monthlyIncomes.find(yearMonth);

    if (incomeRecord == monthlyIncomes.end()) {
        cout << "No income is saved for " << yearMonth
             << ". Set the monthly income first.\n";
        return;
    }

    double income = incomeRecord->second;
    double needsSpent = 0.0;
    double wantsSpent = 0.0;
    double savingsContributed = 0.0;

    for (const Expense& expense : expenses) {
        if (expense.date.substr(0, 7) != yearMonth) {
            continue;
        }

        switch (expense.category) {
            case ExpenseCategory::Needs:
                needsSpent += expense.amount;
                break;
            case ExpenseCategory::Wants:
                wantsSpent += expense.amount;
                break;
            case ExpenseCategory::Savings:
                savingsContributed += expense.amount;
                break;
        }
    }

    ios::fmtflags oldFlags = cout.flags();
    streamsize oldPrecision = cout.precision();

    cout << fixed << setprecision(2);
    cout << "\n=== 50/30/20 Budget Summary: " << yearMonth << " ===\n";
    cout << "Monthly income:       PHP " << income << "\n";
    cout << "Needs budget (50%):   PHP " << income * 0.50 << "\n";
    cout << "Needs spent:          PHP " << needsSpent << "\n";
    cout << "Needs remaining:      PHP " << income * 0.50 - needsSpent << "\n";
    cout << "Wants budget (30%):   PHP " << income * 0.30 << "\n";
    cout << "Wants spent:          PHP " << wantsSpent << "\n";
    cout << "Wants remaining:      PHP " << income * 0.30 - wantsSpent << "\n";
    cout << "Savings target (20%): PHP " << income * 0.20 << "\n";
    cout << "Savings contributed:  PHP " << savingsContributed << "\n";
    cout << "Savings remaining:    PHP "
         << income * 0.20 - savingsContributed << "\n";
    cout << "Total expenses:       PHP " << needsSpent + wantsSpent << "\n";

    cout.flags(oldFlags);
    cout.precision(oldPrecision);
}

void saveAllData(
    const vector<Expense>& expenses,
    const map<string, double>& monthlyIncomes
) {
    bool expensesSaved = saveExpenses(expenses, EXPENSES_FILE);
    bool incomesSaved = saveMonthlyIncomes(monthlyIncomes);

    if (expensesSaved && incomesSaved) {
        cout << "All data saved.\n";
    } else {
        cout << "There was a problem saving one or more data files.\n";
    }
}

void showMenu() {
    cout << "\n====================================\n";
    cout << "     PERSONAL EXPENSE TRACKER\n";
    cout << "====================================\n";
    cout << "1. Set Monthly Income\n";
    cout << "2. Select Expense Type\n";
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

<<<<<<< Updated upstream
// Select expense type
void selectExpense(ExpenseType& selectedExpenseType) {
    clearConsole();
=======
void showAbout() {
    cout << "\nPersonal Expense Tracker\n";
    cout << "Records expenses and summarizes spending using the 50/30/20 rule.\n";
}
>>>>>>> Stashed changes

void showExitScreen() {
    cout << "\nYou have exited the Personal Expense Tracker.\n";
    cout << "Thank you for using the application!\n";
}

<<<<<<< Updated upstream
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
=======
int main() {
    vector<Expense> expenses;
    map<string, double> monthlyIncomes;
    ExpenseType selectedType = ExpenseType::Monthly;

    if (!loadExpenses(expenses, EXPENSES_FILE)) {
        cout << "Could not read the expense file.\n";
>>>>>>> Stashed changes
    }

    if (!loadMonthlyIncomes(monthlyIncomes)) {
        cout << "Could not read the monthly income file.\n";
    }

<<<<<<< Updated upstream

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
    map<string, double> monthlyIncomes;
    ExpenseType selectedExpenseType = ExpenseType::Monthly;
=======
>>>>>>> Stashed changes
    bool running = true;

    while (running) {
        clearConsole();
        showMenu();

        int choice = getChoice(0, 10);

        switch (choice) {
            case 1:
<<<<<<< Updated upstream
                selectExpense(selectedExpenseType);
=======
                setMonthlyIncome(monthlyIncomes);
                pauseConsole();
>>>>>>> Stashed changes
                break;

            case 2:
                selectExpenseType(selectedType);
                pauseConsole();
                break;

            case 3:
                addExpense(expenses, selectedType);
                pauseConsole();
                break;

            case 4:
                viewExpenses(expenses);
                pauseConsole();
                break;

            case 5:
                searchExpenses(expenses);
                pauseConsole();
                break;

            case 6:
<<<<<<< Updated upstream
                clearConsole();
                showBudgetSummaryMenu(expenses, monthlyIncomes);
=======
                updateExpense(expenses);
                pauseConsole();
>>>>>>> Stashed changes
                break;

            case 7:
                deleteExpense(expenses);
                pauseConsole();
                break;

            case 8:
                showBudgetSummary(expenses, monthlyIncomes);
                pauseConsole();
                break;

            case 9:
                saveAllData(expenses, monthlyIncomes);
                pauseConsole();
                break;

            case 10:
                showAbout();
                pauseConsole();
                break;

            case 0:
                saveAllData(expenses, monthlyIncomes);
                showExitScreen();
                running = false;
                break;
        }
    }

    return 0;
}