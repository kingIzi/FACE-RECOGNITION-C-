#pragma once

#include <memory>

#include <QtHttpServer/QHttpServer>
#include <QtCore/QString>
#include <QtCore/QCoreApplication>

#include "facedetect.hpp"

class RequestHandler{
    private:
        QCoreApplication app;
        QString argument;
        std::unique_ptr<FaceDetect> faceDetect = nullptr;
    private:
        QHttpServer server;
        void predictName();
        void trainNewName();
        void initialize();
    public:
        RequestHandler(int argc,char * argv[],const char* argument);
        int startListening();
};

// class RequestHandler{
//     private:
//         char* argv = new char[0];
//         std::unique_ptr<FaceDetect> faceDetect = nullptr;
//     private:
//         QHttpServer server;
//         void predictName();
//         void trainNewName();
//     public:
//         RequestHandler(char * argv[]);
//         void startListening();
//         void initialize();
// };