#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddTask();
    void onEditTask();
    void onDeleteTask();
    void onTaskDoubleClicked(QListWidgetItem* item);
    void onSave();
    void onLoad();

private:
    Ui::MainWindow *ui;
    QList<Task> tasks;

    void refreshTaskList();
    void saveToFile(const QString &fileName);
    void loadFromFile(const QString &fileName);

};

#endif // MAINWINDOW_H
