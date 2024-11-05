#ifndef SQLITEDB_H
#define SQLITEDB_H


#include <QtSql>
#include <QDebug>
#include <QRandomGenerator>

class SqliteDB
{
public:
    SqliteDB(QString _dbFilePath = "");
    QString DBFilePath;
    QSqlDatabase db;

    QMap<QString, QString> kanaTable;
    QVector<QString> kanaLessons;

    QVector<int> KanaIDs;
    void resetKana();
    QMap<int, QString> listHiragana;
    QMap<int, QString> listKatakana;
    QMap<int, QString> listAudio;
    QMap<int, QString> listResult;
    void getKana(QString _kanaTable, bool _hiragana, bool _katakana);

private:


};

#endif // SQLITEDB_H
