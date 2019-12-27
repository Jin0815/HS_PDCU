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
	void PlcTest();//PLC���Խ���
	void SqlTest();//MySQL���ݿ���Խ���
	void OnAddLog(QString log);//�����־������
	void MeasureStart();//��ʼ����
	void MeasureStop();//ֹͣ����
	void SetRequirement();//�����ж���׼
	void Login();//��¼Ȩ��ѡ�����
	void OpenLog();//����־��Ŀ¼
	void OpenProductData();//�򿪲�Ʒ������Ŀ¼
	void SetPassWord();//�޸�Ȩ������
};
