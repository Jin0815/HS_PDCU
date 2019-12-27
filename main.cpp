#include "voltagemeasure.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VoltageMeasure w;
	QtLogin login;
	login.show();
	if (login.exec() == QDialog::Accepted)//调用login.exec()，阻塞主控制流，直到完成返回，继续执行主控制流
	{
		w.show();
		return a.exec();
	}
	else
		return 0;
	return a.exec();
}
