#ifndef CSV_CLASS_H
#define CSV_CLASS_H

#include <QDate>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QApplication>
#include <QString>
#include <QMessageBox>
#include <QProcess>


class CSV_Class
{
public:
	CSV_Class();
	~CSV_Class();
	QString CreateCSV(QString PathName, QString CSV_Word);
	QList<QStringList> ReadFromCSV(QString PathName);//��ȡCSV�ļ�
	void SaveToCSV(QString CsvList, QString PathName); //д�����ݵ�CSV�ļ�
};
#endif
