#include "loadTasksFromFile.h"


void loadTasksFromFile(QVector<Task> &tasks, const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Файл не найден. Будет создан новый список задач.";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(";");

        if (parts.size() == 3) {
            Task task;
            task.title = parts[0];
            task.date = QDate::fromString(parts[1], "dd.MM.yyyy");
            task.priority = parts[2].toInt();

            tasks.append(task);
        }
    }
    file.close();
    qDebug() << "Задачи загружены из файла:" << filename;
}
