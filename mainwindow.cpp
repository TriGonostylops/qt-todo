
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include "taskdialog.h"
#include <QDateEdit>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTask);
    connect(ui->editTaskButton, &QPushButton::clicked, this, &MainWindow::onEditTask);
    connect(ui->deleteTaskButton, &QPushButton::clicked, this, &MainWindow::onDeleteTask);
    connect(ui->todoListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onTaskDoubleClicked);
    connect(ui->inProgressListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onTaskDoubleClicked);
    connect(ui->doneListWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onTaskDoubleClicked);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onAddTask() {
    TaskDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Task task = dialog.getTask();
        tasks.append(task);
        refreshTaskList();
    }
}

void MainWindow::onEditTask() {
    QListWidget* source = nullptr;
    QListWidgetItem* currentItem = nullptr;

    if (ui->todoListWidget->currentItem()) {
        source = ui->todoListWidget;
        currentItem = source->currentItem();
    } else if (ui->inProgressListWidget->currentItem()) {
        source = ui->inProgressListWidget;
        currentItem = source->currentItem();
    } else if (ui->doneListWidget->currentItem()) {
        source = ui->doneListWidget;
        currentItem = source->currentItem();
    } else {
        return;
    }

    if (!currentItem) return;

    int taskIndex = currentItem->data(Qt::UserRole).toInt();
    if (taskIndex < 0 || taskIndex >= tasks.size()) return;

    TaskDialog dialog(this);
    dialog.setTask(tasks[taskIndex]);

    if (dialog.exec() == QDialog::Accepted) {
        tasks[taskIndex] = dialog.getTask();
        refreshTaskList();
    }
}

void MainWindow::onDeleteTask() {
    QListWidget* source = nullptr;
    QListWidgetItem* currentItem = nullptr;

    if (ui->todoListWidget->currentItem()) {
        source = ui->todoListWidget;
        currentItem = source->currentItem();
    } else if (ui->inProgressListWidget->currentItem()) {
        source = ui->inProgressListWidget;
        currentItem = source->currentItem();
    } else if (ui->doneListWidget->currentItem()) {
        source = ui->doneListWidget;
        currentItem = source->currentItem();
    } else {
        return; // no selection
    }

    if (!currentItem) return;

    int taskIndex = currentItem->data(Qt::UserRole).toInt();
    if (taskIndex < 0 || taskIndex >= tasks.size()) return;

    tasks.removeAt(taskIndex);
    refreshTaskList();
}

void MainWindow::refreshTaskList() {
    ui->todoListWidget->clear();
    ui->inProgressListWidget->clear();
    ui->doneListWidget->clear();

    for (int i = 0; i < tasks.size(); ++i) {
        const Task &task = tasks[i];
        QString itemText = QString("%1 [%2]")
                               .arg(task.title)
                               .arg(task.dueDate.toString("yyyy-MM-dd"));

        QListWidgetItem* item = new QListWidgetItem(itemText);
        item->setData(Qt::UserRole, i);  // Store index in task list

        switch (task.status) {
        case Status::ToDo:
            ui->todoListWidget->addItem(item);
            break;
        case Status::InProgress:
            ui->inProgressListWidget->addItem(item);
            break;
        case Status::Done:
            ui->doneListWidget->addItem(item);
            break;
        }
    }
}
void MainWindow::onTaskDoubleClicked(QListWidgetItem* item) {
    if (!item) return;

    QListWidget* senderList = qobject_cast<QListWidget*>(sender());
    if (!senderList) return;

    // Determine the index in the master `tasks` list
    int index = -1;
    QString text = item->text();

    for (int i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];

        QString taskLabel = QString("%1 [%2]").arg(task.title).arg(task.dueDate.toString("yyyy-MM-dd"));
        if (taskLabel == text) {
            // Ensure it's from the correct list
            if ((senderList == ui->todoListWidget && task.status == Status::ToDo) ||
                (senderList == ui->inProgressListWidget && task.status == Status::InProgress) ||
                (senderList == ui->doneListWidget && task.status == Status::Done)) {
                index = i;
                break;
            }
        }
    }

    if (index >= 0 && index < tasks.size()) {
        TaskDialog dialog(this);
        dialog.setTask(tasks[index]);
        dialog.setWindowTitle("View Task");

        dialog.findChild<QLineEdit*>("titleEdit")->setEnabled(false);
        dialog.findChild<QDateEdit*>("dueDateEdit")->setEnabled(false);
        dialog.findChild<QComboBox*>("statusComboBox")->setEnabled(false);
        dialog.findChild<QLineEdit*>("newTagLineEdit")->setEnabled(false);
        dialog.findChild<QPushButton*>("addTagButton")->setEnabled(false);
        dialog.findChild<QPushButton*>("removeTagButton")->setEnabled(false);
        dialog.findChild<QListWidget*>("tagsListWidget")->setEnabled(false);

        dialog.exec();
    }
}
