#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_voltagemeasure.h"
#include "plcdata.h"
#include "mysqldata.h"
#include "qtlogin.h"
#include <QDesktopServices>
#include "standardsetting.h"


class VoltageMeasure : public QMainWindow
{
	Q_OBJECT

public:
	VoltageMeasure(QWidget *parent = Q_NULLPTR);

private:
	Ui::VoltageMeasureClass ui;

private slots:
	void PlcTest();//PLC测试界面
	void SqlTest();//MySQL数据库测试界面
	void OnAddLog(QString log);//添加日志到界面
	void MeasureStart();//开始测量
	void MeasureStop();//停止测量
	void SetRequirement();//设置判定标准
	void Login();//登录权限选择界面
	void OpenLog();//打开日志主目录
	void OpenProductData();//打开产品数据主目录
	void SetPassWord();//修改权限密码
};
