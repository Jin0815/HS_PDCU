#include "qtlogin.h"
#include <QMessageBox>
QString QtLogin::Name_operator = "";
QString QtLogin::Name_technician = "admin";
QString QtLogin::Name_engineer = "admin";
QString QtLogin::password_operator = "";
QString QtLogin::password_technician = "12345";
QString QtLogin::password_engineer = "12345";
QString QtLogin::LoginClass = "operator";
QtLogin::QtLogin(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("登录界面"));
	connect(ui.pushButton_Login, SIGNAL(clicked()), this, SLOT(login()));
	connect(ui.pushButton_Exit, SIGNAL(clicked()), this, SLOT(close()));
}

QtLogin::~QtLogin()
{
}
void QtLogin::login()
{
	int test = ui.comboBox->currentIndex();
	if (ui.lineEdit_ID->text() == Name_operator && ui.lineEdit_PASSWORD->text() == password_operator && ui.comboBox->currentIndex()==0)//操作员登入
	{
		LoginClass = "operator";
		accept();//关闭窗体，并设置返回值为Accepted
	}
	else if (ui.lineEdit_ID->text() == Name_technician && ui.lineEdit_PASSWORD->text() == password_technician&& ui.comboBox->currentIndex() == 1)
	{
		LoginClass = "technician";
		accept();//关闭窗体，并设置返回值为Accepted
	}
	else if (ui.lineEdit_ID->text() == Name_engineer && ui.lineEdit_PASSWORD->text() == password_engineer&& ui.comboBox->currentIndex() == 2)
	{
		LoginClass = "engineer";
		accept();//关闭窗体，并设置返回值为Accepted
	}
	else if (ui.comboBox->currentIndex()> ui.comboBox->count()-1)
	{
		//标题内容OK按钮
		QMessageBox::warning(this, QString::fromLocal8Bit("警告！"), QString::fromLocal8Bit("请勾选任意一种权限模式！"), QMessageBox::Yes);
		//清空输入框内容
		ui.lineEdit_ID->clear();
		ui.lineEdit_PASSWORD->clear();
		//光标定位
		ui.lineEdit_ID->setFocus();
	}
	else
	{
		//标题内容OK按钮
		QMessageBox::warning(this, QString::fromLocal8Bit("警告！"), QString::fromLocal8Bit("用户名或密码错误！"), QMessageBox::Yes);
		//清空输入框内容
		ui.lineEdit_ID->clear();
		ui.lineEdit_PASSWORD->clear();
		//光标定位
		ui.lineEdit_ID->setFocus();
	}
}