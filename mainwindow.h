#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QKeyEvent>
//#include <QSound>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QRegularExpression>
#include <random>
#include <QPixmap>
#include "sqlite/sqlitedb.h"
#include "lesson.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    SqliteDB *db;
    QVector<Lesson *> lessons;
    quint32 currentKana = 0;
    quint32 lastKana = 0;
    quint32 preKana = 0;
    QString project_dir;

    QRegularExpression rx;//("[^A-z]")

    QMediaPlayer *player = nullptr;
    QAudioOutput *audio = nullptr;

    void keyPressEvent(QKeyEvent *event);
    void checkKana();

    void setIconFail();
    void setIconCorrect();



public slots:
    void getLesson();
    void nextKana();
    void setIconNone();
    void validateInput(QString);
    void toggleKataHira();

private:
    Ui::MainWindow *ui;
    bool m_katakana;
    bool m_hiragana;

private slots:
    void onToggleTable();
};

#endif // MAINWINDOW_H
