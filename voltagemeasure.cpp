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
	if (login.exec() == QDialog::Accepted)//����login.exec()����������������ֱ����ɷ��أ�����ִ����������
	{
		if (QtLogin::LoginClass == "operator")
		{
			//����ԱȨ��
			OnAddLog(QString::fromLocal8Bit("��ǰѡ�����Աģʽ..."));
			ui.BT_MySQLTest->setEnabled(false);
			ui.BT_PLCTest->setEnabled(false);
			ui.menu_setting->setEnabled(false);
		}
		else if (QtLogin::LoginClass == "technician")
		{
			//����ԱȨ��
			OnAddLog(QString::fromLocal8Bit("��ǰѡ����Աģʽ..."));
			//������Ӧ����
			ui.BT_MySQLTest->setEnabled(false);
			ui.BT_PLCTest->setEnabled(false);
			ui.menu_setting->setEnabled(true);
		}
		else if (QtLogin::LoginClass == "engineer")
		{
			//����ʦȨ��
			OnAddLog(QString::fromLocal8Bit("��ǰѡ�񹤳�ʦģʽ..."));
			//������Ӧ����
			ui.BT_MySQLTest->setEnabled(true);
			ui.BT_PLCTest->setEnabled(true);
			ui.menu_setting->setEnabled(true);
		}
		else
		{
			//����
			OnAddLog(QString::fromLocal8Bit("��ǰѡ��ģʽ����..."));
		}

	}
	else
	{
		//��¼Ȩ�޳���
		OnAddLog(QString::fromLocal8Bit("��ǰ��¼Ȩ�޳���..."));
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