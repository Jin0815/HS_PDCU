#include "voltagemeasure.h"

VoltageMeasure::VoltageMeasure(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.BT_PLCTest,SIGNAL(clicked()),this,SLOT(PlcTest()));
	connect(ui.BT_MySQLTest, SIGNAL(clicked()), this, SLOT(SqlTest()));
	connect(ui.action_operator, SIGNAL(triggered()), this, SLOT(Login()));
	connect(ui.action_engineer, SIGNAL(triggered()), this, SLOT(Login()));
	connect(ui.action_technician, SIGNAL(triggered()), this, SLOT(Login()));
	connect(ui.action_viewlog, SIGNAL(triggered()), this, SLOT(OpenLog()));
	connect(ui.action_viewproductdata, SIGNAL(triggered()), this, SLOT(OpenProductData()));
	connect(ui.action_setstandard, SIGNAL(triggered()), this, SLOT(SetRequirement()));
}


void VoltageMeasure::PlcTest()
{
	PLCData *plctest = new PLCData();
	plctest->show();
}

void VoltageMeasure::SqlTest()
{
	MySQLData *mysqltest = new MySQLData();
	mysqltest->show();
}

void VoltageMeasure::OnAddLog(QString log)
{
	QString Log = log;
	QDateTime current_data_time = QDateTime::currentDateTime();
	QString current_data = current_data_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
	ui.textBrowser_Log->append("[" + current_data + "]   " + Log);
}

void VoltageMeasure::MeasureStart()
{

}

void VoltageMeasure::MeasureStop()
{

}

void VoltageMeasure::SetRequirement()
{
	StandardSetting *setting = new StandardSetting();
	setting->show();
}

void VoltageMeasure::Login()
{
	QtLogin login;
	login.show();
	if (login.exec() == QDialog::Accepted)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
	{
		if (QtLogin::LoginClass == "operator")
		{
			//操作员权限
			OnAddLog(QString::fromLocal8Bit("当前选择操作员模式..."));
			ui.BT_MySQLTest->setEnabled(false);
			ui.BT_PLCTest->setEnabled(false);
			ui.menu_setting->setEnabled(false);
		}
		else if (QtLogin::LoginClass == "technician")
		{
			//技术员权限
			OnAddLog(QString::fromLocal8Bit("当前选择技术员模式..."));
			//开放相应功能
			ui.BT_MySQLTest->setEnabled(false);
			ui.BT_PLCTest->setEnabled(false);
			ui.menu_setting->setEnabled(true);
		}
		else if (QtLogin::LoginClass == "engineer")
		{
			//工程师权限
			OnAddLog(QString::fromLocal8Bit("当前选择工程师模式..."));
			//开放相应功能
			ui.BT_MySQLTest->setEnabled(true);
			ui.BT_PLCTest->setEnabled(true);
			ui.menu_setting->setEnabled(true);
		}
		else
		{
			//错误
			OnAddLog(QString::fromLocal8Bit("当前选择模式错误..."));
		}

	}
	else
	{
		//登录权限出错
		OnAddLog(QString::fromLocal8Bit("当前登录权限出错..."));
	}
}

void VoltageMeasure::OpenLog()
{
	QString Path = QCoreApplication::applicationDirPath() + "/LOGS";
	QDesktopServices::openUrl(QUrl::fromLocalFile(Path));
}

void VoltageMeasure::OpenProductData()
{
	QString Path = QCoreApplication::applicationDirPath() + "/ProductData";
	QDesktopServices::openUrl(QUrl::fromLocalFile(Path));
}

void VoltageMeasure::SetPassWord()
{

}