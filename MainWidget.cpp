#include "MainWidget.h"
#include<QDebug>

MainWidget::MainWidget()
{
    setWindowTitle("职工信息管理系统");
    this->resize(1000,600);

    //创建水平布局
    QHBoxLayout *HBoxLayout = new QHBoxLayout(this);

    //创建两个分组框
    QGroupBox *Left_Box = createEmpMess();
    QGroupBox *Right_Box = createMenu();

    //拉伸系数比为2：1
    HBoxLayout->addWidget(Left_Box,2);
    HBoxLayout->addWidget(Right_Box,1);
}

QGroupBox * MainWidget::createEmpMess()
{
    QGroupBox * box = new QGroupBox("职工信息");
    TableWidget = new QTableWidget;
    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    TableWidget->setColumnCount(6);
    TableWidget->setHorizontalHeaderLabels(QStringList() <<"工号"<<"姓名"<<"性别"<<"职级"<<"电话"<<"邮箱");
    //见尾部自定义的刷新表格函数
    flushTable();
    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;
    AutoHBoxLayout->addWidget(TableWidget);
    box->setLayout(AutoHBoxLayout);

    return box;
}

QGroupBox * MainWidget::createMenu()
{
    QGroupBox * box = new QGroupBox("功能面板");
    QVBoxLayout * VBoxLayout = new QVBoxLayout;

    ListWidget = new QListWidget;
    QGridLayout * Buts = new QGridLayout;
    AddEmpBtn = new QPushButton("添加");
    DelEmpBtn = new QPushButton("删除");
    SaveBtn = new QPushButton("保存");
    ExitBtn = new QPushButton("退出");
    FindEmpEdit = new QLineEdit;
    FindEmpEdit->setPlaceholderText("输入职工姓名查找...");
    FindEmpEdit->setClearButtonEnabled(true);
    FindEmpEdit->setStyleSheet("QLineEdit{padding:3,3,3,3;}");
    Buts->addWidget(AddEmpBtn,0,0);
    Buts->addWidget(DelEmpBtn,0,1);
    Buts->addWidget(SaveBtn,1,0);
    Buts->addWidget(ExitBtn,1,1);

    //添加单个部件用addWidget()，添加一个本就是布局的组合用addLayout()
    VBoxLayout->addWidget(FindEmpEdit);
    VBoxLayout->addWidget(ListWidget);
    VBoxLayout->addLayout(Buts);
    box->setLayout(VBoxLayout);

    return box;
}

void MainWidget::flushTable()
{
    disconnect(TableWidget, &QTableWidget::cellChanged,0,0);
    QFile file(FILE_NAME);
    file.open(QIODevice::ReadOnly);
    QDataStream dataStr(&file);
    QString id, name, sex, dept, tel, email;
    TableWidget->setRowCount(0);
    while(!dataStr.atEnd())
    {
        TableWidget->setRowCount(TableWidget->rowCount()+1);
        dataStr>>id>>name>>sex>>dept>>tel>>email;
        TableWidget->setItem(TableWidget->rowCount()-1,0,new QTableWidgetItem(id));
        TableWidget->setItem(TableWidget->rowCount()-1,1,new QTableWidgetItem(name));
        TableWidget->setItem(TableWidget->rowCount()-1,2,new QTableWidgetItem(sex));
        TableWidget->setItem(TableWidget->rowCount()-1,3,new QTableWidgetItem(dept));
        TableWidget->setItem(TableWidget->rowCount()-1,4,new QTableWidgetItem(tel));
        TableWidget->setItem(TableWidget->rowCount()-1,5,new QTableWidgetItem(email));
        file.close();


    }
}
