#pragma once

#include <memory>

#include <QtHttpServer/QHttpServer>
#include <QtCore/QString>

#include "facedetect.hpp"

class RequestHandler{
    private:
        char* argv = new char[0];
        std::unique_ptr<FaceDetect> faceDetect = nullptr;
    private:
        QHttpServer server;
        void predictName();
        void trainNewName();
    public:
        RequestHandler(char * argv[]);
        void startListening();
        void initialize();
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