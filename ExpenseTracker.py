import json
from datetime import datetime

# File to store expenses
expense_file = "expenses.json"

# Function to load expenses from file
def load_expenses():
    try:
        with open(expense_file, 'r') as file:
            return json.load(file)
    except FileNotFoundError:
        return []

# Function to save expenses to file
def save_expenses(expenses):
    with open(expense_file, 'w') as file:
        json.dump(expenses, file, indent=4)

# Function to add an expense
def add_expense():
    date = input("Enter the date (YYYY-MM-DD) or leave blank for today's date: ")
    if not date:
        date = datetime.now().strftime("%Y-%m-%d")
    description = input("Enter expense description: ")
    amount = float(input("Enter amount: "))
    category = input("Enter category (e.g., food, transportation): ")
    
    expense = {
        "date": date,
        "description": description,
        "amount": amount,
        "category": category
    }

    expenses.append(expense)
    save_expenses(expenses)
    print("Expense added successfully.")

# Function to display all expenses
def view_expenses():
    if not expenses:
        print("No expenses recorded.")
        return

    print("\nExpenses:")
    print("{:<12} {:<25} {:<10} {:<15}".format("Date", "Description", "Amount", "Category"))
    print("-" * 65)
    for expense in expenses:
        print("{:<12} {:<25} {:<10} {:<15}".format(
            expense["date"],
            expense["description"],
            expense["amount"],
            expense["category"]
        ))

# Function to display total expenses
def view_total():
    total = sum(expense['amount'] for expense in expenses)
    print(f"\nTotal Expenses: ${total:.2f}")

# Main Menu
def main():
    while True:
        print("\n--- Expense Tracker Menu ---")
        print("1. Add Expense")
        print("2. View Expenses")
        print("3. View Total Expenses")
        print("4. Exit")
        choice = input("Choose an option: ")

        if choice == '1':
            add_expense()
        elif choice == '2':
            view_expenses()
        elif choice == '3':
            view_total()
        elif choice == '4':
            print("Exiting the program. Goodbye!")
            break
        else:
            print("Invalid option. Please try again.")

if __name__ == "__main__":
    expenses = load_expenses()
    main()
