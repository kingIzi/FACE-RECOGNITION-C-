#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

#include <QtCore/QCoreApplication>

#include "requesthandler.hpp"



int main(int argc,char* argv[])
{
    QCoreApplication app(argc,argv);
    RequestHandler requests(argv);
    requests.initialize();
    requests.startListening();
    return app.exec();
}





