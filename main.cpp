#include <iostream>
#include <sstream>
#include <string>

void showMenu() {
    std::cout << "\n=== Personal Expense Tracker ===\n";
    std::cout << "1. Add an expense\n";
    std::cout << "2. View all expenses\n";
    std::cout << "3. Search expenses\n";
    std::cout << "4. Update an expense\n";
    std::cout << "5. Delete an expense\n";
    std::cout << "6. Show spending summary\n";
    std::cout << "7. Exit\n";
}

int getMenuChoice() {
    std::string line;

    while (true) {
        std::cout << "Choose an option (1-7): ";

        if (!std::getline(std::cin, line)) {
            return 7; // Exit if input ends
        }

        std::istringstream input(line);
        int choice;
        char extraCharacter;

        if ((input >> choice) &&
            !(input >> extraCharacter) &&
            choice >= 1 &&
            choice <= 7) {
            return choice;
        }

        std::cout << "Invalid choice. Enter a number from 1 to 7.\n";
    }
}

int main() {
    bool running = true;

    while (running) {
        showMenu();
        int choice = getMenuChoice();

        switch (choice) {
            case 1:
                std::cout << "Add Expense will be implemented next.\n";
                break;

            case 2:
                std::cout << "View Expenses will be implemented next.\n";
                break;

            case 3:
                std::cout << "Search Expenses will be implemented next.\n";
                break;

            case 4:
                std::cout << "Update Expense will be implemented next.\n";
                break;

            case 5:
                std::cout << "Delete Expense will be implemented next.\n";
                break;

            case 6:
                std::cout << "Spending Summary will be implemented next.\n";
                break;

            case 7:
                std::cout << "Goodbye!\n";
                running = false;
                break;
        }
    }

    return 0;
}