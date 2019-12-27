#include "GetPLCData.h"
//��ʼ����־��¼
	//��ȡϵͳ��ǰʱ��
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

//�����߳�PLC1��PLC2
//PLC1--�߼�վ��1
int GetPLCData::OpenPLC1()
{
	myplc1.SetActLogicalStationNumber(1);
	myplc1.SetActPassword("");
	//ͨѶ��·��
	iRet = myplc1.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC1���ӳɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӳɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC1����ʧ�ܣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��򿪶˿ڣ�"));
	}
}
int GetPLCData::ClosePLC1()
{
	myplc1.SetActLogicalStationNumber(1);
	myplc1.SetActPassword("");
	//ͨѶ��·�ر�
	iRet = myplc1.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC1�رճɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�رճɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC1�޷��رն˿ڣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��رն˿ڣ�"));
	}
}
QString GetPLCData::ReadPLC1(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc1.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC1��ȡ�ɹ�����");
		rotating_logger1->flush();
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC1��ȡʧ�ܣ���");
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
		rotating_logger1->info("����д��PLC1�ɹ�����");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("д��ɹ���"));
	}
	else
	{
		rotating_logger1->info("����д��PLC1ʧ�ܣ���");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�д��PLC���ݣ�"));
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
		rotating_logger1->info("PLC1������ȡ�ɹ�����");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("������ȡ�ɹ���"));
		return result;
	}
	else
	{
		rotating_logger1->info("PLC1������ȡʧ�ܣ���");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�������ȡPLC���ݣ�"));
		return "0";
	}
}
int GetPLCData::WritePLCBlock1()
{
	return 0;
}
//PLC2--�߼�վ��2
int GetPLCData::OpenPLC2()
{
	myplc2.SetActLogicalStationNumber(2);
	myplc2.SetActPassword("");
	//ͨѶ��·��
	iRet = myplc2.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC2���ӳɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӳɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC2����ʧ�ܣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��򿪶˿ڣ�"));
	}
}
int GetPLCData::ClosePLC2()
{
	myplc2.SetActLogicalStationNumber(1);
	myplc2.SetActPassword("");
	//ͨѶ��·�ر�
	iRet = myplc2.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC2�رճɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�رճɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC2�޷��رն˿ڣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��رն˿ڣ�"));
	}
}
QString GetPLCData::ReadPLC2(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc2.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC2��ȡ�ɹ�����");
		rotating_logger1->flush();
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC2��ȡʧ�ܣ���");
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
		rotating_logger1->info("����д��PLC2�ɹ�����");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("д��ɹ���"));
	}
	else
	{
		rotating_logger1->info("����д��PLC2ʧ�ܣ���");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�д��PLC���ݣ�"));
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
		rotating_logger1->info("PLC2������ȡ�ɹ�����");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("������ȡ�ɹ���"));
		return result;
	}
	else
	{
		rotating_logger1->info("PLC2������ȡʧ�ܣ���");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�������ȡPLC���ݣ�"));
		return "0";
	}
}
int GetPLCData::WritePLCBlock2()
{
	return 0;
}

//ȫ���̶߳�ȡPLC3��PLC4
//PLC3--�߼�վ��3
int GetPLCData::OpenPLC3()
{
	myplc3.SetActLogicalStationNumber(3);
	myplc3.SetActPassword("");
	//ͨѶ��·��
	iRet = myplc3.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC3���ӳɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӳɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC3����ʧ�ܣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��򿪶˿ڣ�"));
	}
}
int GetPLCData::ClosePLC3()
{
	myplc3.SetActLogicalStationNumber(3);
	myplc3.SetActPassword("");
	//ͨѶ��·�ر�
	iRet = myplc3.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC3�رճɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�رճɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC3�޷��رն˿ڣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��رն˿ڣ�"));
	}
}
QString GetPLCData::ReadPLC3(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc3.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC3��ȡ�ɹ�����");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��ȡ�ɹ���"));
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC3��ȡʧ�ܣ���");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷���ȡPLC���ݣ�"));
		return "0";
	}
}
void GetPLCData::FlushPLC_inturn3()
{
	while(true)
	{
		_sleep(100);
		plc1_D2000 = ReadPLC3("D2000").toInt();
		rotating_logger1->info("plc3-��ѡ��(D2000):");
		rotating_logger1->info(plc1_D2000);
		rotating_logger1->flush();
	}
}
//PLC4--�߼�վ��4
int GetPLCData::OpenPLC4()
{
	myplc4.SetActLogicalStationNumber(4);
	myplc4.SetActPassword("");
	//ͨѶ��·��
	iRet = myplc4.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC4���ӳɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӳɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC4����ʧ�ܣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��򿪶˿ڣ�"));
	}
}
int GetPLCData::ClosePLC4()
{
	myplc3.SetActLogicalStationNumber(4);
	myplc3.SetActPassword("");
	//ͨѶ��·�ر�
	iRet = myplc4.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC4�رճɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�رճɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC4�޷��رն˿ڣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��رն˿ڣ�"));
	}
}
QString GetPLCData::ReadPLC4(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc4.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC4��ȡ�ɹ�����");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��ȡ�ɹ���"));
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC4��ȡʧ�ܣ���");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷���ȡPLC���ݣ�"));
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
		rotating_logger1->info("plc4-��֧��(D1999):");
		rotating_logger1->info(plc2_D1999);
		rotating_logger1->info("plc4-��֧��(D2000):");
		rotating_logger1->info(plc2_D2000);
		rotating_logger1->flush();
	}
}

//PLC5--�߼�վ��5
int GetPLCData::OpenPLC5()
{
	myplc5.SetActLogicalStationNumber(5);
	myplc5.SetActPassword("");
	//ͨѶ��·��
	iRet = myplc5.Open();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC5���ӳɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӳɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC5����ʧ�ܣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��򿪶˿ڣ�"));
	}
}
int GetPLCData::ClosePLC5()
{
	myplc5.SetActLogicalStationNumber(5);
	myplc5.SetActPassword("");
	//ͨѶ��·�ر�
	iRet = myplc5.Close();
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC5�رճɹ���");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�رճɹ���"));
	}
	else
	{
		rotating_logger1->info("PLC5�޷��رն˿ڣ�");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��رն˿ڣ�"));
	}
}
QString GetPLCData::ReadPLC5(QString devicename)
{
	QString plcdevicename = devicename;
	int Value;
	iRet = myplc5.GetDevice(plcdevicename, Value);
	if (iRet == 0x00)
	{
		rotating_logger1->info("PLC5��ȡ�ɹ�����");
		rotating_logger1->flush();
		return QString::number(Value);
	}
	else
	{
		rotating_logger1->info("PLC5��ȡʧ�ܣ���");
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
		rotating_logger1->info("����д��PLC5�ɹ�����");
		rotating_logger1->flush();
		return 1;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("д��ɹ���"));
	}
	else
	{
		rotating_logger1->info("����д��PLC5ʧ�ܣ���");
		rotating_logger1->flush();
		return 0;
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�д��PLC���ݣ�"));
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
		rotating_logger1->info("PLC5������ȡ�ɹ�����");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("������ȡ�ɹ���"));
		return result;
	}
	else
	{
		rotating_logger1->info("PLC5������ȡʧ�ܣ���");
		rotating_logger1->flush();
		//QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�������ȡPLC���ݣ�"));
		return "0";
	}
}
int GetPLCData::WritePLCBlock5()
{
	return 0;
}
