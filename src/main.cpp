#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"

#include <QtCore/QCoreApplication>

#include "requesthandler.hpp"



int main(int argc,char* argv[])
{
    RequestHandler requests(argc,argv,argv[1]);
    return requests.startListening();
}





