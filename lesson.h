#ifndef LESSON_H
#define LESSON_H

#include <QWidget>
#include <QDebug>
#include <QPushButton>

namespace Ui {
class Lesson;
}

class Lesson : public QWidget
{
    Q_OBJECT

public:
    explicit Lesson(QString _name, QString _table, QWidget *parent = nullptr);
    ~Lesson();

    QString kanaTable;
    QString KanaTable(){return this->kanaTable;}
    QPushButton *btn;

private:
    Ui::Lesson *ui;
};

#endif // LESSON_H
