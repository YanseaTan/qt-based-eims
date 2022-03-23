#include "MainWidget.h"
#include<QDebug>

MainWidget::MainWidget()
{
    setWindowIcon(QIcon(":/logo.ico"));
    setWindowTitle("职工信息管理系统");
    this->resize(1020,600);

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

    connect(FindEmpEdit, &QLineEdit::returnPressed, this, &MainWidget::findEmpMess);
    connect(AddEmpBtn, &QPushButton::clicked, this, &MainWidget::addEmpBox);
    connect(DelEmpBtn, &QPushButton::clicked, this, &MainWidget::delEmpMess);
    connect(SaveBtn, &QPushButton::clicked, this, &MainWidget::saveEmpMess);
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
    QTextStream textStr(&file);
    QString id, name, sex, dept, tel, email;
    TableWidget->setRowCount(0);
    while(!textStr.atEnd())
    {
        TableWidget->setRowCount(TableWidget->rowCount()+1);
        textStr>>id>>name>>sex>>dept>>tel>>email;
        TableWidget->setItem(TableWidget->rowCount()-1,0,new QTableWidgetItem(id));
        TableWidget->setItem(TableWidget->rowCount()-1,1,new QTableWidgetItem(name));
        TableWidget->setItem(TableWidget->rowCount()-1,2,new QTableWidgetItem(sex));
        TableWidget->setItem(TableWidget->rowCount()-1,3,new QTableWidgetItem(dept));
        TableWidget->setItem(TableWidget->rowCount()-1,4,new QTableWidgetItem(tel));
        TableWidget->setItem(TableWidget->rowCount()-1,5,new QTableWidgetItem(email));
    }
    file.close();
    connect(TableWidget, &QTableWidget::cellChanged, this, &MainWidget::changeEmpMess);
    connect(TableWidget, &QTableWidget::cellChanged, this, &MainWidget::flushListWidget);
}

void MainWidget::flushListWidget(int row)
{
    if(ListWidget->count() > 0)
    {
        ListWidget->item(0)->setText("工 号：" + TableWidget->item(row, 0)->text());
        ListWidget->item(1)->setText("姓 名：" + TableWidget->item(row, 1)->text());
        ListWidget->item(2)->setText("性 别：" + TableWidget->item(row, 2)->text());
        ListWidget->item(3)->setText("职 级：" + TableWidget->item(row, 3)->text());
        ListWidget->item(4)->setText("电 话：" + TableWidget->item(row, 4)->text());
        ListWidget->item(5)->setText("邮 箱：" + TableWidget->item(row, 5)->text());
    }
    else
    {
        ListWidget->addItem("工 号：" + TableWidget->item(row, 0)->text());
        ListWidget->addItem("姓 名：" + TableWidget->item(row, 1)->text());
        ListWidget->addItem("性 别：" + TableWidget->item(row, 2)->text());
        ListWidget->addItem("职 级：" + TableWidget->item(row, 3)->text());
        ListWidget->addItem("电 话：" + TableWidget->item(row, 4)->text());
        ListWidget->addItem("邮 箱：" + TableWidget->item(row, 5)->text());
    }
}

void MainWidget::delEmpMess()
{
    QList<QTableWidgetItem*>items = TableWidget->selectedItems();
    if(items.count() > 0)
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "删除", "确定要删除工号为【" + items.at(0)->text() + "】的职工吗？");
        if(result == QMessageBox::Yes)
        {
            QString ID, name, sex, dept, tel, email;
            QFile file(FILE_NAME);
            file.open(QIODevice::ReadOnly);
            QTextStream readTextStr(&file);

            QFile tempFile(TEMP_FILE_NAME);
            tempFile.open(QIODevice::WriteOnly);
            QTextStream writeTextStr(&tempFile);

            while(!readTextStr.atEnd())
            {
                readTextStr >> ID >> name >> sex >> dept >> tel >> email;
                if(ID != items.at(0)->text())
                {
                    writeTextStr << ID << " " << name << " " << sex << " " << dept << " " << tel << " " << email << "\t";
                }
            }

            tempFile.close();
            file.close();
            file.remove();
            tempFile.rename(FILE_NAME);
            flushTable();
            ListWidget->clear();
        }
    }
    else
    {
        QMessageBox::warning(this, "提示", "请选择要删除的职工");
    }
}

void MainWidget::findEmpMess()
{
    //获得当前表格行数
    qint32 count = TableWidget->rowCount();
    bool findSuccess = false;
    if(count > 0)
    {
        for(qint32 i = 0; i < count; i++)
        {
            QString name = TableWidget->item(i, 1)->text();
            if(name == FindEmpEdit->text())
            {
                findSuccess = true;
                TableWidget->selectRow(i);
                flushListWidget(i);
                break;
            }
        }
        if(findSuccess == false)
        {
            QMessageBox::information(this, "查找失败", "当前表格中没有【" + FindEmpEdit->text() + "】职工");
        }
    }
}

void MainWidget::changeEmpMess(int row)
{
    QString ID, name, sex, dept, tel, email;
    QString empName = TableWidget->item(row, 1)->text();
    QFile file(FILE_NAME);
    file.open(QIODevice::ReadOnly);
    QTextStream readTextStr(&file);

    QFile tempFile(TEMP_FILE_NAME);
    tempFile.open(QIODevice::WriteOnly);
    QTextStream writeTextStr(&tempFile);

    while(!readTextStr.atEnd())
    {
        readTextStr >> ID >> name >> sex >> dept >> tel >> email;
        //如果当前行不是要修改的那行，就从原文件读到的数据进行写入
        if(name != empName)
        {
            writeTextStr << ID << " " << name << " " << sex << " " << dept << " " << tel << " " << email << "\t";
        }
        //如果当前行是要修改的那行，就从表格中那行的数据进行写入
        else
        {
            for(int i = 0; i < TableWidget->columnCount(); i++)
            {
                writeTextStr << TableWidget->item(row, i)->text() << " ";
            }
        }
    }

    tempFile.close();
    file.close();
    file.remove();
    tempFile.rename(FILE_NAME);
}

void MainWidget::saveEmpMess()
{
    QFile file(FILE_NAME);
    file.open(QIODevice::WriteOnly);
    QTextStream textStr(&file);

    for(int i = 0; i < TableWidget->rowCount(); i++)
    {
        for(int j = 0; j < TableWidget->columnCount(); j++)
        {
            textStr << TableWidget->item(i, j)->text() << " ";
        }
        textStr << "\n";
    }
    file.close();
    QMessageBox::information(this, "保存", "保存成功！");
}
