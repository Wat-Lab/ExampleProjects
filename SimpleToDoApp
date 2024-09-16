import os

# Function to display the menu
def display_menu():
    print("\n--- Todo List Menu ---")
    print("1. View Todo List")
    print("2. Add Todo")
    print("3. Remove Todo")
    print("4. Mark Todo as Done")
    print("5. Exit")

# Function to display the todo list
def display_todos(todos):
    if not todos:
        print("\nNo tasks in the list.")
    else:
        print("\n--- Your Todo List ---")
        for i, (task, status) in enumerate(todos, 1):
            status_display = "Done" if status else "Pending"
            print(f"{i}. {task} [{status_display}]")

# Function to add a new todo
def add_todo(todos):
    task = input("\nEnter the new task: ")
    todos.append((task, False))  # Add as (task, status) with status False (not done)
    print(f"Task '{task}' added.")

# Function to remove a todo
def remove_todo(todos):
    display_todos(todos)
    if todos:
        try:
            task_number = int(input("\nEnter the task number to remove: "))
            removed_task = todos.pop(task_number - 1)
            print(f"Task '{removed_task[0]}' removed.")
        except (ValueError, IndexError):
            print("Invalid task number.")

# Function to mark a todo as done
def mark_done(todos):
    display_todos(todos)
    if todos:
        try:
            task_number = int(input("\nEnter the task number to mark as done: "))
            task, _ = todos[task_number - 1]
            todos[task_number - 1] = (task, True)  # Update the task as done
            print(f"Task '{task}' marked as done.")
        except (ValueError, IndexError):
            print("Invalid task number.")

def main():
    todos = []
    while True:
        display_menu()
        choice = input("\nEnter your choice (1-5): ")

        if choice == "1":
            display_todos(todos)
        elif choice == "2":
            add_todo(todos)
        elif choice == "3":
            remove_todo(todos)
        elif choice == "4":
            mark_done(todos)
        elif choice == "5":
            print("Exiting Todo List Application. Goodbye!")
            break
        else:
            print("Invalid choice. Please enter a number between 1 and 5.")

if __name__ == "__main__":
    main()
