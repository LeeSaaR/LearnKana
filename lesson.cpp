#include "lesson.h"
#include "ui_lesson.h"

Lesson::Lesson(QString _name, QString _table, QWidget *parent) :
    QWidget(parent),
    kanaTable(_table),
    ui(new Ui::Lesson)
{
    ui->setupUi(this);
    this->btn = ui->btn;
    ui->btn->setStyleSheet(
                "QPushButton{border: none; background-color: #404040; color: #d0d0d0;}"
                "QPushButton:checked{border: none; background-color: #aa00aa; color: #d0d0d0;}"
                "QPushButton:checked:hover{border: none; background-color: #aa00aa; color: #d0d0d0;}"
                "QPushButton:hover{border: none; background-color: #4f4f4f; color: #d0d0d0;}"

                );
    ui->btn->setText(_name);
}

Lesson::~Lesson()
{
    delete ui;
}

