#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>
enum class Status {
    ToDo,
    InProgress,
    Done
};
struct Task {
    QString title;
    QDate dueDate;
    Status status;
};

#endif // TASK_H
