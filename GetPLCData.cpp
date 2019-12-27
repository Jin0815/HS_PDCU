#include "GetPLCData.h"
//初始化日志记录
	//获取系统当前时间
time_t currentTime1 = time(NULL);
struct tm* t1 = localtime(&currentTime1);
auto rotating_logger1 = rotating_logger_mt("plc1_log", "LOGS/" + std::to_string(1900 + t1->tm_year) + "-" + std::to_string(1 + t1->tm_mon) + "-" + std::to_string(t1->tm_mday) + "/PLC1_log/log.txt", 1048576 * 5, 3);
int GetPLCData::plc1_D2000 = 0;
int GetPLCData::plc2_D1999 = 0;
int GetPLCData::plc2_D2000 = 0;
GetPLCData::GetPLCData(QObject *parent)
	: QObject(parent)
{
	
}
GetPLCData::~GetPLCData()
{
}

//工作线程PLC1和PLC2
//PLC1--逻辑站点1
int GetPLCData::OpenPLC1()
{
	myplc1.SetActLogicalStationNumber(1);
	myplc1.SetActPassword("");
	//通讯线路打开
	iRet = myplc1.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC1连接成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接成功！"));
	}
	else
	{
		rotating_logger1->info("PLC1连接失败！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法打开端口！"));
	}
}
int GetPLCData::ClosePLC1()
{
	myplc1.SetActLogicalStationNumber(1);
	myplc1.SetActPassword("");
	//通讯线路关闭
	iRet = myplc1.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC1关闭成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("关闭成功！"));
	}
	else
	{
		rotating_logger1->info("PLC1无法关闭端口！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法关闭端口！"));
	}
}
QString GetPLCData::ReadPLC1(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc1.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC1读取成功！！");
		rotating_logger1->flush();
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC1读取失败！！");
		rotating_logger1->flush();
		return "0";
	}
}
int GetPLCData::WritePLC1(QString devicename,int value)
{
	QString plcdevicename = devicename;
	int Value = value;
	myplc1.SetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("数据写入PLC1成功！！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("写入成功！"));
	}
	else
	{
		rotating_logger1->info("数据写入PLC1失败！！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法写入PLC数据！"));
	}
}
QString GetPLCData::ReadPLCBlock1(QString devicenames,int num)
{
	QStringList plcdevicenames = devicenames.split(",");
	int Size = num;
	QString result;
	for (int i = 0; i < Size; i++)
	{
		int Value;
		QString PLCNAME = plcdevicenames.at(i);
		iRet = myplc1.GetDevice(PLCNAME, Value);
		result += QString::number(Value) + ",";
	}
	result = result.left(result.size() - 1);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC1批量读取成功！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("批量读取成功！"));
		return result;
	}
	else
	{
		rotating_logger1->info("PLC1批量读取失败！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法批量读取PLC数据！"));
		return "0";
	}
}
int GetPLCData::WritePLCBlock1()
{
	return 0;
}
//PLC2--逻辑站点2
int GetPLCData::OpenPLC2()
{
	myplc2.SetActLogicalStationNumber(2);
	myplc2.SetActPassword("");
	//通讯线路打开
	iRet = myplc2.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC2连接成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接成功！"));
	}
	else
	{
		rotating_logger1->info("PLC2连接失败！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法打开端口！"));
	}
}
int GetPLCData::ClosePLC2()
{
	myplc2.SetActLogicalStationNumber(1);
	myplc2.SetActPassword("");
	//通讯线路关闭
	iRet = myplc2.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC2关闭成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("关闭成功！"));
	}
	else
	{
		rotating_logger1->info("PLC2无法关闭端口！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法关闭端口！"));
	}
}
QString GetPLCData::ReadPLC2(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc2.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC2读取成功！！");
		rotating_logger1->flush();
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC2读取失败！！");
		rotating_logger1->flush();
		return "0";
	}
}
int GetPLCData::WritePLC2(QString devicename, int value)
{
	QString plcdevicename = devicename;
	int Value = value;
	myplc2.SetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("数据写入PLC2成功！！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("写入成功！"));
	}
	else
	{
		rotating_logger1->info("数据写入PLC2失败！！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法写入PLC数据！"));
	}
}
QString GetPLCData::ReadPLCBlock2(QString devicenames, int num)
{
	QStringList plcdevicenames = devicenames.split(",");
	int Size = num;
	QString result;
	for (int i = 0; i < Size; i++)
	{
		int Value;
		QString PLCNAME = plcdevicenames.at(i);
		iRet = myplc2.GetDevice(PLCNAME, Value);
		result += QString::number(Value) + ",";
	}
	result = result.left(result.size() - 1);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC2批量读取成功！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("批量读取成功！"));
		return result;
	}
	else
	{
		rotating_logger1->info("PLC2批量读取失败！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法批量读取PLC数据！"));
		return "0";
	}
}
int GetPLCData::WritePLCBlock2()
{
	return 0;
}

//全局线程读取PLC3和PLC4
//PLC3--逻辑站点3
int GetPLCData::OpenPLC3()
{
	myplc3.SetActLogicalStationNumber(3);
	myplc3.SetActPassword("");
	//通讯线路打开
	iRet = myplc3.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC3连接成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接成功！"));
	}
	else
	{
		rotating_logger1->info("PLC3连接失败！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法打开端口！"));
	}
}
int GetPLCData::ClosePLC3()
{
	myplc3.SetActLogicalStationNumber(3);
	myplc3.SetActPassword("");
	//通讯线路关闭
	iRet = myplc3.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC3关闭成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("关闭成功！"));
	}
	else
	{
		rotating_logger1->info("PLC3无法关闭端口！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法关闭端口！"));
	}
}
QString GetPLCData::ReadPLC3(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc3.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC3读取成功！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("读取成功！"));
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC3读取失败！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法读取PLC数据！"));
		return "0";
	}
}
void GetPLCData::FlushPLC_inturn3()
{
	while(true)
	{
		_sleep(100);
		plc1_D2000 = ReadPLC3("D2000").toInt();
		rotating_logger1->info("plc3-分选机(D2000):");
		rotating_logger1->info(plc1_D2000);
		rotating_logger1->flush();
	}
}
//PLC4--逻辑站点4
int GetPLCData::OpenPLC4()
{
	myplc4.SetActLogicalStationNumber(4);
	myplc4.SetActPassword("");
	//通讯线路打开
	iRet = myplc4.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC4连接成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接成功！"));
	}
	else
	{
		rotating_logger1->info("PLC4连接失败！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法打开端口！"));
	}
}
int GetPLCData::ClosePLC4()
{
	myplc3.SetActLogicalStationNumber(4);
	myplc3.SetActPassword("");
	//通讯线路关闭
	iRet = myplc4.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC4关闭成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("关闭成功！"));
	}
	else
	{
		rotating_logger1->info("PLC4无法关闭端口！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法关闭端口！"));
	}
}
QString GetPLCData::ReadPLC4(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc4.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC4读取成功！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("读取成功！"));
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC4读取失败！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法读取PLC数据！"));
		return "0";
	}
}
void GetPLCData::FlushPLC_inturn4()
{
	while (true)
	{
		_sleep(100);
		plc2_D1999 = ReadPLC4("D1999").toInt();
		plc2_D2000 = ReadPLC4("D2000").toInt();
		rotating_logger1->info("plc4-入支架(D1999):");
		rotating_logger1->info(plc2_D1999);
		rotating_logger1->info("plc4-入支架(D2000):");
		rotating_logger1->info(plc2_D2000);
		rotating_logger1->flush();
	}
}

//PLC5--逻辑站点5
int GetPLCData::OpenPLC5()
{
	myplc5.SetActLogicalStationNumber(5);
	myplc5.SetActPassword("");
	//通讯线路打开
	iRet = myplc5.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC5连接成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("连接成功！"));
	}
	else
	{
		rotating_logger1->info("PLC5连接失败！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法打开端口！"));
	}
}
int GetPLCData::ClosePLC5()
{
	myplc5.SetActLogicalStationNumber(5);
	myplc5.SetActPassword("");
	//通讯线路关闭
	iRet = myplc5.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC5关闭成功！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("关闭成功！"));
	}
	else
	{
		rotating_logger1->info("PLC5无法关闭端口！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法关闭端口！"));
	}
}
QString GetPLCData::ReadPLC5(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc5.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC5读取成功！！");
		rotating_logger1->flush();
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC5读取失败！！");
		rotating_logger1->flush();
		return "0";
	}
}
int GetPLCData::WritePLC5(QString devicename, int value)
{
	QString plcdevicename = devicename;
	int Value = value;
	myplc5.SetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("数据写入PLC5成功！！");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("写入成功！"));
	}
	else
	{
		rotating_logger1->info("数据写入PLC5失败！！");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法写入PLC数据！"));
	}
}
QString GetPLCData::ReadPLCBlock5(QString devicenames, int num)
{
	QStringList plcdevicenames = devicenames.split(",");
	int Size = num;
	QString result;
	for (int i = 0; i < Size; i++)
	{
		int Value;
		QString PLCNAME = plcdevicenames.at(i);
		iRet = myplc5.GetDevice(PLCNAME, Value);
		result += QString::number(Value) + ",";
	}
	result = result.left(result.size() - 1);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC5批量读取成功！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("批量读取成功！"));
		return result;
	}
	else
	{
		rotating_logger1->info("PLC5批量读取失败！！");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("无法批量读取PLC数据！"));
		return "0";
	}
}
int GetPLCData::WritePLCBlock5()
{
	return 0;
}
