#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

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
void selectExpense() {
    clearConsole();

    cout << "\n=== Select Expense Type ===\n";
    cout << "1. Monthly Expenses\n";
    cout << "2. Weekly Expenses\n";
    cout << "3. Daily Expenses\n";

    int expenseType = getChoice(1, 3);

    switch (expenseType) {
        case 1:
            cout << "\nYou selected Monthly Expenses.\n";
            break;
        case 2:
            cout << "\nYou selected Weekly Expenses.\n";
            break;
        case 3:
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
    bool running = true;

    while (running) {
        clearConsole();
        showMenu();

        int choice = getChoice(1, 8);

        switch (choice) {
            case 1:
                selectExpense();
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
