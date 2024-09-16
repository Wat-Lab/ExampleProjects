import json
from datetime import datetime

FILE = "expenses.json"

def load_expenses():
    try:
        with open(FILE, 'r') as file:
            return json.load(file)
    except FileNotFoundError:
        return []

def save_expenses(expenses):
    with open(FILE, 'w') as file:
        json.dump(expenses, file, indent=4)

def add_expense(expenses):
    expense = {
        "date": input("Date (YYYY-MM-DD) or blank for today: ") or datetime.now().strftime("%Y-%m-%d"),
        "description": input("Description: "),
        "amount": float(input("Amount: ")),
        "category": input("Category: ")
    }
    expenses.append(expense)
    save_expenses(expenses)
    print("Expense added.\n")

def display_expenses(expenses):
    if not expenses:
        print("No expenses recorded.\n")
        return
    print(f"\n{'Date':<12} {'Description':<20} {'Amount':<10} {'Category':<15}")
    print("-" * 60)
    for e in expenses:
        print(f"{e['date']:<12} {e['description']:<20} {e['amount']:<10.2f} {e['category']:<15}")
    print()

def display_total(expenses):
    print(f"\nTotal Expenses: ${sum(e['amount'] for e in expenses):.2f}\n")

def main():
    expenses = load_expenses()
    actions = {
        '1': lambda: add_expense(expenses),
        '2': lambda: display_expenses(expenses),
        '3': lambda: display_total(expenses),
        '4': lambda: exit("Goodbye!")
    }
    while True:
        choice = input("\n1. Add Expense\n2. View Expenses\n3. View Total\n4. Exit\nChoose an option: ")
        actions.get(choice, lambda: print("Invalid option\n"))()

if __name__ == "__main__":
    main()
