#ifndef USEMYSQL_H
#define USEMYSQL_H

#include <QObject>
#include <Windows.h>
#include <mysql.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <QSqlDatabase>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
using namespace spdlog;
class UseMySQL : public QObject
{
	Q_OBJECT

public:
	UseMySQL(QObject *parent= Q_NULLPTR);
	~UseMySQL();
	int connectMYSQL(QString connect_mysql);//����һ��MySQL����
	int connectDBTable(QString  connect_mysql, QString databasename);//����ĳһ�����ݿ��ĳһ����
	int createDB(QString connect_mysql, QString databasename, QString tablename, QString Class, QString V_Lower, QString V_Upper);//����һ�����ݿ��Լ�ĳһ����
	int closeDBTable(QString  connect_mysql, QString databasename);//�ر�ĳһ�����ݿ��ĳһ����
	int ShowDatabaseTable(QString databasename, QString tablename);//�����������ʾ����
	int AddtoDB(QString TableName, QString Class, QString V_Lower, QString V_Upper);//����ĳһ�м�¼
	int DeletefromDB(QString TableName, QString WordbyDelete, QString WordbyDeleteValue);//ɾ��ĳһ�м�¼
	QString QueryfromDB(QString TableName, QString BeQueryWord, QString ConditionWord, QString ConditionWordValue);//��ѯ��¼
	int UpdateDB(QString TableName, QString BeUpdateWord, QString ConditionWord, QString BeUpdateWordValue, QString ConditionWordValue);//�޸ĸ��¼�¼
	QSqlDatabase getDatabase();
	int AddtoDB_BatterySelect(QString TableName, QString SN, QString VoltageValue, QString VoltageGrade);
	int AddtoDB_CaseandBattery(QString TableName, QString CaseSN, QString SN1, QString SN2, QString SN3, QString SN4, QString SN5, QString SN6, QString SN7, QString SN8, QString SN9, QString SN10, QString SN11, QString SN12, QString SN13, QString SN14, QString SN15, QString SN16, QString SN17, QString SN18, QString SN19, QString SN20, QString SN21, QString SN22, QString SN23, QString SN24, QString SN25, QString SN26, QString SN27, QString SN28, QString SN29, QString SN30, QString SN31, QString SN32, QString SN33, QString SN34, QString SN35, QString SN36, QString SN37, QString SN38, QString SN39, QString SN40, QString SN41, QString SN42, QString SN43, QString SN44, QString SN45, QString SN46, QString SN47, QString SN48, QString SN49, QString SN50, QString SN51, QString SN52, QString SN53, QString SN54, QString SN55, QString SN56);

	//ƽ�����
	int createDB_VoltageMeasure(QString connect_mysql, QString databasename, QString tablename, QString StandardClass, QString V_Lower, QString V_Upper);
	int AddtoDB_SettingVoltageStanard(QString TableName, QString StandardClass, QString V_Lower, QString V_Upper);
private:
	QSqlDatabase database;
};

#endif // !USEMYSQL_H