#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

struct Task {
    QString title;
    QDate dueDate;
    bool completed = false;
};

#endif // TASK_H
