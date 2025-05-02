#include "printTasks.h"

void printTasks(const QVector<Task> &tasks) {
    if (tasks.isEmpty()) {
        qDebug() << "Список задач пуст.";
        return;
    }

    qDebug() << "\nСписок задач:";
    for (int i = 0; i < tasks.size(); ++i) {
        const Task& task = tasks[i];
        qDebug() << "Задача #" << i + 1 << ":";
        qDebug() << "  Название:" << task.title;
        qDebug() << "  Дата:" << task.date.toString("dd.MM.yyyy");
        qDebug() << "  Приоритет:" << task.priority;
        qDebug() << "------------------";
    }
}

