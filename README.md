# 💰 Personal Expense Tracker

**C++ Console Application \| CS0053 Final Group Project**

A console-based personal finance application developed in C++ to help
users record, organize, search, update, and delete expenses while
monitoring monthly income and spending through the **50/30/20 budgeting
rule**.

------------------------------------------------------------------------

## 📌 Table of Contents

- [💰 Personal Expense Tracker](#-personal-expense-tracker)
  - [📌 Table of Contents](#-table-of-contents)
  - [📝 Project Overview](#-project-overview)
    - [Problem Statement](#problem-statement)
  - [🎯 Objectives](#-objectives)
    - [General Objective](#general-objective)
    - [Specific Objectives](#specific-objectives)
  - [✨ Core Features](#-core-features)
    - [Main Menu](#main-menu)
  - [🗂️ Expense Classification](#️-expense-classification)
  - [📅 Expense Types](#-expense-types)
  - [🧮 Expense Tracker Algorithm](#-expense-tracker-algorithm)
    - [Primary Algorithm: Rule-Based Budgeting Algorithm](#primary-algorithm-rule-based-budgeting-algorithm)
    - [1. Budget Allocation Formulas](#1-budget-allocation-formulas)
    - [2. Algorithm Process](#2-algorithm-process)
    - [3. Budget Calculation Pseudocode](#3-budget-calculation-pseudocode)
    - [4. Why This Algorithm Was Selected](#4-why-this-algorithm-was-selected)
  - [⚙️ Supporting Algorithms and Techniques](#️-supporting-algorithms-and-techniques)
    - [1. CRUD Operations](#1-crud-operations)
    - [2. Linear Search](#2-linear-search)
    - [3. File Handling](#3-file-handling)
    - [4. Input Validation](#4-input-validation)
    - [5. Sorting](#5-sorting)
  - [🔄 System Workflow](#-system-workflow)
    - [Main System Components](#main-system-components)
  - [💾 Data Structures and File Storage](#-data-structures-and-file-storage)
    - [Expense Structure](#expense-structure)
    - [Enumerations](#enumerations)
    - [Data Collections](#data-collections)
    - [Local Data Files](#local-data-files)
  - [📁 Project Structure](#-project-structure)
  - [🖥️ Requirements](#️-requirements)
  - [🚀 Installation and Execution](#-installation-and-execution)
    - [1. Clone the Repository](#1-clone-the-repository)
    - [2. Open the Project Directory](#2-open-the-project-directory)
    - [3. Compile the Source Code](#3-compile-the-source-code)
    - [4. Run the Applicatiogit add README.mdn](#4-run-the-applicatiogit-add-readmemdn)
    - [5. Start Using the Application](#5-start-using-the-application)
  - [📊 Sample Budget Calculation](#-sample-budget-calculation)
  - [🛡️ Validation and Error Handling](#️-validation-and-error-handling)
  - [🧪 Testing](#-testing)
  - [⚠️ Limitations](#️-limitations)
  - [👥 Development Team](#-development-team)
    - [Development and Collaboration](#development-and-collaboration)
  - [📚 Project Information](#-project-information)

------------------------------------------------------------------------

## 📝 Project Overview

The **Personal Expense Tracker** is a C++ console application designed
to make personal expense monitoring more organized and manageable. It
provides users with a way to record financial transactions, classify
them according to their purpose, and review their spending for a
selected month.

The main algorithm of the project is a **Rule-Based Budgeting
Algorithm** based on the 50/30/20 budgeting rule. This method divides a
user's monthly income into three budget allocations:

-   **50% -- Needs:** Essential expenses.
-   **30% -- Wants:** Non-essential or discretionary expenses.
-   **20% -- Savings:** Money intended for savings and future financial
    goals.

By combining expense management operations with budget calculations, the
system helps users understand how their money is allocated, how much
they have spent, and how much remains in each budget category.

The application stores expense records and monthly income locally using
text files, allowing information to be loaded again when the program is
reopened.

### Problem Statement

Keeping track of personal expenses can become difficult when
transactions are recorded manually or are not organized by category.
Users may struggle to identify where their money goes, calculate their
total spending, and determine whether they are staying within their
intended budget.

The Personal Expense Tracker addresses these concerns through structured
expense recording, category classification, monthly budget calculations,
and local data storage.

------------------------------------------------------------------------

## 🎯 Objectives

### General Objective

To develop a functional C++ Personal Expense Tracker that helps users
manage personal expenses, monitor monthly spending, and organize income
through the 50/30/20 budgeting rule.

### Specific Objectives

1.  **Track Expenses** -- Record financial transactions with
    descriptions, amounts, dates, categories, and expense types.
2.  **Allocate Monthly Income** -- Calculate the recommended Needs,
    Wants, and Savings allocations.
3.  **Monitor Spending** -- Determine actual spending and remaining
    balances for each budget category.
4.  **Manage Records** -- Provide functions for adding, viewing,
    searching, updating, and deleting expenses.
5.  **Preserve Data** -- Save and load expense records and monthly
    income using local text files.
6.  **Validate Inputs** -- Check user entries, numeric values, dates,
    and menu selections to maintain data accuracy.
7.  **Promote Budget Awareness** -- Present a monthly spending summary
    to help users review their financial activity.

------------------------------------------------------------------------

## ✨ Core Features

  -----------------------------------------------------------------------
  Feature                             Description
  ----------------------------------- -----------------------------------
  Select Expense Type                 Select Monthly, Weekly, or Daily
                                      before recording an expense.

  Set Monthly Income                  Enter and save income for a
                                      specified month using `YYYY-MM`
                                      format.

  Add an Expense                      Record a description, amount, date,
                                      category, and selected expense
                                      type.

  View All Expenses                   Display all saved expense records.

  Search an Expense                   Search using an expense ID or a
                                      description keyword.

  Update an Expense                   Modify an existing expense's
                                      details.

  Delete an Expense                   Remove an expense after
                                      confirmation.

  Show Spending Summary               Calculate budget allocations,
                                      actual spending, and remaining
                                      balances for a selected month.

  Save Data                           Save expense records and monthly
                                      income to local files.

  About the System                    Display information about the
                                      application.
  -----------------------------------------------------------------------

### Main Menu

The current application provides the following console menu:

``` text
====================================
       PERSONAL EXPENSE TRACKER
====================================
1. Select Type of Expense
2. Set Monthly Income
3. Add an Expense
4. View All Expenses
5. Search an Expense
6. Update an Expense
7. Delete an Expense
8. Show Spending Summary
9. Save Data
10. About the System
0. Exit
====================================
```

------------------------------------------------------------------------

## 🗂️ Expense Classification

The system organizes financial records into three primary categories
based on the 50/30/20 budgeting rule.

  ----------------------------------------------------------------------------
  Category                    Allocation Description         Examples
  ---------------- --------------------- ------------------- -----------------
  **Needs**                          50% Essential expenses  Food, groceries,
                                         required for        transportation,
                                         everyday living and school
                                         responsibilities.   necessities,
                                                             utilities, rent,
                                                             and essential
                                                             bills

  **Wants**                          30% Non-essential       Entertainment,
                                         expenses related to dining out,
                                         personal            shopping,
                                         preferences and     subscriptions,
                                         leisure.            hobbies, and
                                                             leisure
                                                             activities

  **Savings**                       20% Contributions       Emergency funds,
                                         intended for future personal savings,
                                         financial needs and and savings goals
                                         goals.                                                  
             
  ----------------------------------------------------------------------------

**Important:** The application records these as the three main expense
categories. Detailed examples above are suggested classifications; the
program itself asks the user to select Needs, Wants, or Savings.

Savings contributions are tracked separately from ordinary spending. A
calculated savings target does not automatically mean that the target
has been achieved.

------------------------------------------------------------------------

## 📅 Expense Types

Before adding an expense, users can select one of the following expense
types:

  Expense Type   Description
  -------------- ---------------------------------
  **Monthly**    Expenses identified as monthly.
  **Weekly**     Expenses identified as weekly.
  **Daily**      Expenses identified as daily.

The selected expense type is stored with the expense record. It serves
as a classification of the transaction and is distinct from the 50/30/20
budget category.

------------------------------------------------------------------------

## 🧮 Expense Tracker Algorithm

### Primary Algorithm: Rule-Based Budgeting Algorithm

The main algorithm calculates the recommended budget allocation based on
the user's monthly income. It then compares the allocation with the
actual amounts recorded under each category.

### 1. Budget Allocation Formulas

Let `I` represent the user's monthly income.

``` text
Needs Budget   = Monthly Income × 0.50
Wants Budget   = Monthly Income × 0.30
Savings Target = Monthly Income × 0.20
```

The remaining budget is calculated using:

``` text
Remaining Budget = Allocated Budget − Actual Spending
```

For savings:

``` text
Remaining Savings Target = Savings Budget − Actual Savings Contributions
```

Total ordinary expenses are calculated as:

``` text
Total Expenses = Needs Spending + Wants Spending
```

### 2. Algorithm Process

1.  Obtain the selected month from the user.
2.  Check whether monthly income has been recorded for that month.
3.  Calculate the 50% Needs allocation.
4.  Calculate the 30% Wants allocation.
5.  Calculate the 20% Savings allocation.
6.  Examine the saved expense records.
7.  Include only records whose dates belong to the selected month.
8.  Accumulate amounts separately for Needs, Wants, and Savings.
9.  Calculate the remaining balance for each allocation.
10. Display the monthly budget summary.

### 3. Budget Calculation Pseudocode

``` text
FUNCTION calculateBudget(monthlyIncome)

    needsBudget = monthlyIncome * 0.50
    wantsBudget = monthlyIncome * 0.30
    savingsBudget = monthlyIncome * 0.20

    RETURN budget allocations

END FUNCTION


FUNCTION updateBudgetSpending(budget, expenses, selectedMonth)

    needsSpent = 0
    wantsSpent = 0
    savingsContributed = 0

    FOR each expense in expenses

        IF expense.date belongs to selectedMonth

            IF expense.category is Needs
                needsSpent += expense.amount

            ELSE IF expense.category is Wants
                wantsSpent += expense.amount

            ELSE IF expense.category is Savings
                savingsContributed += expense.amount

            END IF

        END IF

    END FOR

    needsRemaining = needsBudget - needsSpent
    wantsRemaining = wantsBudget - wantsSpent
    savingsRemaining = savingsBudget - savingsContributed

    totalExpenses = needsSpent + wantsSpent

    DISPLAY budget allocation
    DISPLAY actual spending
    DISPLAY remaining balances

END FUNCTION
```

### 4. Why This Algorithm Was Selected

The Rule-Based Budgeting Algorithm is appropriate because the project
requires a straightforward and consistent way to divide monthly income
and monitor spending.

It is deterministic: the same monthly income and expense records produce
the same budget allocations and totals. Its calculations are also easy
to verify using sample inputs and test cases.

More advanced algorithms, such as Greedy Algorithms, Divide and Conquer,
and Dynamic Programming, are unnecessary for the project's stated
budgeting requirements.

------------------------------------------------------------------------

## ⚙️ Supporting Algorithms and Techniques

The budgeting algorithm works together with supporting techniques that
manage the application's records and inputs.

### 1. CRUD Operations

CRUD stands for Create, Read, Update, and Delete. These operations allow
users to manage expense records.

  Operation    Application
  ------------ ------------------------------------
  **Create**   Add a new expense record.
  **Read**     View saved expense records.
  **Update**   Modify an existing expense record.
  **Delete**   Remove an expense record.

### 2. Linear Search

Linear Search is used to locate an expense by its ID. The program checks
records one by one until it finds the requested ID or reaches the end of
the collection.

The application also searches descriptions by checking whether the
entered keyword appears in each expense description.

**ID search pseudocode:**

``` text
FOR each expense in expenses

    IF expense.id equals searchID
        DISPLAY expense
        RETURN expense index
    END IF

END FOR

DISPLAY "Expense not found"
RETURN -1
```

**Worst-case time complexity:** `O(n)`, where `n` is the number of
stored expense records.

### 3. File Handling

File handling preserves information between program sessions.

The application uses:

-   `expenses.txt` -- Stores expense records in CSV-formatted text.
-   `monthly_income.txt` -- Stores monthly income records.

The system loads saved records when it starts and saves changes when
records are added, updated, or deleted. Users can also manually save all
data through the menu.

### 4. Input Validation

Input validation helps prevent invalid information from entering the
system.

The implementation checks:

-   Menu selections against the accepted range.
-   Expense amounts and monthly income for positive numeric values.
-   Required text fields to ensure they are not empty.
-   Dates using the `YYYY-MM-DD` format.
-   Monthly income periods using the `YYYY-MM` format.
-   Expense IDs before updating or deleting records.
-   Numeric input errors to allow the program to recover and request
    valid input.

### 5. Sorting

Sorting is an optional supporting technique. It may be added in future
improvements to arrange expenses by date or amount. It is not currently
listed as a menu feature in the submitted implementation.

------------------------------------------------------------------------

## 🔄 System Workflow

The application follows a menu-driven process:

``` text
                  START
                    |
                    v
          LOAD SAVED DATA FILES
                    |
                    v
             DISPLAY MENU
                    |
                    v
          VALIDATE USER SELECTION
                    |
                    v
           EXECUTE SELECTED TASK
                    |
       +------------+-------------+
       |            |             |
       v            v             v
  EXPENSE        BUDGET         DATA
 MANAGEMENT    CALCULATION    MANAGEMENT
       |            |             |
       +------------+-------------+
                    |
                    v
             DISPLAY RESULT
                    |
                    v
            RETURN TO MENU
                    |
             User selects 0?
                /       \
              No         Yes
              |           |
              v           v
          DISPLAY      SAVE DATA
            MENU          |
                          v
                         EXIT
```

### Main System Components

1.  **User Interface** -- Displays the console menu and receives user
    commands.
2.  **Input Validation** -- Checks the validity of entered information.
3.  **Expense Management** -- Handles expense creation, viewing,
    searching, updating, and deletion.
4.  **Budget Calculator** -- Calculates 50/30/20 allocations and
    remaining balances.
5.  **Summary Generator** -- Displays the selected month's financial
    summary.
6.  **Data Storage** -- Loads and saves expense and income records.

------------------------------------------------------------------------

## 💾 Data Structures and File Storage

### Expense Structure

The application uses an `Expense` structure defined in `expense.h`.

``` cpp
struct Expense {
    int id = 0;
    std::string description;
    double amount = 0.0;
    std::string date;

    ExpenseCategory category = ExpenseCategory::Needs;
    ExpenseType expenseType = ExpenseType::Monthly;
};
```

### Enumerations

The application uses enumerations to represent expense types and budget
categories.

``` cpp
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
```

### Data Collections

The program uses:

-   `vector<Expense>` to store multiple expense records in memory.
-   `map<string, double>` to associate a year-month value with its
    monthly income.

### Local Data Files

  -----------------------------------------------------------------------
  File                                Purpose
  ----------------------------------- -----------------------------------
  `expenses.txt`                      Stores expense IDs, descriptions,
                                      amounts, dates, categories, and
                                      expense types.

  `monthly_income.txt`                Stores monthly income values
                                      associated with their corresponding
                                      months.

  -----------------------------------------------------------------------

Expense records are written using CSV-formatted fields inside
`expenses.txt`. The program includes CSV field quoting and parsing
utilities to handle commas and quotation marks in text fields.

------------------------------------------------------------------------

## 📁 Project Structure

The main project files are organized as follows:

``` text
CS0053-TN35-unKNOWNymous-PersonalExpenseTracker/
│
├── .github/
│   ├── instructions/
│   │   └── unittestMcp.instructions.md
│   └── prompts/
│       └── UnitTestMcp.UnitTestEngineer.agent.md
│
├── .vscode/
│   └── tasks.json
│
├── expense.h
├── main.cpp
├── .gitignore
└── README.md
```

**Generated files:** When the application runs, it creates or updates
`expenses.txt` and `monthly_income.txt` in its working directory.
Executable files such as `.exe` files are build outputs and are not
required to compile the source code.

------------------------------------------------------------------------

## 🖥️ Requirements

To build and run the application, you need:

-   A C++ compiler that supports **C++11 or later**.
-   A terminal or command prompt.
-   A code editor or IDE, such as Visual Studio Code, Code::Blocks, or
    another C++ development environment.

The project uses standard C++ libraries and does not require an external
package or database.

------------------------------------------------------------------------

## 🚀 Installation and Execution

### 1. Clone the Repository

``` bash
git clone <YOUR-GITHUB-REPOSITORY-URL>
```

### 2. Open the Project Directory

``` bash
cd CS0053-TN35-unKNOWNymous-PersonalExpenseTracker
```

### 3. Compile the Source Code

Using `g++`:

``` bash
g++ -std=c++11 main.cpp -o PET
```

If your compiler uses a different default standard, make sure it
supports the C++ features used by the source code.

### 4. Run the Applicatiogit add README.mdn

**Windows:**

``` bash
.\PET.exe
```

**Linux/macOS:**

``` bash
./PET
```

### 5. Start Using the Application

1.  Select an expense type.
2.  Set the monthly income for the month you want to monitor.
3.  Add expenses and assign each one to Needs, Wants, or Savings.
4.  View, search, update, or delete expense records as needed.
5.  Open the spending summary and enter the month to review.
6.  Save your data before exiting.

**Note:** The application uses relative file names. Run it from the
project directory so its local data files are created and loaded in the
expected working directory.

------------------------------------------------------------------------

## 📊 Sample Budget Calculation

Suppose a user has a monthly income of **₱20,000.00**.

  Category      Allocation           Budget
  ----------- ------------ ----------------
  Needs                50%       ₱10,000.00
  Wants                30%        ₱6,000.00
  Savings              20%        ₱4,000.00
  **Total**       **100%**   **₱20,000.00**

Assume the user records the following transactions for the selected
month:

  Category                  Actual Amount
  ----------------------- ---------------
  Needs                         ₱7,500.00
  Wants                         ₱2,000.00
  Savings Contributions         ₱1,000.00

The resulting balances are:

  Category     Allocated Budget   Actual Amount   Remaining
  ---------- ------------------ --------------- -----------
  Needs              ₱10,000.00       ₱7,500.00   ₱2,500.00
  Wants               ₱6,000.00       ₱2,000.00   ₱4,000.00
  Savings             ₱4,000.00       ₱1,000.00   ₱3,000.00

**Total ordinary expenses:** ₱9,500.00 (Needs + Wants).

The savings contribution is shown separately and is not included in
ordinary expenses. A negative remaining balance indicates that actual
spending or contributions have exceeded the corresponding allocation.

------------------------------------------------------------------------

## 🛡️ Validation and Error Handling

The application includes validation and basic recovery mechanisms to
help maintain reliable records.

-   Invalid menu choices are rejected, and the user is prompted again.
-   Non-numeric menu entries are cleared from the input stream.
-   Amounts and income must be positive and finite.
-   Empty descriptions are not accepted.
-   Dates are checked for valid year, month, day, and leap-year values.
-   Monthly income periods must follow the `YYYY-MM` format.
-   Update and delete operations require an existing expense ID.
-   Deletion requires user confirmation.
-   Invalid or malformed saved expense rows are skipped during loading.
-   If saving an expense update or deletion fails, the original
    in-memory record is restored.

------------------------------------------------------------------------

## 🧪 Testing

The following scenarios are recommended for verifying the application's
behavior. Actual results should be documented after executing the tests.

  -----------------------------------------------------------------------
  Test Case               Scenario                Expected Result
  ----------------------- ----------------------- -----------------------
  1\. Valid Income        Enter a positive        The income is saved for
                          monthly income.         the selected month.

  2\. Invalid Income      Enter zero, a negative  The system rejects the
                          amount, or non-numeric  value and requests
                          input.                  valid input.

  3\. Add Expense         Enter valid expense     The expense is assigned
                          details and a category. an ID and saved.

  4\. View Expenses       Open the expense list   Saved expense records
                          when records exist.     are displayed.

  5\. Search Existing ID  Search using an         The matching expense is
                          existing expense ID.    displayed.

  6\. Search Missing ID   Search using a          An expense-not-found
                          nonexistent ID.         message is displayed.

  7\. Update Expense      Update an existing      The revised record is
                          expense.                saved.

  8\. Delete Expense      Confirm deletion of an  The record is removed
                          existing expense.       and the data file is
                                                  updated.

  9\. Budget Summary      Enter a month with      The correct
                          saved income and        allocations, spending
                          expenses.               totals, and remaining
                                                  balances are displayed.

  10\. Data Persistence   Save, close, and reopen Previously saved
                          the application.        expenses and income are
                                                  loaded.
  -----------------------------------------------------------------------

Testing results should include the actual observed program output. Do
not report a test as passed until it has been executed and verified.

------------------------------------------------------------------------

## ⚠️ Limitations

-   The application is designed for local, single-user expense tracking.
-   It does not connect to bank accounts or automatically import
    transactions.
-   It does not provide online synchronization or simultaneous
    multi-user access.
-   Expense categories are limited to Needs, Wants, and Savings.
-   Monthly budget summaries are calculated by filtering expense dates
    for the selected `YYYY-MM` period.
-   Monthly, Weekly, and Daily are stored as expense types; the 50/30/20
    budget summary itself is calculated on a monthly basis.
-   The 50/30/20 rule is a budgeting guideline and may not fit every
    user's financial situation.
-   Financial values are represented using C++ `double`; floating-point
    rounding may affect some calculations.

------------------------------------------------------------------------

## 👥 Development Team

**CS0053 -- Final Group Project**
```
  Member     Name
  ---------- -----------------------------
  Member 1   Dacunos, Mark Daniel
  Member 2   Machica, Benedict
  Member 3   Segunto, Bienn Kyla
  Member 4   Villarina, Dinah Chrishalei
```

------------------------------------------------------------------------
### Development and Collaboration

The project uses Git and GitHub for collaborative development,
source-code management, and integration of group contributions.

The team's collaboration workflow includes:

-   Feature branches for separate development tasks.
-   Meaningful commits to document changes.
-   Pull requests for integrating completed features.
-   Code reviews before merging changes into the main branch.
------------------------------------------------------------------------

## 📚 Project Information
```
  -----------------------------------------------------------------------
  Item                                Details
  ----------------------------------- -----------------------------------
  Project                             Personal Expense Tracker

  Subject                             CS0053

  Project Type                        Final Group Project

  Programming Language                C++

  Application Type                    Console-Based Application

  Primary Algorithm                   Rule-Based Budgeting Algorithm

  Budgeting Method                    50/30/20 Rule

  Supporting Techniques               CRUD Operations, Linear Search,
                                      File Handling, Input Validation
                                      
  -----------------------------------------------------------------------
```
------------------------------------------------------------------------

**Developed as a CS0053 Final Group Project.**

*Track your expenses, understand your spending, and make every peso
count.* 💗
