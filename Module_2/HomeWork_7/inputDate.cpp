
#include "inputDate.h"

QDate inputDate()
{
    while (true) {
        QString dateStr;
        QTextStream(stdin) >> dateStr;
        QDate date = QDate::fromString(dateStr, "dd.MM.yyyy");

        if (date.isValid()) {
            return date;
        }
        qDebug() << "Неверный формат даты. Попробуйте снова (ДД.ММ.ГГГГ):";
    }

}
