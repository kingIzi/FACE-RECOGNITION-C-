#pragma once

#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <QtCore/QJsonObject>

class FaceDetect{
    private:
        std::string trainningDataset;
        std::string testingDataset;
        cv::Ptr<cv::face::LBPHFaceRecognizer> model;
    private:
        void read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
        void read_csv_as_filenames(const std::string& filename, std::vector<std::string>& images, std::vector<int>& labels, char separator = ';');
        const std::string findNameByClassLabel(int& predictedLabel);
        void appendTrainnedModelNames(const std::string& name,const int& classLabel) const;
    public: 
        FaceDetect(const char* trainningDataset,const char* testingDataset);
        void trainDataset();
        QJsonObject trainDataset(const std::string& identifier);
        const QJsonObject predictFace(const std::string& filePath);
};