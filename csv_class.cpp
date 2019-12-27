#include "csv_class.h"

CSV_Class::CSV_Class()
{
}

CSV_Class::~CSV_Class()
{
}

QString CSV_Class::CreateCSV(QString PathName,QString CSV_Word)//����һ���µ�CSV�ļ�
{
	//****************һ��Ŀ¼******************
	//CSV�ļ����ϼ�Ŀ¼
	QString Csv_Dir = QApplication::applicationDirPath() + "/ProductData" ;
	//���Ŀ¼�Ƿ����
	QDir dir;
	if (!dir.exists(Csv_Dir))
	{
		bool res = dir.mkdir(Csv_Dir);
	}
	//****************����Ŀ¼*******************
	Csv_Dir = Csv_Dir +"/" +QDateTime::currentDateTime().toString("yyyy-MM-dd");
	//���Ŀ¼�Ƿ����
	if (!dir.exists(Csv_Dir))
	{
		bool res = dir.mkdir(Csv_Dir);
	}
	//�ж�CSV�ļ��Ƿ����
	//CSV�ļ���Ŀ¼
	QString CSVPathName = Csv_Dir + "/" + PathName;
	QFile file(CSVPathName);
	if (!file.exists())
	{
		file.open(QIODevice::WriteOnly | QIODevice::Append);
		QTextStream in(&file);
		in << CSV_Word;
		file.flush();
		file.close();
	}
	return CSVPathName;
}
QList<QStringList> CSV_Class::ReadFromCSV(QString PathName)//��ȡCSV�ļ�
{
	QList<QStringList> retList;
	QFile file(PathName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return retList;
	while (!file.atEnd())
	{
		QString line = file.readLine();
		line.replace('\n', "");
		QStringList linelist = line.split(',');
		retList.append(linelist);
	}
	file.close();
	return retList;
}
void CSV_Class::SaveToCSV(QString CsvList, QString PathName) //д�����ݵ�CSV�ļ�
{
		QFile file(PathName);
		if (QProcess::startDetached(PathName))
		{
			QMessageBox::about(nullptr, QString::fromLocal8Bit("Error"), PathName + QString::fromLocal8Bit("�Ѿ������޷�д����Ϣ����رգ�����"));
		}
		else
		{
			if (!(file.open(QIODevice::WriteOnly | QIODevice::Append)))
			{
				QMessageBox::warning(NULL, "warning", QString("Can't Open this Document:%1 (Reason:%2)").arg(PathName).arg(file.errorString()));
				return;
			}
			else
			{
				QTextStream in(&file);
				in << "\n" << CsvList;
				file.flush();
				file.close();
			}
		}
}
