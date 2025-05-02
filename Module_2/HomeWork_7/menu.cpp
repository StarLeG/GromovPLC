#include "menu.h"
#include "qglobal.h"



int menu(QVector<Task> &tasks, const QString filename)
{
    qDebug() << "\n\tМеню:";
    qDebug() << "______________________";
    qDebug() << "1. Добавить задачу";
    qDebug() << "2. Просмотреть задачи";
    qDebug() << "3. Удалить задачу";
    qDebug() << "4. Редактировать задачу";
    qDebug() << "5. Поиск задач";
    qDebug() << "6. Выйти";
    qDebug() << "______________________";
    qDebug() << "Выберите действие:";


    QTextStream stream(stdin);
    QString choiceStr;
    stream >> choiceStr;
    bool ok;
    int choice = choiceStr.toInt(&ok);

    if (!ok || choice < 1 || choice > 6) {
        qDebug() << "Неверный ввод. Пожалуйста, введите число от 1 до 6.";
        stream.readLine();

    }

    switch (choice) {
    case Menu::AddTask:{ // Добавление задачи
        Task newTask;
        qDebug() << "Введите название задачи:";
        newTask.title = QTextStream(stdin).readLine().trimmed();

        qDebug() << "Введите дату выполнения (ДД.ММ.ГГГГ):";
        newTask.date = inputDate();

        qDebug() << "Введите приоритет (1-3):";
        newTask.priority = inputPriority();


        tasks.append(newTask);
        qDebug() << "Задача добавлена!";
        break;
    }
    case Menu::ViewTasks:{ // Просмотр задач
        printTasks(tasks);
        break;
    }
    case Menu::DeleteTask:{ // Удаление задач
        printTasks(tasks);
        if (tasks.isEmpty()) {
            break;
        }

        qDebug() << "Введите номер задачи для удаления:";
        int index;
        QTextStream(stdin) >> index;

        if (index >= 1 && index <= tasks.size()) {
            tasks.removeAt(index - 1);
            qDebug() << "Задача удалена!";
        } else {
            qDebug() << "Неверный номер задачи!";
        }
        break;
    }
    case Menu::EditTask:{ // Редактирование задач
        printTasks(tasks);
        if (tasks.isEmpty()) {
            break;
        }

        qDebug() << "Введите номер задачи для редактирования:";
        int index;
        QTextStream(stdin) >> index;

        if (index >= 1 && index <= tasks.size()) {
            editTask(tasks[index - 1]);
            qDebug() << "Задача обновлена!";
        } else {
            qDebug() << "Неверный номер задачи!";
        }

        break;
    }
    case Menu::SearchTasks: { // Поиск задач
        qDebug() << "Введите ключевое слово для поиска:";
        QTextStream(stdin).readLine();  // Очистка буфера
        QString keyword = QTextStream(stdin).readLine().trimmed();

        searchTasks(tasks, keyword);
        break;
    }
    case Menu::LogOut:{  // Выход из программы
        qDebug() << "Сохранение задач в файл...";
        saveTasksToFile(tasks, filename);
        qDebug() << "Выход из программы.";
        return 1;
    }
    default:{
        qDebug() << "Неверный выбор. Попробуйте снова.";
        break;
    }
    }
    return 0;
}
