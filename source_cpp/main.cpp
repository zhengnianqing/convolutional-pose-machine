#include "pose_re.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	//QApplication::addLibraryPath("./ plugins");
	//QApplication::addL("./qtdll");

	QApplication a(argc, argv);
	Pose_Re w;
	w.show();
	return a.exec();
}

