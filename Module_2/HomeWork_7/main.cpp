#include "main.h"
#include "menu.h"
#include "loadTasksFromFile.h"


int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Rus");
    QCoreApplication a(argc, argv);
    QVector<Task> tasks;  // Вектор для хранения задач
    const QString filename = "tasks.dat";
    loadTasksFromFile(tasks, filename);



    while(true){
        int exit = menu(tasks, filename);
        if(exit == 1) break;
    }


    return a.exec();
}
