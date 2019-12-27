#pragma once

#include <QDialog>
#include "ui_qtlogin.h"

class QtLogin : public QDialog
{
	Q_OBJECT

public:
	QtLogin(QWidget *parent = Q_NULLPTR);
	~QtLogin();
	static QString Name_operator;
	static QString Name_technician;
	static QString Name_engineer;
	static QString password_operator;
	static QString password_technician;
	static QString password_engineer;
	static QString LoginClass;

private:
	Ui::QtLogin ui;
	

signals:

public slots:
	void login();//点击登录按钮是执行的槽函数
};
