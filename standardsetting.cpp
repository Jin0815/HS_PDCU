#include "standardsetting.h"

StandardSetting::StandardSetting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	mysql = new UseMySQL();
	mysql->connectMYSQL("MySQL");
	mysql->createDB_VoltageMeasure("MySQL","VoltageMeasure","SetStandardValue","StandardClass","V_Lower","V_Upper");
	ui.doubleSpinBox_maxmin_Low->setValue((mysql->QueryfromDB("SetStandardValue","V_Lower","StandardClass","Max_Min")).toDouble());
	ui.doubleSpinBox_maxmin_Up->setValue((mysql->QueryfromDB("SetStandardValue", "V_Upper", "StandardClass", "Max_Min")).toDouble());
	ui.doubleSpinBox_VValue_Low->setValue((mysql->QueryfromDB("SetStandardValue", "V_Lower", "StandardClass", "VValue")).toDouble());
	ui.doubleSpinBox_VValue_Up->setValue((mysql->QueryfromDB("SetStandardValue", "V_Upper", "StandardClass", "VValue")).toDouble());
	connect(ui.pushButton_YESandSAVE,SIGNAL(clicked()),this,SLOT(SaveSetting()));
}

StandardSetting::~StandardSetting()
{
	delete mysql;
}

void StandardSetting::SaveSetting()
{
	QString MaxMin_VLower = QString::number(ui.doubleSpinBox_maxmin_Low->value());
	QString MaxMin_VUper = QString::number(ui.doubleSpinBox_maxmin_Up->value());
	QString VVlaue_VLower = QString::number(ui.doubleSpinBox_VValue_Low->value());
	QString VValue_VUper = QString::number(ui.doubleSpinBox_VValue_Up->value());
	mysql->DeletefromDB("SetStandardValue","StandardClass","Max_Min");
	mysql->DeletefromDB("SetStandardValue", "StandardClass", "VValue");
	mysql->AddtoDB_SettingVoltageStanard("SetStandardValue", "Max_Min", MaxMin_VLower, MaxMin_VUper);
	mysql->AddtoDB_SettingVoltageStanard("SetStandardValue", "VValue", VVlaue_VLower, VValue_VUper);
}
