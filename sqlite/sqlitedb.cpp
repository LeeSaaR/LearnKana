#include "sqlitedb.h"

SqliteDB::SqliteDB(QString _dbFilePath) :
    DBFilePath(_dbFilePath)
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(this->DBFilePath);

    if (!this->db.open()) {
        qDebug() << "project not found";
    }
    else {
        qDebug() << "connect to database: " << this->DBFilePath;
    }
    this->kanaLessons.append("Kana_Vocals");
    this->kanaLessons.append("Kana_A");
    this->kanaLessons.append("Kana_I");
    this->kanaLessons.append("Kana_U");
    this->kanaLessons.append("Kana_E");
    this->kanaLessons.append("Kana_O");
    this->kanaLessons.append("Kana_K");
    this->kanaLessons.append("Kana_S");
    this->kanaLessons.append("Kana_T");
    this->kanaLessons.append("Kana_N");
    this->kanaLessons.append("Kana_H");
    this->kanaLessons.append("Kana_M");
    this->kanaLessons.append("Kana_Y");
    this->kanaLessons.append("Kana_R");
    this->kanaLessons.append("Kana_W");
    this->kanaLessons.append("Kana_G");
    this->kanaLessons.append("Kana_Z");
    this->kanaLessons.append("Kana_D");
    this->kanaLessons.append("Kana_B");
    this->kanaLessons.append("Kana_P");
    this->kanaLessons.append("Kana_Ya");
    this->kanaLessons.append("Kana_Yu");
    this->kanaLessons.append("Kana_Yo");
    this->kanaLessons.append("Kana");
}

void SqliteDB::resetKana()
{
    while (!this->KanaIDs.isEmpty()) {
        this->KanaIDs.removeLast();
    }
    if (!this->listHiragana.isEmpty()) this->listHiragana.clear();
    if (!this->listKatakana.isEmpty()) this->listKatakana.clear();
    if (!this->listResult.isEmpty()) this->listResult.clear();
    if (!this->listAudio.isEmpty()) this->listAudio.clear();

}



void SqliteDB::getKana(QString _kanaTable, bool _hiragana, bool _katakana)
{
    QSqlQuery *query(new QSqlQuery(this->db));

    if (_kanaTable == "Kana_Vocals") {
        query->prepare("SELECT ID FROM Kana_Vocals");
    }
    if (_kanaTable == "Kana_A") {
        query->prepare("SELECT ID FROM Kana_A");
    }
    if (_kanaTable == "Kana_I") {
        query->prepare("SELECT ID FROM Kana_I");
    }
    if (_kanaTable == "Kana_U") {
        query->prepare("SELECT ID FROM Kana_U");
    }
    if (_kanaTable == "Kana_E") {
        query->prepare("SELECT ID FROM Kana_E");
    }
    if (_kanaTable == "Kana_O") {
        query->prepare("SELECT ID FROM Kana_O");
    }
    if (_kanaTable == "Kana_K") {
        query->prepare("SELECT ID FROM Kana_K");
    }
    if (_kanaTable == "Kana_S") {
        query->prepare("SELECT ID FROM Kana_S");
    }
    if (_kanaTable == "Kana_T") {
        query->prepare("SELECT ID FROM Kana_T");
    }
    if (_kanaTable == "Kana_N") {
        query->prepare("SELECT ID FROM Kana_N");
    }
    if (_kanaTable == "Kana_H") {
        query->prepare("SELECT ID FROM Kana_H");
    }
    if (_kanaTable == "Kana_M") {
        query->prepare("SELECT ID FROM Kana_M");
    }
    if (_kanaTable == "Kana_Y") {
        query->prepare("SELECT ID FROM Kana_Y");
    }
    if (_kanaTable == "Kana_R") {
        query->prepare("SELECT ID FROM Kana_R");
    }
    if (_kanaTable == "Kana_W") {
        query->prepare("SELECT ID FROM Kana_W");
    }
    if (_kanaTable == "Kana_G") {
        query->prepare("SELECT ID FROM Kana_G");
    }
    if (_kanaTable == "Kana_Z") {
        query->prepare("SELECT ID FROM Kana_Z");
    }
    if (_kanaTable == "Kana_D") {
        query->prepare("SELECT ID FROM Kana_D");
    }
    if (_kanaTable == "Kana_B") {
        query->prepare("SELECT ID FROM Kana_B");
    }
    if (_kanaTable == "Kana_P") {
        query->prepare("SELECT ID FROM Kana_P");
    }
    if (_kanaTable == "Kana_Ya") {
        query->prepare("SELECT ID FROM Kana_Ya");
    }
    if (_kanaTable == "Kana_Yu") {
        query->prepare("SELECT ID FROM Kana_Yu");
    }
    if (_kanaTable == "Kana_Yo") {
        query->prepare("SELECT ID FROM Kana_Yo");
    }
    if (_kanaTable == "Kana") {
        query->prepare("SELECT ID FROM Kana");
    }

    query->exec();
    query->first();
    query->previous();
    this->resetKana();

    while (query->next()) {
        this->KanaIDs.append(query->value("ID").toInt());
    }
    query->finish();

    for (int _id : this->KanaIDs) {

        query->prepare("SELECT Romanji, Hiragana, Katakana, Audio FROM Kana "
                       "WHERE ID = :id");
        query->bindValue(":id", _id);
        query->exec();

        query->first();
        if ((_hiragana) && !(_katakana)) {
            this->listHiragana[_id] = query->value("Hiragana").toString();
            this->listResult[_id]   = query->value("Romanji").toString();
            /*
             * The sound is disabled in terms of copyright
             this->listAudio[_id]    = query->value("Audio").toString();
            */
        }
        if ((_katakana) && !(_hiragana)) {
            this->listKatakana[_id] = query->value("Katakana").toString();
            this->listResult[_id]   = query->value("Romanji").toString();
            /*
             * The sound is disabled in terms of copyright
             this->listAudio[_id]    = query->value("Audio").toString();
            */
        }
        if ((_katakana) && (_hiragana)) {
            this->listHiragana[_id] = query->value("Hiragana").toString();
            this->listKatakana[_id] = query->value("Katakana").toString();
            this->listResult[_id]   = query->value("Romanji").toString();
            /*
             * The sound is disabled in terms of copyright
             this->listAudio[_id]    = query->value("Audio").toString();
            */
        }
        query->finish();
    }

}
