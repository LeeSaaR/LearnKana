#include "dialogtable.h"
#include "ui_dialogtable.h"

#include <QPixmap>

DialogTable::DialogTable(bool isHiragana, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTable)
{
    ui->setupUi(this);
    if (isHiragana){
        setWindowTitle("LearnKana - Hiragana Table");
        QPixmap pxm = QPixmap(":/table/Hiragana.png");
        ui->label->setPixmap(pxm.scaledToWidth(1200));
    }
    else {
        setWindowTitle("LearnKana - Katakana Table");
        QPixmap pxm = QPixmap(":/table/Katakana.png");
        ui->label->setPixmap(pxm.scaledToWidth(1200));
    }
}

DialogTable::~DialogTable()
{
    delete ui;
}
