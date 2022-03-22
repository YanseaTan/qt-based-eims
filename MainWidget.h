#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFile>
#include <QDataStream>
#include "EditEmpMessBox.h"
#include "Tool.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget();
    void addEmpBox();

public slots:
    void flushTable();
    void flushListWidget();

private:
    QGroupBox * createEmpMess();
    QGroupBox * createMenu();

private:
    QTableWidget * TableWidget;
    QListWidget * ListWidget;
    QPushButton * AddEmpBtn;
    QPushButton * DelEmpBtn;
    QPushButton * SaveBtn;
    QPushButton * ExitBtn;
    QLineEdit * FindEmpEdit;
    EditEmpMessBox * messBox;
};
#endif // MAINWINDOW_H
