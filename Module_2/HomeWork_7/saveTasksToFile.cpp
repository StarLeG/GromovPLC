#include "saveTasksToFile.h"


void saveTasksToFile(const QVector<Task> &tasks, const QString filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Ошибка открытия файла для записи!";
        return;
    }

    QTextStream out(&file);
    for (const Task& task : tasks) {

        out << task.title << ";" << task.date.toString("dd.MM.yyyy") << ";" << task.priority << "\n";
    }
    file.close();
    qDebug() << "Задачи сохранены в файл:" << filename;
}
