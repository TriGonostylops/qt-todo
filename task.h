#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>

enum class Status {
    ToDo,
    InProgress,
    Done
};

struct Task {
    QString title;
    QDate dueDate;
    Status status;
    QStringList tags;

    QJsonObject toJson() const {
        QJsonObject obj;
        obj["title"] = title;
        obj["dueDate"] = dueDate.toString(Qt::ISODate);
        obj["status"] = static_cast<int>(status);

        QJsonArray tagArray;
        for (const QString &tag : tags) tagArray.append(tag);
        obj["tags"] = tagArray;

        return obj;
    }

    static Task fromJson(const QJsonObject &obj) {
        Task t;
        t.title = obj["title"].toString();
        t.dueDate = QDate::fromString(obj["dueDate"].toString(), Qt::ISODate);
        t.status = static_cast<Status>(obj["status"].toInt());

        QJsonArray tagArray = obj["tags"].toArray();
        for (const QJsonValue &val : tagArray)
            t.tags.append(val.toString());

        return t;
    }
};

#endif // TASK_H
