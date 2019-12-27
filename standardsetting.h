#pragma once

#include <QWidget>
#include "ui_standardsetting.h"
#include "usemysql.h"

class StandardSetting : public QWidget
{
	Q_OBJECT

public:
	StandardSetting(QWidget *parent = Q_NULLPTR);
	~StandardSetting();

private:
	Ui::StandardSetting ui;
	UseMySQL *mysql;

private slots:
	void SaveSetting();
};
