# CS0053 • TN35 • Final Group Project

# AI Interaction Log

**Personal Expense Tracker | Group unKNOWNymous**

| Project detail | Information |
|---|---|
| Group | unKNOWNymous |
| Section | TN35 |
| Project | Personal Expense Tracker |
| Language | C++ |
| Repository | [Personal Expense Tracker on GitHub](https://github.com/vllrnDnh/CS0053-TN35-unKNOWNymous-PersonalExpenseTracker) |

---

## Purpose

This log documents how AI assistance was used during the planning, development, testing preparation, and explanation of the Personal Expense Tracker. It records the task or prompt, the AI response, the group's decision, the reason for that decision, and how the result was checked.

**Evidence note:** The entries below are based on the project-related ChatGPT discussions available in the conversation history and the configuration files included in the project repository. A recommendation or explanation being reviewed does not, by itself, prove that the program was successfully tested. Runtime tests and test-coverage claims must be supported by actual execution evidence.

## 1. AI Interaction Records

### Interaction 1 — Algorithm recommendation and implementation (October 19, 2026)

| Required field | Record |
|---|---|
| **Prompt / task** | Asked for the best C++ algorithm for a school Personal Expense Tracker project, with budget tracking as its main feature. The request included algorithm steps and sample code. |
| **AI response summary** | AI recommended a rule-based **50/30/20 budgeting algorithm**: allocate 50% of income to Needs, 30% to Wants, and 20% to Savings; categorize transactions; calculate spending totals; compare spending against the allocated budgets; and show remaining balances or overspending warnings. The sample implementation used a `Transaction` structure, arrays, a vector, input validation, and a menu. |
| **Decision** | **MODIFIED.** The group adopted the 50/30/20 budgeting logic but did not use the sample implementation exactly as provided. |
| **Reason** | The recommended budgeting rule matched the project's main objective, but the sample code needed to fit the group's existing program structure, expense categories, menu, and data-persistence requirements. |
| **Final approach / changes** | The budgeting calculations were incorporated into the group's C++ application. The project uses the shared `Expense` structure and `ExpenseCategory` enum for Needs, Wants, and Savings; `ExpenseType` for Monthly, Weekly, and Daily; a vector for expense records; a map for monthly income; and text files for saving expense and income data. The 50/30/20 allocations are used in the budget and spending-summary features. |
| **Verification** | The final source structure and project documentation were reviewed against the implementation, including `main.cpp`, `expense.h`, and the README. **Runtime verification remains dependent on the group's actual test executions**; attach the corresponding inputs, expected and actual outputs, and screenshots before claiming that all scenarios passed. |

### Interaction 2 — Sample input planning

| Required field | Record |
|---|---|
| **Prompt / task** | Asked for sample user inputs to check whether the Personal Expense Tracker works correctly and matches its documented features. |
| **AI response summary** | AI provided a sample-use sequence for exercising the application's main functions, including setting income, adding expenses, viewing and searching records, updating and deleting records, and checking the budget summary. |
| **Decision** | **ACCEPTED AS A TEST-PLANNING REFERENCE.** |
| **Reason** | A structured sequence helps the group test the menu options in a consistent order and identify missing or incorrect behavior. The suggested values are examples, not evidence that the tests were executed. |
| **Verification** | Use the sequence against the actual application. Record the exact inputs, expected results, actual results, and screenshots. Do not mark a scenario as passed until it has been run. |

### Interaction 3 — Testing documentation

| Required field | Record |
|---|---|
| **Prompt / task** | Asked how to complete the project's 11 testing sections before submission. |
| **AI response summary** | AI explained how to prepare test scenarios and document expected versus actual results, including normal, boundary, and invalid-input cases. |
| **Decision** | **ACCEPTED AS A DOCUMENTATION GUIDE.** |
| **Reason** | The project guidelines require concrete testing evidence. Recording expected and actual results makes the test outcome more useful than listing test names or writing only “Passed.” |
| **Verification** | The group must complete the test table using actual program executions. Include at least the required number of test cases and attach supporting output or screenshots. Any unexecuted case must remain marked pending. |

### Interaction 4 — Code and system-structure explanation

| Required field | Record |
|---|---|
| **Prompt / task** | Asked for an analysis of `main.cpp` and an explanation of the system structure, including the purpose of `expense.h`, and later requested shorter, direct explanations for the presentation. |
| **AI response summary** | AI explained the menu-driven program flow, the responsibilities handled in `main.cpp`, the shared `Expense` structure and enums in `expense.h`, and the use of data files for persistence. It also helped shorten the explanations for presentation delivery. |
| **Decision** | **MODIFIED.** The explanations were shortened and adjusted to describe the project's actual code and presentation time limit. |
| **Reason** | The original explanations needed to be concise enough for the presentation while remaining technically accurate and consistent with the submitted source code. |
| **Verification** | The descriptions should be checked against the current `main.cpp`, `expense.h`, and README. The presenter should be able to explain each component and answer questions about the actual implementation. |

---

## 2. AI Testing Workflow Configuration

The repository contains two AI testing configuration files:

| Repository file | What it establishes | What it does not prove |
|---|---|---|
| `.github/instructions/unittestMcp.instructions.md` | Provides instructions for using UnitTest MCP for test generation, test review, test execution, coverage inspection, and reporting. It also describes safeguards such as preserving existing program behavior and reporting results honestly. | It does not prove that test files were generated, reviewed, executed, or passed, or that coverage was achieved. |

### Repository evidence

Commit `80e6e6c` is described as **“chore: add project instructions and VS Code configuration.”** This supports the claim that project instructions and VS Code configuration were added to the repository. It should not be presented as proof that automated unit testing or coverage analysis was completed.

---

## 3. Modified AI Recommendation — 50/30/20 Budgeting Algorithm

This is the documented example of an AI recommendation that the group modified.

| Field | Record |
|---|---|
| **Original AI recommendation** | Use a rule-based 50/30/20 algorithm: allocate 50% of income to Needs, 30% to Wants, and 20% to Savings; categorize transactions; calculate spending totals; compare them with the allocations; and display remaining balances or overspending warnings. The AI's sample code used a `Transaction` structure, arrays, and an in-memory vector. |
| **Decision** | **MODIFIED** |
| **Reason** | The budgeting rule was suitable for the project's objective, but the sample code did not match the group's existing data model and required file-persistence features. |
| **Final approach** | The group retained the 50/30/20 calculations and adapted the implementation to its own C++ structure: `Expense`, `ExpenseCategory`, and `ExpenseType` in `expense.h`; expense records stored in a vector; monthly income organized in a map; and text-file persistence through `expenses.txt` and `monthly_income.txt`. The calculations are integrated with the program's budget and spending-summary functions. |
| **Verification** | The source organization and documented implementation were reviewed against `main.cpp`, `expense.h`, and the README. This confirms the design was adapted to the project structure. It does **not** independently confirm runtime correctness; actual test inputs and outputs must be attached to demonstrate that the calculations work as expected. |

---

## 4. Verification and Submission Checklist

- [ ] Confirm that the interaction records accurately represent the prompts and AI assistance used by the group.
- [ ] Add screenshots or conversation references where required by the instructor.
- [ ] Confirm which group member used each AI interaction; do not assign authorship without evidence.
- [ ] Run the sample test scenarios on the final version of the application.
- [ ] Record exact test inputs, expected results, actual results, and pass/fail outcomes.
- [ ] Attach test output or screenshots. Include coverage results only if coverage was actually inspected.
- [ ] If UnitTest MCP was used, retain the generated test files and actual tool execution/review results.
- [ ] Retain repository evidence for the two `.github` configuration files and commit `80e6e6c`.
- [ ] Make sure every group member understands the AI-assisted changes and can explain the submitted code.

## Compliance reminder

The CS0053 / TN35 project guidelines require meaningful AI interactions to be documented with the prompt, response summary, decision, reason, and verification. They also require at least one justified rejected or modified recommendation. This log records the modified 50/30/20 algorithm recommendation. The group must still supply genuine execution evidence for any testing claims and confirm that the entries accurately represent its work.

---

*Prepared from the group's project-related ChatGPT discussions, uploaded project materials, repository configuration files, and available commit-history details. Any runtime testing or coverage result not supported by actual evidence is intentionally not claimed.*
