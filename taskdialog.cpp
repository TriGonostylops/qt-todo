#include "taskdialog.h"
#include "ui_taskdialog.h"

TaskDialog::TaskDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::TaskDialog) {
    ui->setupUi(this);

    ui->dueDateEdit->setCalendarPopup(true);
    ui->dueDateEdit->setDate(QDate::currentDate());

    connect(ui->addTagButton, &QPushButton::clicked, this, &TaskDialog::onAddTag);
    connect(ui->removeTagButton, &QPushButton::clicked, this, &TaskDialog::onRemoveTag);
}

TaskDialog::~TaskDialog() {
    delete ui;
}

void TaskDialog::setTask(const Task &task) {
    ui->titleEdit->setText(task.title);
    ui->dueDateEdit->setDate(task.dueDate);
    ui->statusComboBox->setCurrentIndex(static_cast<int>(task.status));

    ui->tagsListWidget->clear();
    for (const QString &tag : task.tags) {
        ui->tagsListWidget->addItem(tag);
    }
}

Task TaskDialog::getTask() const {
    Task t;
    t.title = ui->titleEdit->text();
    t.dueDate = ui->dueDateEdit->date();
    t.status = static_cast<Status>(ui->statusComboBox->currentIndex());

    QStringList tags;
    for (int i = 0; i < ui->tagsListWidget->count(); ++i) {
        tags << ui->tagsListWidget->item(i)->text();
    }
    t.tags = tags;

    return t;
}

void TaskDialog::onAddTag() {
    QString newTag = ui->newTagLineEdit->text().trimmed();
    if (!newTag.isEmpty()) {
        // Prevent duplicates
        bool exists = false;
        for (int i = 0; i < ui->tagsListWidget->count(); ++i) {
            if (ui->tagsListWidget->item(i)->text().compare(newTag, Qt::CaseInsensitive) == 0) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            ui->tagsListWidget->addItem(newTag);
            ui->newTagLineEdit->clear();
        }
    }
}

void TaskDialog::onRemoveTag() {
    QListWidgetItem *item = ui->tagsListWidget->currentItem();
    if (item) {
        delete item;
    }
}
