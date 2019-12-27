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
 //获取系统当前时间
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
	if (QSqlDatabase::contains(connect_mysql))//判断testConnect连接是否存在并连接
	{
		database = QSqlDatabase::database(connect_mysql);
	}
	else //未连接则新建数据库连接
	{
		database = QSqlDatabase::addDatabase("QMYSQL", "MySQL");
		//database = QSqlDatabase::database("testConnect");//创建数据库连接，并为其命名testConnect
		database.setHostName("192.168.3.10");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
		database.setPort(3306);                 //连接数据库端口号，与设置一致
		database.setUserName("root");           //数据库用户名，与设置一致
		database.setPassword("MYSQL");         //数据库密码，与设置一致
	}
	bool ok = database.open();
	if (!database.open())
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("MySQL连接失败！"));
		rotating_logger->info("MySQL连接失败！");
		rotating_logger->flush();
		return;
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("MySQL连接成功！"));
		rotating_logger->info("MySQL连接成功！");
		rotating_logger->flush();
	}
}
void MySQLData::createDB(QString connect_mysql, QString databasename,QString tablename)
{
	QString querystring;
	//创建数据库
	database = QSqlDatabase::database(connect_mysql);
	QSqlQuery query(database);
	query.exec("CREATE DATABASE IF NOT EXISTS "+ databasename);
	if (database.lastError().isValid())
	{
		qDebug() << "Create database failed." << database.lastError();
		return;
	}
	//创建数据表student
	database.setDatabaseName(databasename);
	if (!database.open())
	{
		qDebug() << "database open failed";
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("createDB+数据库打开失败！"));
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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), databasename + QString::fromLocal8Bit("数据库以及表创建成功！"));
		return;
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), databasename + QString::fromLocal8Bit("数据库以及表创建失败！"));
		return;
	}

}
void MySQLData::connectDBTable(QString connect_mysql,QString databasename)
{
	database = QSqlDatabase::database(connect_mysql);
    database.setDatabaseName(databasename);
	//打开数据库
	bool ok = database.open();
	if (!database.open())
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), databasename + QString::fromLocal8Bit("数据库连接失败！"));
		return;
	}
	else
	{
		//qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), databasename + QString::fromLocal8Bit("数据库连接成功！"));
	}
}
void MySQLData::closeDBTable(QString  connect_mysql, QString databasename)
{
	//关闭数据库
	database.close();
}
void MySQLData::AddtoDB(QString TableName)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///设置utf-8编码
	QString add = "insert into "+ TableName +" values('lisi44', '201808464', 'woman')";
	bool ok =query.exec(add);
	if (ok)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName+QString::fromLocal8Bit("数据库添加数据成功！"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName + QString::fromLocal8Bit("数据库添加数据失败！"));
	}
}
void MySQLData::DeletefromDB(QString TableName)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///设置utf-8编码
	QString del= "delete from " + TableName + " where Name='lisi1'";
	bool ok = query.exec(del);
	if (ok)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName + QString::fromLocal8Bit("数据库删除数据成功！"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName + QString::fromLocal8Bit("数据库删除数据失败！"));
	}
}
QString MySQLData::QueryfromDB(QString TableName,QString BeQueryWord,QString ConditionWord, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///设置utf-8编码
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
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName + QString::fromLocal8Bit("数据库查询数据成功！"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName + QString::fromLocal8Bit("数据库查询数据失败！"));
		return 0;
	}
}
void MySQLData::UpdateDB(QString TableName, QString BeUpdateWord, QString ConditionWord, QString BeUpdateWordValue, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///设置utf-8编码
	QString del = "update " + TableName + "set " + BeUpdateWord + "='" + BeUpdateWordValue + "'" + " where " + ConditionWord + "='" + ConditionWordValue + "'";
	bool ok = query.exec(del);
	if (ok)
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName + QString::fromLocal8Bit("数据库更新数据成功！"));
	}
	else
	{
		qDebug() << "fail to connect mysql:" << database.lastError().text();
		QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), TableName + QString::fromLocal8Bit("数据库更新数据失败！"));
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
