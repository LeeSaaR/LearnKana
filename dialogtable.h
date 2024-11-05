#ifndef DIALOGTABLE_H
#define DIALOGTABLE_H

#include <QDialog>

namespace Ui {
class DialogTable;
}

class DialogTable : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTable(bool isHiragana, QWidget *parent = nullptr);
    ~DialogTable();

private:
    Ui::DialogTable *ui;
};

#endif // DIALOGTABLE_H
