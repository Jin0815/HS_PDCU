#include "voltagemeasure.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VoltageMeasure w;
	QtLogin login;
	login.show();
	if (login.exec() == QDialog::Accepted)//����login.exec()����������������ֱ����ɷ��أ�����ִ����������
	{
		w.show();
		return a.exec();
	}
	else
		return 0;
	return a.exec();
}
