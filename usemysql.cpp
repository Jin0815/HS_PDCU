#include "usemysql.h"

//��ȡϵͳ��ǰʱ��
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
		rotating_logger_usemysql->info("MySQL����ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
	else
	{
		rotating_logger_usemysql->info("MySQL���ӳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
}
int UseMySQL::createDB(QString connect_mysql, QString databasename, QString tablename, QString Class, QString V_Lower, QString V_Upper)
{
	QString querystring;
	//�������ݿ�
	database = QSqlDatabase::database(connect_mysql);
	QSqlQuery query(database);
	query.exec("CREATE DATABASE IF NOT EXISTS " + databasename);
	if (database.lastError().isValid())
	{
		rotating_logger_usemysql->info("�������ݿ�ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
	//�������ݱ�student
	database.setDatabaseName(databasename);
	if (!database.open())
	{
		rotating_logger_usemysql->info("���ݿ��ʧ�ܣ�");
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
		rotating_logger_usemysql->info("���ݿ��Լ������ɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ��Լ�����ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return  0;
	}

}
int UseMySQL::connectDBTable(QString connect_mysql, QString databasename)
{
	database = QSqlDatabase::database(connect_mysql);
	database.setDatabaseName(databasename);
	//�����ݿ�
	bool ok = database.open();
	if (!database.open())
	{
		rotating_logger_usemysql->info("���ݿ�����ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ����ӳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
}
int UseMySQL::closeDBTable(QString  connect_mysql, QString databasename)
{
	//�ر����ݿ�
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
		rotating_logger_usemysql->info("���ݿ�������ݳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ��������ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
int UseMySQL::DeletefromDB(QString TableName,QString WordbyDelete, QString WordbyDeleteValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///����utf-8����
	QString del = "delete from " + TableName + " where "+ WordbyDelete +"='"+ WordbyDeleteValue +"'";
	bool ok = query.exec(del);
	if (ok)
	{
		rotating_logger_usemysql->info("���ݿ�ɾ�����ݳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ�ɾ������ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
QString UseMySQL::QueryfromDB(QString TableName, QString BeQueryWord, QString ConditionWord, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///����utf-8����
	QString del = "select "+ BeQueryWord +" from " + TableName + " where " + ConditionWord + "='" + ConditionWordValue + "'";
	bool ok = query.exec(del);
	QString result;
	while (query.next())
	{
		result = result + query.value(0).toString() + ",";
	}
	if (ok)
	{
		rotating_logger_usemysql->info("���ݿ��ѯ���ݳɹ���");
		rotating_logger_usemysql->flush();
		return result.left(result.size()-1);
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ��ѯ����ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
int UseMySQL::UpdateDB(QString TableName, QString BeUpdateWord, QString ConditionWord, QString BeUpdateWordValue, QString ConditionWordValue)
{
	QSqlQuery query(database);
	//database.exec("SET NAMES 'UTF-8'"); ///����utf-8����
	QString del = "update " + TableName + "set " + BeUpdateWord + "='" + BeUpdateWordValue + "'" + " where " + ConditionWord + "='" + ConditionWordValue + "'";
	bool ok = query.exec(del);
	if (ok)
	{
		rotating_logger_usemysql->info("���ݿ�������ݳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ��������ʧ�ܣ�");
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

//���ɸѡ���ݿ�
int UseMySQL::AddtoDB_BatterySelect(QString TableName, QString SN, QString VoltageValue, QString VoltageGrade)
{
	QSqlQuery query(database);
	QString add = "insert into " + TableName + " values('" + SN + "','" + VoltageValue + "','" + VoltageGrade + "')";
	bool ok = query.exec(add);
	if (ok)
	{
		rotating_logger_usemysql->info("���ݿ�������ݳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ��������ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
}
//���56�ڵ�����ݿ�
int UseMySQL::AddtoDB_CaseandBattery(QString TableName, QString CaseSN, QString SN1, QString SN2, QString SN3, QString SN4, QString SN5, QString SN6, QString SN7, QString SN8, QString SN9, QString SN10, QString SN11, QString SN12, QString SN13, QString SN14, QString SN15, QString SN16, QString SN17, QString SN18, QString SN19, QString SN20, QString SN21, QString SN22, QString SN23, QString SN24, QString SN25, QString SN26, QString SN27, QString SN28, QString SN29, QString SN30,QString SN31, QString SN32, QString SN33, QString SN34, QString SN35, QString SN36, QString SN37, QString SN38, QString SN39, QString SN40,QString SN41, QString SN42, QString SN43, QString SN44, QString SN45, QString SN46, QString SN47, QString SN48, QString SN49, QString SN50,QString SN51, QString SN52, QString SN53, QString SN54, QString SN55, QString SN56)
{
	QSqlQuery query(database);
	QString add = "insert into " + TableName + " values('" + CaseSN + "','" + SN1 + "','" + SN2 + "','" + SN3 + "','" + SN4 + "','" + SN5 + "','" + SN6 + "','" + SN7 + "','" + SN8 + "','" + SN9 + "','" + SN10 + "','" + SN11 + "','" + SN12 + "','" + SN13 + "','" + SN14 + "','" + SN15 + "','" + SN16 + "','" + SN17 + "','" + SN18 + "','" + SN19 + "','" + SN20 + "','" + SN21 + "','" + SN22 + "','" + SN23 + "','" + SN24 + "','" + SN25 + "','" + SN26 + "','" + SN27 + "','" + SN28 + "','" + SN29 + "','" + SN30 + "','" + SN31 + "','" + SN32 + "','" + SN33 + "','" + SN34 + "','" + SN35 + "','" + SN36 + "','" + SN37 + "','" + SN38 + "','" + SN39 + "','" + SN40 + "','" + SN41 + "','" + SN42 + "','" + SN43 + "','" + SN44 + "','" + SN45 + "','" + SN46 + "','" + SN47 + "','" + SN48 + "','" + SN49 + "','" + SN50 + "','" + SN51 + "','" + SN52 + "','" + SN53 + "','" + SN54 + "','" + SN55 + "','" + SN56 + "')";
	bool ok = query.exec(add);
	if (ok)
	{
		rotating_logger_usemysql->info("���56�ڵ�����ݿ�������ݳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ��������ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
}



//ƽ����Ե�ѹ���Եı�׼��Χ
int UseMySQL::createDB_VoltageMeasure(QString connect_mysql, QString databasename, QString tablename, QString StandardClass, QString V_Lower, QString V_Upper)
{
	QString querystring;
	//�������ݿ�
	database = QSqlDatabase::database(connect_mysql);
	QSqlQuery query(database);
	query.exec("CREATE DATABASE IF NOT EXISTS " + databasename);
	if (database.lastError().isValid())
	{
		rotating_logger_usemysql->info("�������ݿ�ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
	//�������ݱ�student
	database.setDatabaseName(databasename);
	if (!database.open())
	{
		rotating_logger_usemysql->info("���ݿ��ʧ�ܣ�");
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
		rotating_logger_usemysql->info("���ݿ��Լ������ɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("���ݿ��Լ�����ʧ�ܣ�");
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
		rotating_logger_usemysql->info("ƽ����Ե�ѹ��׼���ݿ�������ݳɹ���");
		rotating_logger_usemysql->flush();
		return 1;
	}
	else
	{
		rotating_logger_usemysql->info("ƽ����Ե�ѹ��׼���ݿ��������ʧ�ܣ�");
		rotating_logger_usemysql->flush();
		return 0;
	}
}