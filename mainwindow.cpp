#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Connect buttons
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::onAddTask);
    connect(ui->editTaskButton, &QPushButton::clicked, this, &MainWindow::onEditTask);
    connect(ui->deleteTaskButton, &QPushButton::clicked, this, &MainWindow::onDeleteTask);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onAddTask() {
    bool ok;
    QString text = QInputDialog::getText(this, "New Task", "Task title:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        Task t;
        t.title = text;
        t.dueDate = QDate::currentDate();
        tasks.append(t);
        refreshTaskList();
    }
}

void MainWindow::onEditTask() {
    int row = ui->taskListWidget->currentRow();
    if (row < 0 || row >= tasks.size()) return;

    Task &task = tasks[row];

    bool ok;
    QString text = QInputDialog::getText(this, "Edit Task", "Task title:", QLineEdit::Normal, task.title, &ok);
    if (ok && !text.isEmpty()) {
        task.title = text;
        refreshTaskList();
    }
}

void MainWindow::onDeleteTask() {
    int row = ui->taskListWidget->currentRow();
    if (row >= 0 && row < tasks.size()) {
        tasks.removeAt(row);
        refreshTaskList();
    }
}

void MainWindow::refreshTaskList() {
    ui->taskListWidget->clear();
    for (const Task &task : tasks) {
        ui->taskListWidget->addItem(task.title);
    }
}
