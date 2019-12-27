#ifndef GETPLCDATA_H
#define GETPLCDATA_H

#include <actprogtypelib.h>
#include <actutltypelib.h>
#include<QVector>
#include <QLine>
#include <QIntValidator>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <QObject>
#include <map>
#include <string>
#include <ctime>
#include <time.h>
using namespace spdlog;
class GetPLCData : public QObject
{
	Q_OBJECT

public:
	explicit GetPLCData(QObject *parent = Q_NULLPTR);
	~GetPLCData();
	//PLC1
	int OpenPLC1();
	int ClosePLC1();
	QString ReadPLC1(QString devicename);
	int WritePLC1(QString devicename, int value);
	QString ReadPLCBlock1(QString devicenames, int num);
	int WritePLCBlock1();
	//PLC2
	int OpenPLC2();
	int ClosePLC2();
	QString ReadPLC2(QString devicename);
	int WritePLC2(QString devicename, int value);
	QString ReadPLCBlock2(QString devicenames, int num);
	int WritePLCBlock2();
	//PLC3
	int OpenPLC3();
	int ClosePLC3();
	QString ReadPLC3(QString devicename);
	static int plc1_D2000;//分选机触发信号
	void FlushPLC_inturn3();//线程循环读取PLC3
	//PLC4
	int OpenPLC4();
	int ClosePLC4();
	QString ReadPLC4(QString devicename);
	static int plc2_D1999;//入支架电池绑定码
	static int plc2_D2000;//入支架电池电压等级复判
	void FlushPLC_inturn4();//线程循环读取PLC4
	//PLC5
	int OpenPLC5();
	int ClosePLC5();
	QString ReadPLC5(QString devicename);
	int WritePLC5(QString devicename, int value);
	QString ReadPLCBlock5(QString devicenames, int num);
	int WritePLCBlock5();

private:
	ActUtlTypeLib::ActUtlType myplc1;
	ActUtlTypeLib::ActUtlType myplc2;
	ActUtlTypeLib::ActUtlType myplc3;
	ActUtlTypeLib::ActUtlType myplc4;
	ActUtlTypeLib::ActUtlType myplc5;
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
};
#endif // !GETPLCDATA_H