#include "csv_class.h"

CSV_Class::CSV_Class()
{
}

CSV_Class::~CSV_Class()
{
}

QString CSV_Class::CreateCSV(QString PathName,QString CSV_Word)//创建一个新的CSV文件
{
	//****************一级目录******************
	//CSV文件的上级目录
	QString Csv_Dir = QApplication::applicationDirPath() + "/ProductData" ;
	//检查目录是否存在
	QDir dir;
	if (!dir.exists(Csv_Dir))
	{
		bool res = dir.mkdir(Csv_Dir);
	}
	//****************二级目录*******************
	Csv_Dir = Csv_Dir +"/" +QDateTime::currentDateTime().toString("yyyy-MM-dd");
	//检查目录是否存在
	if (!dir.exists(Csv_Dir))
	{
		bool res = dir.mkdir(Csv_Dir);
	}
	//判断CSV文件是否存在
	//CSV文件的目录
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
QList<QStringList> CSV_Class::ReadFromCSV(QString PathName)//读取CSV文件
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
void CSV_Class::SaveToCSV(QString CsvList, QString PathName) //写入数据到CSV文件
{
		QFile file(PathName);
		if (QProcess::startDetached(PathName))
		{
			QMessageBox::about(nullptr, QString::fromLocal8Bit("Error"), PathName + QString::fromLocal8Bit("已经被打开无法写入信息，请关闭！！！"));
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
