#include "inputPriority.h"




int inputPriority() {
    while (true) {
        int priority;
        QTextStream(stdin) >> priority;

        if (priority >= 1 && priority <= 3) {
            return priority;
        }
        qDebug() << "Приоритет должен быть 1-3. Попробуйте снова:";
    }
}
