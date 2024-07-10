#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Task.h"

using namespace std;

// Function prototypes
void printMenu();
void addTask(vector<Task>& tasks);
void removeTask(vector<Task>& tasks);
void viewTasks(const vector<Task>& tasks);
void saveTasksToFile(const vector<Task>& tasks, const string& filename);
void loadTasksFromFile(vector<Task>& tasks, const string& filename);

// Function that outlines main menu and directs user input to correct action
int main() {
    vector<Task> tasks;
    int choice;
    string filename; // Variable to hold file name

    // Load tasks from file at the beginning
    cout << "Enter file name to load tasks from: ";
    cin >> filename;
    loadTasksFromFile(tasks, filename);

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addTask(tasks);
                break;
            case 2:
                removeTask(tasks);
                break;
            case 3:
                viewTasks(tasks);
                break;
            case 4:
                cout << "Enter file name to save tasks to: ";
                cin >> filename;
                saveTasksToFile(tasks, filename); // Save tasks to file
                break;
            case 5:
                cout << "Enter file name to load tasks from: ";
                cin >> filename;
                loadTasksFromFile(tasks, filename); // Load tasks from file
                break;
            case 6:
                saveTasksToFile(tasks, filename); // Save tasks to file before exiting
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

// Function to print menu to user when they start program
void printMenu() {
    cout << "\nTo-Do List Manager\n";
    cout << "------------------\n";
    cout << "1. Add Task\n";
    cout << "2. Remove Task\n";
    cout << "3. View Tasks\n";
    cout << "4. Save Tasks\n";
    cout << "5. Load Tasks\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

// Function to add tasks to the user's generated list
void addTask(vector<Task>& tasks) {
    string description;
    cout << "Enter task description: ";
    cin.ignore();
    getline(cin, description);
    Task newTask(description);
    tasks.push_back(newTask);
    cout << "Task added successfully.\n";
}

// Function to remove tasks from user's generated list
void removeTask(vector<Task>& tasks) {
    int index;
    cout << "Enter index of task to remove (1-" << tasks.size() << "): ";
    cin >> index;

    if (index >= 1 && index <= tasks.size()) {
        tasks.erase(tasks.begin() + index - 1);
        cout << "Task removed successfully.\n";
    } else {
        cout << "Invalid index. No task removed.\n";
    }
}

// Function to list the complete view of tasks for the user
void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
    } else {
        cout << "Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". ";
            cout << tasks[i].getDescription();
            if (tasks[i].isCompleted()) {
                cout << " (Completed)";
            }
            cout << "\n";
        }
    }
}

// Function to save the user's generated list to a filename
void saveTasksToFile(const vector<Task>& tasks, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& task : tasks) {
            outFile << task.getDescription() << "," << (task.isCompleted() ? "1" : "0") << "\n";
        }
        outFile.close();
        cout << "Tasks saved to file '" << filename << "'.\n";
    } else {
        cout << "Unable to open file '" << filename << "' to save tasks.\n";
    }
}

// Function to load a generated list that the user selects. 
void loadTasksFromFile(vector<Task>& tasks, const string& filename) {
    tasks.clear(); // Clear existing tasks before loading from file
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string description, completedStr;
            getline(ss, description, ',');
            getline(ss, completedStr, ',');
            bool completed = (completedStr == "1");
            tasks.emplace_back(description);
            if (completed) {
                tasks.back().markCompleted();
            }
        }
        inFile.close();
        cout << "Tasks loaded from file '" << filename << "'.\n";
    } else {
        cout << "Unable to open file '" << filename << "' to load tasks.\n";
    }
}

