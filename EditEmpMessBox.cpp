#include "EditEmpMessBox.h"

EditEmpMessBox::EditEmpMessBox()
{
    setWindowTitle("添加职工信息");
    QVBoxLayout * VBox = new QVBoxLayout;

    QFormLayout * FormLayout = new QFormLayout;
    ID = new QLineEdit;
    name = new QLineEdit;
    sex = new QLineEdit;
    dept = new QLineEdit;
    tel = new QLineEdit;
    email = new QLineEdit;

}
