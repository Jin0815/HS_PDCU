#include "mysqldata.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QTextCodec>
#include <string>
#include <ctime>
#include <time.h>
#pragma comment(lib,"libmysql.lib")
 //��ȡϵͳ��ǰʱ��
time_t currentTime = time(NULL); 
struct tm* t = localtime(&currentTime);
auto rotating_logger = rotating_logger_mt("plc_log", "LOGS/" + std::to_string(1900+t->tm_year)+"-"+ std::to_string(1+t->tm_mon)+"-"+ std::to_string(t->tm_mday) +"/PLC_log/log.txt", 1048576 * 5, 3);
MySQLData::MySQLData(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.BT_testsql,SIGNAL(clicked()),this,SLOT(BT_testsql_Clicked()));
}

MySQLData::~MySQLData()
{
}

void MySQLData::BT_testsql_Clicked()
{
	connectMYSQL(ui.lineEdit_connectname->text());
	connectDBTable(ui.lineEdit_connectname->text(), ui.lineEdit_sqlname->text());
	ShowDatabaseTable(ui.lineEdit_sqlname->text(), ui.lineEdit_tablename->text());
}
void MySQLData::connectMYSQL(QString connect_mysql)
{
	if (QSqlDatabase::contains(connect_mysql))//�ж�testConnect�����Ƿ���ڲ�����
	{
		database = QSqlDatabase::database(connect_mysql);
	}
	else //δ�������½����ݿ�����
	{
		database = QSqlDatabase::addDatabase("QMYSQL", "MySQL");
		//database = QSqlDatabase::database("testConnect");//�������ݿ����ӣ���Ϊ������testConnect
		database.setHostName("192.168.3.10");      //�������ݿ���������������Ҫע�⣨�����Ϊ��127.0.0.1�������ֲ������ӣ����Ϊlocalhost)
		database.setPort(3306);                 //�������ݿ�˿ںţ�������һ��
		database.setUserName("root");           //���ݿ��û�����������һ��
		database.setPassword("MYSQL");         //���ݿ����룬������һ��
	}
	bool ok = database.open();
	if (!database.open())
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("MySQL����ʧ�ܣ�"));
		rotating_logger->info("MySQL����ʧ�ܣ�");
		rotating_logger->flush();
		return;
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("MySQL���ӳɹ���"));
		rotating_logger->info("MySQL���ӳɹ���");
		rotating_logger->flush();
	}
}
void MySQLData::createDB(QString connect_mysql, QString databasename,QString tablename)
{
	QString querystring;
	//�������ݿ�
	database = QSqlDatabase::database(connect_mysql);
	QSqlQuery query(database);
	query.exec("CREATE DATABASE IF NOT EXISTS "+ databasename);
	if (database.lastError().isValid())
	{
		qDebug() << "Create database failed." << database.lastError();
		return;
	}
	//�������ݱ�student
	database.setDatabaseName(databasename);
	if (!database.open())
	{
		qDebug() << "database open failed";
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("createDB+���ݿ��ʧ�ܣ�"));
		return;
	}
	querystring =
		"CREATE TABLE IF NOT EXISTS "+ databasename+"."+ tablename+"\
            (\
                Name varchar(20),\
                NO varchar(20) primary key,\
                Sex varchar(20),\
                Tell varchar(20),\
                Address varchar(30), \
                Hobbies varchar(30)\
                )";
	bool ok =query.exec(querystring);
	if (ok)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), databasename + QString::fromLocal8Bit("���ݿ��Լ������ɹ���"));
		return;
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), databasename + QString::fromLocal8Bit("���ݿ��Լ�����ʧ�ܣ�"));
		return;
	}

}
void MySQLData::connectDBTable(QString connect_mysql,QString databasename)
{
	database = QSqlDatabase::database(connect_mysql);
    database.setDatabaseName(databasename);
	//�����ݿ�
	bool ok = database.open();
	if (!database.open())
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), databasename + QString::fromLocal8Bit("���ݿ�����ʧ�ܣ�"));
		return;
	}
	else
	{
		//qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), databasename + QString::fromLocal8Bit("���ݿ����ӳɹ���"));
	}
}
void MySQLData::closeDBTable(QString  connect_mysql, QString databasename)
{
	//�ر����ݿ�
	database.close();
}
void MySQLData::AddtoDB(QString TableName)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///����utf-8����
	QString add = "insert into "+ TableName +" values('lisi44', '201808464', 'woman')";
	bool ok =query.exec(add);
	if (ok)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName+QString::fromLocal8Bit("���ݿ�������ݳɹ���"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName + QString::fromLocal8Bit("���ݿ��������ʧ�ܣ�"));
	}
}
void MySQLData::DeletefromDB(QString TableName)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///����utf-8����
	QString del= "delete from " + TableName + " where Name='lisi1'";
	bool ok = query.exec(del);
	if (ok)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName + QString::fromLocal8Bit("���ݿ�ɾ�����ݳɹ���"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName + QString::fromLocal8Bit("���ݿ�ɾ������ʧ�ܣ�"));
	}
}
QString MySQLData::QueryfromDB(QString TableName,QString BeQueryWord,QString ConditionWord, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///����utf-8����
	QString del = "select "+ BeQueryWord +" from "+ TableName + " where " + ConditionWord + "='" + ConditionWordValue + "'";
	bool ok = query.exec(del);
	QString result;
	while (query.next())
	{
		result = result+query.value(0).toString()+",";
	}
	qDebug() << result;
	if (ok)
	{
		return result;
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName + QString::fromLocal8Bit("���ݿ��ѯ���ݳɹ���"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName + QString::fromLocal8Bit("���ݿ��ѯ����ʧ�ܣ�"));
		return 0;
	}
}
void MySQLData::UpdateDB(QString TableName, QString BeUpdateWord, QString ConditionWord, QString BeUpdateWordValue, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///����utf-8����
	QString del = "update " + TableName + "set " + BeUpdateWord + "='" + BeUpdateWordValue + "'" + " where " + ConditionWord + "='" + ConditionWordValue + "'";
	bool ok = query.exec(del);
	if (ok)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName + QString::fromLocal8Bit("���ݿ�������ݳɹ���"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), TableName + QString::fromLocal8Bit("���ݿ��������ʧ�ܣ�"));
	}
}
void MySQLData::ShowDatabaseTable(QString databasename, QString tablename)
{
	static QSqlQueryModel *model = new QSqlQueryModel(ui.tableView);
	model->setQuery("SELECT * FROM "+tablename,database);
	/*model->setHeaderData(0,Qt::Horizontal,tr("Name"));
	model->setHeaderData(0, Qt::Horizontal, tr("NO"));
	model->setHeaderData(0, Qt::Horizontal, tr("Sex"));
	model->setHeaderData(0, Qt::Horizontal, tr("Tell"));
	model->setHeaderData(0, Qt::Horizontal, tr("Address"));
	model->setHeaderData(0, Qt::Horizontal, tr("Hobbies"));*/
	ui.tableView->setModel(model);
	ui.tableView->show();
}
