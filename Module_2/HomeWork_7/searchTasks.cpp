#include "searchTasks.h"



void searchTasks(const QVector<Task> &tasks, const QString &keyword) {
    QVector<Task> foundTasks;

    for (const Task& task : tasks) {
        if (task.title.contains(keyword, Qt::CaseInsensitive)) {
            foundTasks.append(task);
        }
    }

    if (foundTasks.isEmpty()) {
        qDebug() << "Задачи с ключевым словом \"" << keyword << "\" не найдены.";
    } else {
        qDebug() << "Найденные задачи:";
        printTasks(foundTasks);
    }
}
