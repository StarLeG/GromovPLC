#include "calculator.h"

Calculator::Calculator()
    : val1(0.), val2(0.), result(0.), oper(Operation::None),
    lastOper(Operation::None), isDecimal(false), decimalPlaces(0),
    isCalculated(false), displayString("0"), mem(0.) {}

int Calculator::reset()
{
    val1 = 0.;
    val2 = 0.;
    oper = Operation::None;
    lastOper = Operation::None;
    result = 0.;
    isCalculated = false;
    displayString = "0";

    return 0;
}

int Calculator::digit(int d)
{
    if (isCalculated) {
        reset();
    }

    if (!isDecimal) {
        if (oper == Operation::None) {
            val1 = val1 * 10 + d;
            result = val1;
        } else {
            val2 = val2 * 10 + d;
            result = val2;
        }
    } else {
        if (oper == Operation::None) {
            val1 = val1 + d / pow(10, ++decimalPlaces);
            result = val1;
        } else {
            val2 = val2 + d / pow(10, ++decimalPlaces);
            result = val2;
        }
    }

    isCalculated = false;
    updateDisplayString();

    return 0;
}

int Calculator::operation(Operation o)
{
    if (isCalculated) {
        val1 = result;
        val2 = 0.;
    }

    oper = o;
    lastOper = o;
    isDecimal = false;
    decimalPlaces = 0;
    isCalculated = false;
    updateDisplayString();
    return 0;
}

int Calculator::calculate()
{
    if (oper == Operation::None && lastOper != Operation::None) {
        oper = lastOper;
    }

    switch (oper) {
    case Operation::Add:
        result = val1 + val2;
        break;
    case Operation::Subtract:
        result = val1 - val2;
        break;
    case Operation::Multiply:
        result = val1 * val2;
        break;
    case Operation::Divide:
        if (val2 != 0) {
            result = val1 / val2;
        } else {
            result = 0;
        }
        break;
    default:
        result  = 0;
        break;
    }


    val1 = result;
    //val2 = 0.;
    isCalculated = true;

    if (isCalculated) {
        displayString = QString::number(result, 'g', 10);
    } else {
        updateDisplayString();
    }

    return 0;
}

int Calculator::changeSign()
{
    if (oper == Operation::None) {
        val1 = -val1;
        result = val1;
    } else {
        val2 = -val2;
        result = val2;
    }

    updateDisplayString();
    return 0;
}

void Calculator::setDecimal()
{
    isDecimal = true;
    decimalPlaces = 0;
}

void Calculator::backspace()
{
    QString currentValue = QString::number(result, 'g', 10);

    if (currentValue.length() > 0) {
        currentValue.chop(1);
        if (currentValue.isEmpty()) {
            currentValue = "0";
        }

        if (oper == Operation::None) {
            val1 = currentValue.toDouble();
            result = val1;
        } else {
            val2 = currentValue.toDouble();
            result = val2;
        }

        updateDisplayString();
    }
}


QString Calculator::getDisplayString()
{
    return displayString;
}

void Calculator::updateDisplayString()
{
    if (oper == Operation::None) {
        displayString = QString::number(val1, 'g', 10);
    } else {
        QString operationSymbol;
        switch (oper) {
        case Operation::Add:
            operationSymbol = "+";
            break;
        case Operation::Subtract:
            operationSymbol = "-";
            break;
        case Operation::Multiply:
            operationSymbol = "*";
            break;
        case Operation::Divide:
            operationSymbol = "/";
            break;
        default:
            operationSymbol = "";
            break;
        }
        displayString = QString::number(val1, 'g', 10) + " " + operationSymbol + " " + QString::number(val2, 'g', 10);
    }
}

int Calculator::percentage()
{
    if (oper == Operation::None) {
        val1 = val1 / 100;
        result = val1;
    } else {
        val2 = val1 * val2 / 100;
        result = val2;
    }

    updateDisplayString();
    return 0;
}


void Calculator::memory()
{
    mem = result;
    qDebug() << "Memory1 = " << mem;
}



void Calculator::memoryRecall()
{
    val2 = mem;
    updateDisplayString();
}

void Calculator::memoryClear()
{
    mem = 0.;
}
