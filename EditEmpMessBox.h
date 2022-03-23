#ifndef EDITEMPMESSBOX_H
#define EDITEMPMESSBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "Tool.h"
#include "Employee.h"

class EditEmpMessBox : public QDialog
{
    Q_OBJECT
public:
    EditEmpMessBox();
signals:
    void closeBox();
public slots:
    void saveEmpMess();
public:
    //发出 closeBox 信号
    void emitCloseBox();
private:
    QLineEdit * ID;
    QLineEdit * name;
    QLineEdit * sex;
    QLineEdit * dept;
    QLineEdit * tel;
    QLineEdit * email;
    QPushButton * submit;
    QPushButton * cancel;
};

#endif // EDITEMPMESSBOX_H
