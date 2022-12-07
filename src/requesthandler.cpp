#include "requesthandler.hpp"

#include <QtNetwork/QHostAddress>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>
#include <QtHttpServer/QHttpServerRequest>
#include <QtCore/QJsonObject>



RequestHandler::RequestHandler(char * baseDatasetUrl[]) : 
    faceDetect(std::make_unique<FaceDetect>(baseDatasetUrl[1],baseDatasetUrl[2]))
{

}

void RequestHandler::startListening()
{
    const auto port = this->server.listen(QHostAddress::LocalHost,3000);
    if (!port) { return; }
    qDebug() << QCoreApplication::translate("QHttpServerExample",
            "Running on http://127.0.0.1:%1/ (Press CTRL+C to quit)").arg(port);

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
