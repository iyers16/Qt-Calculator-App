#include "calculator.h"
#include "./ui_calculator.h"
#include <QRegularExpression>
double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool subTrigger = false;
bool addTrigger = false;
const int numberOfNumbers = 10;
Calculator::Calculator(QWidget *parent) : QMainWindow(parent) , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[numberOfNumbers];

    for (int i = 0; i < numberOfNumbers ; ++i )
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearDisplay()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    QString val = ((displayVal.toDouble() == 0)||(displayVal.toDouble() == 0.0)) ? butVal : displayVal+butVal;
    ui->Display->setText(val);
//    if(
//       (displayVal.toDouble() == 0)||
//       (displayVal.toDouble() == 0.0)
//      )
//    {
//        ui->Display->setText(butVal);
//    }
//    else
//    {
//        double dblNewVal = (displayVal + butVal).toDouble();
//        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
//        ui->Display->setText(displayVal+butVal);
//    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = mulTrigger = addTrigger = subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        mulTrigger = true;
    }
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }

    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger ||
       subTrigger ||
       mulTrigger ||
       divTrigger )
    {
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        }
        else if(subTrigger)
        {
            solution = calcVal - dblDisplayVal;
        }
        else if(mulTrigger)
        {
            solution = calcVal * dblDisplayVal;
        }
        else
        {
            solution = calcVal / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));

}

void Calculator::ChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-+]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch())
    {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearDisplay()
{
    ui->Display->setText(QString::number(0.0));
}
