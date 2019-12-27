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
	this->setWindowTitle(QString::fromLocal8Bit("��¼����"));
	connect(ui.pushButton_Login, SIGNAL(clicked()), this, SLOT(login()));
	connect(ui.pushButton_Exit, SIGNAL(clicked()), this, SLOT(close()));
}

QtLogin::~QtLogin()
{
}
void QtLogin::login()
{
	int test = ui.comboBox->currentIndex();
	if (ui.lineEdit_ID->text() == Name_operator && ui.lineEdit_PASSWORD->text() == password_operator && ui.comboBox->currentIndex()==0)//����Ա����
	{
		LoginClass = "operator";
		accept();//�رմ��壬�����÷���ֵΪAccepted
	}
	else if (ui.lineEdit_ID->text() == Name_technician && ui.lineEdit_PASSWORD->text() == password_technician&& ui.comboBox->currentIndex() == 1)
	{
		LoginClass = "technician";
		accept();//�رմ��壬�����÷���ֵΪAccepted
	}
	else if (ui.lineEdit_ID->text() == Name_engineer && ui.lineEdit_PASSWORD->text() == password_engineer&& ui.comboBox->currentIndex() == 2)
	{
		LoginClass = "engineer";
		accept();//�رմ��壬�����÷���ֵΪAccepted
	}
	else if (ui.comboBox->currentIndex()> ui.comboBox->count()-1)
	{
		//��������OK��ť
		QMessageBox::warning(this, QString::fromLocal8Bit("���棡"), QString::fromLocal8Bit("�빴ѡ����һ��Ȩ��ģʽ��"), QMessageBox::Yes);
		//������������
		ui.lineEdit_ID->clear();
		ui.lineEdit_PASSWORD->clear();
		//��궨λ
		ui.lineEdit_ID->setFocus();
	}
	else
	{
		//��������OK��ť
		QMessageBox::warning(this, QString::fromLocal8Bit("���棡"), QString::fromLocal8Bit("�û������������"), QMessageBox::Yes);
		//������������
		ui.lineEdit_ID->clear();
		ui.lineEdit_PASSWORD->clear();
		//��궨λ
		ui.lineEdit_ID->setFocus();
	}
}