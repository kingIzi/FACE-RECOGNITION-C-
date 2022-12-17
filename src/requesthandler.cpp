#include "requesthandler.hpp"

#include <QtNetwork/QHostAddress>
#include <QtCore/QDebug>
#include <QtHttpServer/QHttpServerRequest>



RequestHandler::RequestHandler(int argc,char * argv[],const char* argument) : 
    app(argc,argv),
    argument(argument),
    faceDetect(nullptr)
{
    const auto separator = ';';
    const auto filePaths = this->argument.split(";");
    try
    {
        if (filePaths.length() != 2) {
            throw std::invalid_argument("Could not locate train or test dataset directory. Please verify");
        }
        const auto trainData = filePaths.first().toStdString();
        const auto testData = filePaths.back().toStdString();
        this->faceDetect = std::make_unique<FaceDetect>(trainData.c_str(),testData.c_str());
        this->initialize();
    }
    catch(const std::invalid_argument& e)
    {
        qDebug() << e.what();
        exit(-1);
    }
    
}

int RequestHandler::startListening()
{
    const auto port = this->server.listen(QHostAddress::LocalHost,3000);
    if (!port) { return -1; }
    qDebug() << QCoreApplication::translate("QHttpServerExample",
            "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);
    return this->app.exec();
}

void RequestHandler::initialize()
{
    this->predictName();
    this->trainNewName();
}

void RequestHandler::predictName()
{
    this->server.route("/find/<arg>",QHttpServerRequest::Method::Get,[this](const QString& file,const QHttpServerRequest& request){
        const auto response = this->faceDetect->predictFace(file.toStdString());
        return response;
    });
}


void RequestHandler::trainNewName()
{
    this->server.route("/train/<arg>", QHttpServerRequest::Method::Get,
    [this](const QString& id,const QHttpServerRequest &request) {
        const auto response = this->faceDetect->trainDataset(id.toStdString());
        return response;
    });
}
