#include <QWidget>
#include "ui_plcdata.h"
#include <actprogtypelib.h>
#include <actutltypelib.h>
#include<QVector>
#include <QLine>
#include <QIntValidator>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>

class PLCData : public QWidget
{
	Q_OBJECT

public:
	explicit PLCData(QWidget *parent = Q_NULLPTR);
	~PLCData();
private:
	Ui::PLCData ui;
	/*ActProgTypeLib::ActProgType myplc;*/
	ActUtlTypeLib::ActUtlType myplc;
	QString szCpuName;
	qint32 lCpuType;
	qint32 iRet;
	int lpsData_l;//实际只用低16位
	int lpsData_h;//实际只用低16位
	qint64 lpsData_all;//实际只用低32位
	qint16 lpsData2;
	int *mylpsData;
	bool ok;
	QByteArray buf;
	QByteArray buf2;
private slots:
	void OpenPLC();
	void ClosePLC();
	QString ReadPLC();
	void WritePLC();
	QString ReadPLCBlock();
	void WritePLCBlock();
};
