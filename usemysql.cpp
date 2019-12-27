#include "usemysql.h"

//获取系统当前时间
time_t currentTime_usemysql = time(NULL);
struct tm* t_usemysql = localtime(&currentTime_usemysql);
auto rotating_logger_usemysql = rotating_logger_mt("usemysql_log", "LOGS/" + std::to_string(1900 + t_usemysql->tm_year) + "-" + std::to_string(1 + t_usemysql->tm_mon) + "-" + std::to_string(t_usemysql->tm_mday) + "/UseMySQL_log/log.txt", 1048576 * 5, 3);
UseMySQL::UseMySQL(QObject *parent)
	: QObject(parent)
{
}

UseMySQL::~UseMySQL()
{
}

int UseMySQL::connectMYSQL(QString connect_mysql)
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
		rotating_logger_usemysql->info("MySQL连接失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
	else
	{
		rotating_logger_usemysql->info("MySQL连接成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
}
int UseMySQL::createDB(QString connect_mysql, QString databasename, QString tablename, QString Class, QString V_Lower, QString V_Upper)
{
	QString querystring;
	//创建数据库
	database = QSqlDatabase::database(connect_mysql);
	QSqlQuery query(database);
	query.exec("CREATE DATABASE IF NOT EXISTS " + databasename);
	if (database.lastError().isValid())
	{
		rotating_logger_usemysql->info("创建数据库失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
	//创建数据表student
	database.setDatabaseName(databasename);
	if (!database.open())
	{
		rotating_logger_usemysql->info("数据库打开失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
	querystring =
		"CREATE TABLE IF NOT EXISTS " + databasename + "." + tablename + "\
            (\
                Class INT primary key,\
                V_Lower DOUBLE,\
                V_Upper DOUBLE\
                )";
	bool ok = query.exec(querystring);
	if (ok)
	{
		rotating_logger_usemysql->info("数据库以及表创建成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("数据库以及表创建失败！");
		rotating_logger_usemysql->flush();
		return  0;
	}

}
int UseMySQL::connectDBTable(QString connect_mysql, QString databasename)
{
	database = QSqlDatabase::database(connect_mysql);
	database.setDatabaseName(databasename);
	//打开数据库
	bool ok = database.open();
	if (!database.open())
	{
		rotating_logger_usemysql->info("数据库连接失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
	else
	{
		rotating_logger_usemysql->info("数据库连接成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
}
int UseMySQL::closeDBTable(QString  connect_mysql, QString databasename)
{
	//关闭数据库
	database.close();
	return 1;
}
int UseMySQL::AddtoDB(QString TableName, QString Class, QString V_Lower, QString V_Upper)
{
	QSqlQuery query(database);
	QString add = "insert into " + TableName + " values('"+ Class +"','"+ V_Lower +"','"+ V_Upper +"')";
	bool ok = query.exec(add);
	if (ok)
	{
		rotating_logger_usemysql->info("数据库添加数据成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("数据库添加数据失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
int UseMySQL::DeletefromDB(QString TableName,QString WordbyDelete, QString WordbyDeleteValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///设置utf-8编码
	QString del = "delete from " + TableName + " where "+ WordbyDelete +"='"+ WordbyDeleteValue +"'";
	bool ok = query.exec(del);
	if (ok)
	{
		rotating_logger_usemysql->info("数据库删除数据成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("数据库删除数据失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
QString UseMySQL::QueryfromDB(QString TableName, QString BeQueryWord, QString ConditionWord, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///设置utf-8编码
	QString del = "select "+ BeQueryWord +" from " + TableName + " where " + ConditionWord + "='" + ConditionWordValue + "'";
	bool ok = query.exec(del);
	QString result;
	while (query.next())
	{
		result = result + query.value(0).toString() + ",";
	}
	if (ok)
	{
		rotating_logger_usemysql->info("数据库查询数据成功！");
		rotating_logger_usemysql->flush();
		return result.left(result.size()-1);
	}
	else
	{
		rotating_logger_usemysql->info("数据库查询数据失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
int UseMySQL::UpdateDB(QString TableName, QString BeUpdateWord, QString ConditionWord, QString BeUpdateWordValue, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///设置utf-8编码
	QString del = "update " + TableName + "set " + BeUpdateWord + "='" + BeUpdateWordValue + "'" + " where " + ConditionWord + "='" + ConditionWordValue + "'";
	bool ok = query.exec(del);
	if (ok)
	{
		rotating_logger_usemysql->info("数据库更新数据成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("数据库更新数据失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
int UseMySQL::ShowDatabaseTable(QString databasename, QString tablename)
{
	static QSqlQueryModel *model = new QSqlQueryModel();
	model->setQuery("SELECT * FROM " + tablename, database);
	/*model->setHeaderData(0,Qt::Horizontal,tr("Name"));
	model->setHeaderData(0, Qt::Horizontal, tr("NO"));
	model->setHeaderData(0, Qt::Horizontal, tr("Sex"));
	model->setHeaderData(0, Qt::Horizontal, tr("Tell"));
	model->setHeaderData(0, Qt::Horizontal, tr("Address"));
	model->setHeaderData(0, Qt::Horizontal, tr("Hobbies"));*/
	return 1;

}
QSqlDatabase UseMySQL::getDatabase()
{
	return database;
}

//电池筛选数据库
int UseMySQL::AddtoDB_BatterySelect(QString TableName, QString SN, QString VoltageValue, QString VoltageGrade)
{
	QSqlQuery query(database);
	QString add = "insert into " + TableName + " values('" + SN + "','" + VoltageValue + "','" + VoltageGrade + "')";
	bool ok = query.exec(add);
	if (ok)
	{
		rotating_logger_usemysql->info("数据库添加数据成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("数据库添加数据失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
//存进56节电池数据库
int UseMySQL::AddtoDB_CaseandBattery(QString TableName, QString CaseSN, QString SN1, QString SN2, QString SN3, QString SN4, QString SN5, QString SN6, QString SN7, QString SN8, QString SN9, QString SN10, QString SN11, QString SN12, QString SN13, QString SN14, QString SN15, QString SN16, QString SN17, QString SN18, QString SN19, QString SN20, QString SN21, QString SN22, QString SN23, QString SN24, QString SN25, QString SN26, QString SN27, QString SN28, QString SN29, QString SN30,QString SN31, QString SN32, QString SN33, QString SN34, QString SN35, QString SN36, QString SN37, QString SN38, QString SN39, QString SN40,QString SN41, QString SN42, QString SN43, QString SN44, QString SN45, QString SN46, QString SN47, QString SN48, QString SN49, QString SN50,QString SN51, QString SN52, QString SN53, QString SN54, QString SN55, QString SN56)
{
	QSqlQuery query(database);
	QString add = "insert into " + TableName + " values('" + CaseSN + "','" + SN1 + "','" + SN2 + "','" + SN3 + "','" + SN4 + "','" + SN5 + "','" + SN6 + "','" + SN7 + "','" + SN8 + "','" + SN9 + "','" + SN10 + "','" + SN11 + "','" + SN12 + "','" + SN13 + "','" + SN14 + "','" + SN15 + "','" + SN16 + "','" + SN17 + "','" + SN18 + "','" + SN19 + "','" + SN20 + "','" + SN21 + "','" + SN22 + "','" + SN23 + "','" + SN24 + "','" + SN25 + "','" + SN26 + "','" + SN27 + "','" + SN28 + "','" + SN29 + "','" + SN30 + "','" + SN31 + "','" + SN32 + "','" + SN33 + "','" + SN34 + "','" + SN35 + "','" + SN36 + "','" + SN37 + "','" + SN38 + "','" + SN39 + "','" + SN40 + "','" + SN41 + "','" + SN42 + "','" + SN43 + "','" + SN44 + "','" + SN45 + "','" + SN46 + "','" + SN47 + "','" + SN48 + "','" + SN49 + "','" + SN50 + "','" + SN51 + "','" + SN52 + "','" + SN53 + "','" + SN54 + "','" + SN55 + "','" + SN56 + "')";
	bool ok = query.exec(add);
	if (ok)
	{
		rotating_logger_usemysql->info("存进56节电池数据库添加数据成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("数据库添加数据失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
}



//平衡测试电压测试的标准范围
int UseMySQL::createDB_VoltageMeasure(QString connect_mysql, QString databasename, QString tablename, QString StandardClass, QString V_Lower, QString V_Upper)
{
	QString querystring;
	//创建数据库
	database = QSqlDatabase::database(connect_mysql);
	QSqlQuery query(database);
	query.exec("CREATE DATABASE IF NOT EXISTS " + databasename);
	if (database.lastError().isValid())
	{
		rotating_logger_usemysql->info("创建数据库失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
	//创建数据表student
	database.setDatabaseName(databasename);
	if (!database.open())
	{
		rotating_logger_usemysql->info("数据库打开失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
	querystring =
		"CREATE TABLE IF NOT EXISTS " + databasename + "." + tablename + "\
            (\
                StandardClass VARCHAR(50) primary key,\
                V_Lower VARCHAR(50),\
                V_Upper VARCHAR(50)\
                )";
	bool ok = query.exec(querystring);
	if (ok)
	{
		rotating_logger_usemysql->info("数据库以及表创建成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("数据库以及表创建失败！");
		rotating_logger_usemysql->flush();
		return  0;
	}

}
int UseMySQL::AddtoDB_SettingVoltageStanard(QString TableName, QString StandardClass, QString V_Lower, QString V_Upper)
{
	QSqlQuery query(database);
	QString add = "insert into " + TableName + " values('" + StandardClass + "','" + V_Lower + "','" + V_Upper + "')";
	bool ok = query.exec(add);
	if (ok)
	{
		rotating_logger_usemysql->info("平衡测试电压标准数据库添加数据成功！");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("平衡测试电压标准数据库添加数据失败！");
		rotating_logger_usemysql->flush();
		return 0;
	}
}