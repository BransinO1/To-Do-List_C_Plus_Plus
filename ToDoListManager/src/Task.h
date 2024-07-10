#ifndef TASK_H
#define TASK_H

#include <string>

// Class outline for task, sets up private and public parts and constructors and methods
class Task {
private:
    std::string description;
    bool completed;

public:
    // Constructor
    Task(const std::string& desc);

    // Methods
    std::string getDescription() const;
    void setDescription(const std::string& desc);
    bool isCompleted() const;
    void markCompleted();
};

#endif // TASK_H
