#ifndef MENU_H
#define MENU_H

#include "inputDate.h"
#include "main.h"
#include "inputPriority.h"
#include "printTasks.h"
#include "editTask.h"
#include "searchTasks.h"
#include "saveTasksToFile.h"



enum Menu{
    AddTask = 1,
    ViewTasks,
    DeleteTask,
    EditTask,
    SearchTasks,
    LogOut
};


int menu(QVector<Task> &tasks, const QString filename);


#endif // MENU_H
