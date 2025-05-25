#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include "task.h"

namespace Ui {
class TaskDialog;
}

class TaskDialog : public QDialog {
    Q_OBJECT

public:
    explicit TaskDialog(QWidget *parent = nullptr);
    ~TaskDialog();

    void setTask(const Task &task);
    Task getTask() const;

private slots:
    void onAddTag();
    void onRemoveTag();

private:
    Ui::TaskDialog *ui;
};

#endif // TASKDIALOG_H
