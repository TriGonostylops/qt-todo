#include "taskdialog.h"
#include "ui_taskdialog.h"

TaskDialog::TaskDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TaskDialog) {
    ui->setupUi(this);

    ui->dueDateEdit->setCalendarPopup(true);
    ui->dueDateEdit->setDate(QDate::currentDate());
}

TaskDialog::~TaskDialog() {
    delete ui;
}

void TaskDialog::setTask(const Task &task) {
    ui->titleEdit->setText(task.title);
    ui->dueDateEdit->setDate(task.dueDate);

    int index = 0;
    switch (task.status) {
        case Status::ToDo: index = 0; break;
        case Status::InProgress: index = 1; break;
        case Status::Done: index = 2; break;
    }
    ui->statusComboBox->setCurrentIndex(index);
}

Task TaskDialog::getTask() const {
    Task task;
    task.title = ui->titleEdit->text();
    task.dueDate = ui->dueDateEdit->date();
    switch (ui->statusComboBox->currentIndex()) {
        case 0: task.status = Status::ToDo; break;
        case 1: task.status = Status::InProgress; break;
        case 2: task.status = Status::Done; break;
    }
    return task;
}
