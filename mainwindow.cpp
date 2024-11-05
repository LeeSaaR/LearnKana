#include "mainwindow.h"
#include "dialogtable.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set path and file
    QDir dir_pwd;
    dir_pwd.cdUp();
    project_dir = dir_pwd.absolutePath()+ "/LearnKana";

    /*
     * The sound is disabled in terms of copyright

    player = new QMediaPlayer;
    audio = new QAudioOutput;
    player->setAudioOutput(audio);
    audio->setVolume(100);
    */

    /*
     * you may need set the right path to the database
    */

    const QString database_file = "/LearnKana/database/Japanisch.db";

    this->db = new SqliteDB( dir_pwd.absolutePath() + database_file );
    rx.setPattern("[^A-z]");
    for (QString &_kanaTable : this->db->kanaLessons) {
        this->lessons.append(new Lesson( QString(_kanaTable).replace("_", " "), _kanaTable, this));
        connect(this->lessons.last()->btn, SIGNAL(clicked()), this, SLOT(getLesson()));
        ui->listLessons->layout()->removeItem(ui->spacer_Lessons);
        ui->listLessons->layout()->addWidget(this->lessons.last());
        ui->listLessons->layout()->addItem(ui->spacer_Lessons);
    }
    connect(ui->btn_next, SIGNAL(clicked()), this, SLOT(nextKana()));
    connect(ui->lineEdit_Result, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(setIconNone()));
    connect(ui->lineEdit_Result, SIGNAL(textChanged(QString)), this, SLOT(validateInput(QString)));
    connect(ui->btn_toggle_kata_hira, &QPushButton::clicked, this, &MainWindow::toggleKataHira);

    m_hiragana = false;
    m_katakana = true;
    this->db->getKana("Kana_Vocals", m_hiragana, m_katakana);
    this->currentKana = QRandomGenerator::global()->bounded(0, this->db->KanaIDs.size());
    if ((m_hiragana) && !(m_katakana))
        ui->label_Kana->setText(this->db->listHiragana[this->db->KanaIDs[this->currentKana]]);
    else if ((m_katakana) && !(m_hiragana))
        ui->label_Kana->setText(this->db->listKatakana[this->db->KanaIDs[this->currentKana]]);


    connect(ui->btn_toggle_table, &QPushButton::clicked, this, &MainWindow::onToggleTable);
}

MainWindow::~MainWindow()
{
    if (audio != nullptr) delete player;
    if (player != nullptr) delete player;
    delete ui;
}

void MainWindow::getLesson()
{
    for (Lesson * lesson : lessons)
        lesson->btn->setChecked(false);

    Lesson *_clickedLesson = qobject_cast<Lesson *>(sender()->parent());
    _clickedLesson->btn->setChecked(true);
    ui->lineEdit_Result->setFocus();
    this->db->getKana(_clickedLesson->KanaTable(), m_hiragana, m_katakana);
    this->currentKana = QRandomGenerator::global()->bounded(0, this->db->KanaIDs.size());

    if ((m_hiragana) && !(m_katakana))
        ui->label_Kana->setText(this->db->listHiragana[this->db->KanaIDs[this->currentKana]]);
    else if ((m_katakana) && !(m_hiragana))
        ui->label_Kana->setText(this->db->listKatakana[this->db->KanaIDs[this->currentKana]]);
}

void MainWindow::nextKana()
{
    this->lastKana    = this->currentKana;
    this->currentKana = QRandomGenerator::global()->bounded(0, this->db->KanaIDs.size());
    while (this->currentKana == this->lastKana) {
        this->currentKana = QRandomGenerator::global()->bounded(0, this->db->KanaIDs.size());
    }

    if ((m_hiragana) && !(m_katakana))
        ui->label_Kana->setText(this->db->listHiragana[this->db->KanaIDs[this->currentKana]]);
    else if ((m_katakana) && !(m_hiragana))
        ui->label_Kana->setText(this->db->listKatakana[this->db->KanaIDs[this->currentKana]]);
}

void MainWindow::checkKana()
{
    if (ui->lineEdit_Result->text() == this->db->listResult[this->db->KanaIDs[this->currentKana]]) {
        this->nextKana();
        ui->lineEdit_Result->setText("");
        this->setIconCorrect();

        /*
         * The sound is disabled in turns of copyright
        player->setSource(QUrl::fromLocalFile(project_dir+"/data/audio/"+this->db->listAudio[this->db->KanaIDs[this->currentKana]]));
        player->play();
        player->setPosition(0);
        */

    }
    else {
        ui->lineEdit_Result->selectAll();
        this->setIconFail();
    }

}

void MainWindow::setIconFail()
{
    ui->label_Result->show();
    ui->label_Result->setPixmap(QPixmap(":/data/icons/fail.svg"));

}

void MainWindow::setIconCorrect()
{
    ui->label_Result->show();
    ui->label_Result->setPixmap(QPixmap(":/data/icons/correct.svg"));
}

void MainWindow::setIconNone()
{
    ui->label_Result->hide();
}

void MainWindow::validateInput(QString _text)
{
    if (ui->lineEdit_Result->text().contains(rx)) {
        ui->lineEdit_Result->setText(_text.remove(rx));
    }
    ui->lineEdit_Result->setText(ui->lineEdit_Result->text().toLower());
}

void MainWindow::toggleKataHira()
{
    if (ui->btn_toggle_kata_hira->isChecked())
    {
        ui->btn_toggle_kata_hira->setText("Hiragana");
        m_katakana = false;
        m_hiragana = true;
    }
    else
    {
        ui->btn_toggle_kata_hira->setText("Katakana");
        m_katakana = true;
        m_hiragana = false;
    }

    ui->lineEdit_Result->setFocus();
    this->db->getKana("Kana_Vocals", m_hiragana, m_katakana);
    this->currentKana = QRandomGenerator::global()->bounded(0, this->db->KanaIDs.size());

    if ((m_hiragana) && !(m_katakana))
        ui->label_Kana->setText(this->db->listHiragana[this->db->KanaIDs[this->currentKana]]);
    else if ((m_katakana) && !(m_hiragana))
        ui->label_Kana->setText(this->db->listKatakana[this->db->KanaIDs[this->currentKana]]);
}

void MainWindow::onToggleTable()
{
    bool isHiragana = ui->btn_toggle_kata_hira->isChecked();
    DialogTable *dialog = new DialogTable(isHiragana, this);
    dialog->exec();
    delete dialog;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
        this->checkKana();
    }
    if (event->key() == Qt::Key_Down) {

        this->nextKana();
        this->setIconNone();
    }
}
