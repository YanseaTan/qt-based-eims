#include "MainWidget.h"
#include<QDebug>

MainWidget::MainWidget()
{
    setWindowTitle("职工信息管理系统");
    this->resize(1000,600);

    //创建水平布局
    QHBoxLayout *HBoxLayout = new QHBoxLayout(this);

    //创建两个面板框
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
    //刷新表格信息
    flushTable();
    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;
    AutoHBoxLayout->addWidget(TableWidget);
    box->setLayout(AutoHBoxLayout);

    connect(TableWidget, &QTableWidget::cellClicked, this, &MainWidget::flushListWidget);
    connect(TableWidget, &QTableWidget::cellChanged, this, &MainWidget::changeEmpMess);
    connect(TableWidget, &QTableWidget::cellChanged, this, &MainWidget::flushListWidget);
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

    connect(AddEmpBtn, &QPushButton::clicked, this, &MainWidget::addEmpBox);
    connect(ExitBtn, &QPushButton::clicked, this, &MainWidget::close);
    return box;
}

void MainWidget::addEmpBox()
{
    messBox = new EditEmpMessBox;
    QObject::connect(messBox, &EditEmpMessBox::closeBox, this, &MainWidget::flushTable);
    QObject::connect(messBox, &EditEmpMessBox::closeBox, ListWidget, &QListWidget::clear);
    messBox->exec();
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

void MainWidget::flushListWidget(int row)
{

}

void MainWidget::delEmpMess()
{

}

void MainWidget::findEmpMess()
{

}

void MainWidget::changeEmpMess(int row)
{

}

void MainWidget::saveEmpMess()
{

}
