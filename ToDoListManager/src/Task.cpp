#include "Task.h"

// Constructor
Task::Task(const std::string& desc) : description(desc), completed(false) {}

// Getter for description
std::string Task::getDescription() const {
    return description;
}

// Setter for description
void Task::setDescription(const std::string& desc) {
    description = desc;
}

// Getter for completed status
bool Task::isCompleted() const {
    return completed;
}

// Mark task as completed
void Task::markCompleted() {
    completed = true;
}
