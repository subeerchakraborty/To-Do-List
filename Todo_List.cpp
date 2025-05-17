#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>

using namespace std;

struct Task {
    string description;
    bool completed;
};

vector<Task> tasks;

void clearScreen() {
    system("cls"); // For Windows. Use "clear" for Linux/Mac
}

void displayMenu() {
    cout << "\n===== TO-DO LIST MANAGER =====" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. View All Tasks" << endl;
    cout << "3. Mark Task as Completed" << endl;
    cout << "4. Delete Task" << endl;
    cout << "5. Save to File" << endl;
    cout << "6. Load from File" << endl;
    cout << "7. Exit" << endl;
    cout << "==============================" << endl;
    cout << "Enter your choice: ";
}

void addTask() {
    Task newTask;
    cout << "Enter task description: ";
    getline(cin, newTask.description);
    newTask.completed = false;
    tasks.push_back(newTask);
    cout << "Task added successfully!" << endl;
}

void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks in the list!" << endl;
        return;
    }

    cout << "\n===== TASK LIST =====" << endl;
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". [" << (tasks[i].completed ? "X" : " ") << "] "
             << tasks[i].description << endl;
    }
}

void markCompleted() {
    viewTasks();
    if (tasks.empty()) return;

    int index;
    cout << "Enter task number to mark as completed: ";
    cin >> index;

    if (index < 1 || index > static_cast<int>(tasks.size())) {
        cout << "Invalid task number!" << endl;
        return;
    }

    tasks[index - 1].completed = true;
    cout << "Task marked as completed!" << endl;
}

void deleteTask() {
    viewTasks();
    if (tasks.empty()) return;

    int index;
    cout << "Enter task number to delete: ";
    cin >> index;

    if (index < 1 || index > static_cast<int>(tasks.size())) {
        cout << "Invalid task number!" << endl;
        return;
    }

    tasks.erase(tasks.begin() + index - 1);
    cout << "Task deleted successfully!" << endl;
}

void saveToFile() {
    ofstream file("todo.txt");
    if (!file) {
        cout << "Error saving to file!" << endl;
        return;
    }

    for (const auto& task : tasks) {
        file << task.completed << " " << task.description << endl;
    }

    cout << "Tasks saved to file!" << endl;
}

void loadFromFile() {
    ifstream file("todo.txt");
    if (!file) {
        cout << "No saved tasks found!" << endl;
        return;
    }

    tasks.clear();
    Task task;
    string line;
    
    while (getline(file, line)) {
        size_t spacePos = line.find(' ');
        if (spacePos != string::npos) {
            task.completed = line[0] == '1';
            task.description = line.substr(spacePos + 1);
            tasks.push_back(task);
        }
    }

    cout << "Tasks loaded from file!" << endl;
}

int main() {
    int choice;

    do {
        clearScreen();
        displayMenu();
        cin >> choice;

        // Clear input buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                markCompleted();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                loadFromFile();
                break;
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
        cout << "\nPress Enter to continue...";
        cin.get();
    } while (choice != 7);

    return 0;
}