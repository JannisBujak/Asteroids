// QTProject.cpp : Defines the entry point for the application.
//

#include "QTProject.h"


using namespace std;

int main(int argc, char** argv)
{	
	QApplication app(argc, argv);

	QPushButton button;
	button.setText("My text");
	button.setToolTip("A tooltip");
	button.show();

	return app.exec();
}
