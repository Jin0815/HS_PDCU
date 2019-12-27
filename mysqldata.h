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
	void connectMYSQL(QString connect_mysql);//创建一个MySQL连接
	void connectDBTable(QString  connect_mysql, QString databasename);//连接某一个数据库的某一个表
	void createDB(QString connect_mysql, QString databasename, QString tablename);//创建一个数据库以及某一个表
	void closeDBTable(QString  connect_mysql, QString databasename);//关闭某一个数据库的某一个表
	void ShowDatabaseTable(QString databasename, QString tablename);//将表格数据显示出来
	void AddtoDB(QString TableName);//增加某一行记录
	void DeletefromDB(QString TableName);//删除某一行记录
	QString QueryfromDB(QString TableName, QString BeQueryWord, QString ConditionWord, QString ConditionWordValue);//查询记录
	void UpdateDB(QString TableName, QString BeUpdateWord, QString ConditionWord, QString BeUpdateWordValue, QString ConditionWordValue);//修改更新记录
	
private:
	Ui::MySQLData ui;
	QSqlDatabase database;
	
private slots:
	void BT_testsql_Clicked();
};
