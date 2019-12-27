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
	int lpsData_l;//ʵ��ֻ�õ�16λ
	int lpsData_h;//ʵ��ֻ�õ�16λ
	qint64 lpsData_all;//ʵ��ֻ�õ�32λ
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
