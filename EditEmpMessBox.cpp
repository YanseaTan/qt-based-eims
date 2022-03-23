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
    FormLayout->addRow("工号：",ID);
    FormLayout->addRow("姓名：",name);
    FormLayout->addRow("性别：",sex);
    FormLayout->addRow("职级：",dept);
    FormLayout->addRow("电话：",tel);
    FormLayout->addRow("邮箱：",email);
    //标签有足够的空间适应，如果最小大小比可用空间大，输入框会被换到下一行
    FormLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);

    QHBoxLayout * HBox = new QHBoxLayout;
    submit = new QPushButton("提交");
    cancel = new QPushButton("取消");
    HBox->addWidget(submit);
    HBox->addWidget(cancel);

    VBox->addLayout(FormLayout,4);
    VBox->addLayout(HBox,1);
    this->setLayout(VBox);

    QObject::connect(submit, &QPushButton::clicked, this, &EditEmpMessBox::saveEmpMess);
    QObject::connect(cancel, &QPushButton::clicked, this, &EditEmpMessBox::close);
}

void EditEmpMessBox::saveEmpMess()
{
    if(this->ID->text() != "" && this->name->text() != "" && this->sex->text() != "" && this->dept->text() != "" && this->tel->text() != "" && this->email->text() != "")
    {
        Employee emp;
        emp.setID(this->ID->text());
        emp.setName(this->name->text());
        emp.setSex(this->sex->text());
        emp.setDept(this->dept->text());
        emp.setTel(this->tel->text());
        emp.setEmail(this->email->text());

        QFile file(FILE_NAME);
        file.open(QIODevice::WriteOnly|QIODevice::Append);
        QDataStream dataStr(&file);
        dataStr << emp.getID() << emp.getName() << emp.getSex() << emp.getDept() << emp.getTel() << emp.getEmail();
        file.close();
        this->close();
        emitCloseBox();
    }
    else
    {
        QMessageBox::warning(this, "提示", "请将信息填写完整", QMessageBox::Ok);
    }
}

void EditEmpMessBox::emitCloseBox()
{
    emit closeBox();
}
