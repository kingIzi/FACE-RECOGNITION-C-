#pragma once

#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/highgui.hpp>

#include <string>
#include <tuple>
#include <vector>

#include <QtCore/QList>
#include <QtCore/QJsonObject>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>


class FaceDetect{
    private:
        QDir trainData;
        QDir testData;
        cv::Ptr<cv::face::LBPHFaceRecognizer> model;
        std::vector<cv::Mat> images;
        std::vector<int> labels;   
    private:
        void read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';');
        void read_csv_as_filenames(const std::string& filename, std::vector<std::string>& images, std::vector<int>& labels, char separator = ';');
        const std::string findNameByClassLabel(int& predictedLabel);
        void appendTrainnedModelNames(const std::string& name,const int& classLabel) const;
        const std::tuple<int,double,std::string> makePrediction(const std::string& filePath);
        const QList<QString> getDirNamesList(char separator = ';') const;

        const QJsonObject trainDataset(const QList<QFileInfo>& directories,const QFileInfoList::const_iterator& it,const std::string& identifier);
        void startTrainning(const std::vector<cv::Mat>& images,const std::vector<int>& labels);
        const QJsonObject startTrainning(const QList<QFileInfo>& files,const std::string& identifier,const int indexOf,std::vector<cv::Mat>& images,std::vector<int>& labels);

        const bool missingSuffix(const std::string& filename) const;
        const QJsonObject predictFace(const QList<QFileInfo>& files,const QFileInfoList::const_iterator& it,const std::string& filename);

        //errors
        const QJsonObject alreadyTrainedDataset(const std::string& identifier) const;
        const QJsonObject trainningDatasetNotFound(const std::string& identifier) const;
        const QJsonObject emptyTrainningDataset(const std::string& identifier) const;
        const QJsonObject trainDatasetSuccessfull(const std::string& identifier) const;
        const QJsonObject modelNotCreatedError(const std::string& identifier) const;

        const QJsonObject predictFaceInvalidInputError(const std::string& name) const;
        const QJsonObject predictFaceNameNotFound(const std::string& name) const;
        const QJsonObject predictionSuccessfull(const int predictedLabel,double confidence,const std::string name,const std::string input) const;
    public: 
        FaceDetect(const char* trainningDataset,const char* testingDataset);
        const QJsonObject trainDataset(const std::string& identifier);
        const QJsonObject predictFace(const std::string& filePath);
};