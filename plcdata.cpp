#include "plcdata.h"

PLCData::PLCData(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.BT_OpenPLC,SIGNAL(clicked()),this,SLOT(OpenPLC()));
	connect(ui.BT_ClosePLC, SIGNAL(clicked()), this, SLOT(ClosePLC()));
	connect(ui.BT_ReadPLC, SIGNAL(clicked()), this, SLOT(ReadPLC()));
	connect(ui.BT_WritePLC, SIGNAL(clicked()), this, SLOT(WritePLC()));
	connect(ui.BT_ReadPLC_Block, SIGNAL(clicked()), this, SLOT(ReadPLCBlock()));
}
PLCData::~PLCData()
{
}
//������Ժ���
void PLCData::OpenPLC()
{
	myplc.SetActLogicalStationNumber(3);
	myplc.SetActPassword("");
	qDebug() << "myplc";
	//ͨѶ��·��
	iRet = myplc.Open();
	qDebug("return:%x", iRet);
	if (iRet == 0x00)
	{
		//�ɱ�̿�����CPU�ͺŻ�ȡ
		iRet = myplc.GetCpuType(szCpuName, lCpuType);
		qDebug("return:%x szCpuName:%s lCpuType:%d", iRet, qPrintable(szCpuName), lCpuType);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ӳɹ���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��򿪶˿ڣ�"));
	}
}
void PLCData::ClosePLC()
{
	//ͨѶ��·�ر�
	qDebug() << "close";
	iRet = myplc.Close();
	qDebug("return:%x", iRet);
	if (iRet == 0x00)
	{
		//�ɱ�̿�����CPU�ͺŻ�ȡ
		iRet = myplc.GetCpuType(szCpuName, lCpuType);
		qDebug("return:%x szCpuName:%s lCpuType:%d", iRet, qPrintable(szCpuName), lCpuType);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�رճɹ���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷��رն˿ڣ�"));
	}
}
QString PLCData::ReadPLC()
{
	QString plcdevicename = ui.LineEdit_DeviceName->text();
	/*QString Value = ui.LineEdit_ReadPLC->text();*/
	int Value;
	iRet=myplc.GetDevice(plcdevicename, Value);
	ui.textshowReadPLC->setText(QString::number(Value));
	if (iRet == 0x00)
	{
		//�ɱ�̿�����CPU�ͺŻ�ȡ
		iRet = myplc.GetCpuType(szCpuName, lCpuType);
		qDebug("return:%x szCpuName:%s lCpuType:%d", iRet, qPrintable(szCpuName), lCpuType);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��ȡ�ɹ���"));
		
		return QString::number(Value);
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷���ȡPLC���ݣ�"));
		return 0;
	}
}
void PLCData::WritePLC()
{
	QString plcdevicename = ui.LineEdit_DeviceName->text();
	int Value = ui.LineEdit_WritePLCValue->text().toInt();
	myplc.SetDevice(plcdevicename,Value);
	if (iRet == 0x00)
	{
		//�ɱ�̿�����CPU�ͺŻ�ȡ
		iRet = myplc.GetCpuType(szCpuName, lCpuType);
		qDebug("return:%x szCpuName:%s lCpuType:%d", iRet, qPrintable(szCpuName), lCpuType);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("д��ɹ���"));
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�д��PLC���ݣ�"));
	}
}
QString PLCData::ReadPLCBlock()
{
	QString plcdevicename =ui.LineEdit_DeviceName->text();
	QStringList plcdevicenames = plcdevicename.split(",");
	int Size = ui.lineEdit_readplcNUM->text().toInt(&ok, 10);
	QString result;
	for (int i=0;i<Size;i++)
	{
		int Value;
		QString PLCNAME = plcdevicenames.at(i);
		iRet = myplc.GetDevice(PLCNAME, Value);
		result += QString::number(Value)+",";
	}
	result = result.left(result.size() - 1);
	ui.textshowReadPLC->setText(result);
	if (iRet == 0x00)
	{
		//�ɱ�̿�����CPU�ͺŻ�ȡ
		iRet = myplc.GetCpuType(szCpuName, lCpuType);
		qDebug("return:%x szCpuName:%s lCpuType:%d", iRet, qPrintable(szCpuName), lCpuType);
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("������ȡ�ɹ���"));
		return result;
	}
	else
	{
		QMessageBox::about(nullptr, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�޷�������ȡPLC���ݣ�"));
		return 0;
	}
}
void PLCData::WritePLCBlock()
{

}

