#include "editTask.h"


void editTask(Task &task) {
    QTextStream stream(stdin);

    qDebug() << "Текущее название (" << task.title << "). Новое название (Enter - оставить):";
    QString newTitle = QTextStream(stdin).readLine().trimmed();
    if (!newTitle.isEmpty()) {
        task.title = newTitle;
    }

    qDebug() << "Текущая дата (" << task.date.toString("dd.MM.yyyy") << "). Новая дата (Enter - оставить):";
    QString dateStr = QTextStream(stdin).readLine().trimmed();
    if (!dateStr.isEmpty()) {
        task.date = QDate::fromString(dateStr, "dd.MM.yyyy");
    }

    qDebug() << "Текущий приоритет (" << task.priority << "). Новый приоритет (Enter - оставить):";
    QString priorityStr = stream.readLine().trimmed();
    if (!priorityStr.isEmpty()) {
        while (true) {
            bool ok;
            int newPriority = priorityStr.toInt(&ok);
            if (ok && newPriority >= 1 && newPriority <= 3) {
                task.priority = newPriority;
                break;
            }
            qDebug() << "Приоритет должен быть 1-3. Попробуйте снова:";
            priorityStr = stream.readLine().trimmed();
        }
    }
}
