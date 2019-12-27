#pragma once

#include <QWidget>
#include "ui_mysqldata.h"
#include <Windows.h>
#include <mysql.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <QSqlDatabase>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
using namespace spdlog;
class MySQLData : public QWidget
{
	Q_OBJECT

public:
	MySQLData(QWidget *parent = Q_NULLPTR);
	~MySQLData();
	void connectMYSQL(QString connect_mysql);//����һ��MySQL����
	void connectDBTable(QString  connect_mysql, QString databasename);//����ĳһ�����ݿ��ĳһ����
	void createDB(QString connect_mysql, QString databasename, QString tablename);//����һ�����ݿ��Լ�ĳһ����
	void closeDBTable(QString  connect_mysql, QString databasename);//�ر�ĳһ�����ݿ��ĳһ����
	void ShowDatabaseTable(QString databasename, QString tablename);//�����������ʾ����
	void AddtoDB(QString TableName);//����ĳһ�м�¼
	void DeletefromDB(QString TableName);//ɾ��ĳһ�м�¼
	QString QueryfromDB(QString TableName, QString BeQueryWord, QString ConditionWord, QString ConditionWordValue);//��ѯ��¼
	void UpdateDB(QString TableName, QString BeUpdateWord, QString ConditionWord, QString BeUpdateWordValue, QString ConditionWordValue);//�޸ĸ��¼�¼
	
private:
	Ui::MySQLData ui;
	QSqlDatabase database;
	
private slots:
	void BT_testsql_Clicked();
};
