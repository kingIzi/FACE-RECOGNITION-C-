#include <algorithm>
#include <list>
#include <iterator>

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtConcurrent/QtConcurrent>
#include <QtCore/QDirIterator>
#include <QtCore/QFile>

#include "facedetect.hpp"


FaceDetect::FaceDetect(const char* trainningDataset,const char* testingDataset) : 
    trainningDataset(trainningDataset),
    testingDataset(testingDataset),
    model(cv::face::LBPHFaceRecognizer::create())
{
    if (QFileInfo::exists(RECOGNITION_MODEL)){
        this->model->read(RECOGNITION_MODEL);
    }
}

void FaceDetect::read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator)
{
    std::ifstream file(filename.c_str(), std::ifstream::in);
    if (!file) {
        std::string error_message = "No valid input file was given, please check the given filename.";
        std::cerr << error_message.c_str() << std::endl;
        return;
    }
    std::string line, path, classlabel;
    while (std::getline(file, line)) {
        std::stringstream liness(line);
        std::getline(liness, path, separator);
        std::getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(cv::imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void FaceDetect::read_csv_as_filenames(const std::string& filename, std::vector<std::string>& images, std::vector<int>& labels, char separator)
{
    std::ifstream file(filename.c_str(), std::ifstream::in);
    if (!file) {
        std::string error_message = "No valid input file was given, please check the given filename.";
        std::cerr << error_message.c_str() << std::endl;
        return;
    }
    std::string line, path, classlabel;
    while (std::getline(file, line)) {
        std::stringstream liness(line);
        std::getline(liness, path, separator);
        std::getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(path);
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

void FaceDetect::appendTrainnedModelNames(const std::string& name,const int& classLabel) const
{
    std::ofstream outfile(DATASET_CSV,std::ios_base::app);
    outfile << name  << ";" << classLabel << std::endl;
    outfile.close();
}

QJsonObject FaceDetect::trainDataset(const std::string& identifier)
{
    QJsonObject response;
    QDir directory(this->trainningDataset.c_str());
    directory.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    auto directories = directory.entryInfoList();
    std::sort(directories.begin(),directories.end(),[](const QFileInfo& a,const QFileInfo& b){
        return a.fileName().compare(b.fileName()) == 0;
    });
    const auto it = std::find_if(directories.begin(),directories.end(),[identifier](const QFileInfo& dir){
        return identifier == dir.fileName().toStdString();
    });
    if (it != directories.end()){
        const auto distance = std::distance(directories.begin() , it);
        const auto dir = directories[distance];
        directory.cd(dir.fileName());
        const auto files = directory.entryInfoList(QStringList() << "*.jpg" << "*.png" << "*.jpeg",QDir::Files,QDir::Name);
        if (files.empty()) {
            response.insert("Error","Could not train dataset because folder is empty.");
            response.insert("file",identifier.c_str());
        }
        else{
            const auto indexOf = directories.indexOf(dir);
            std::vector<cv::Mat> images; images.reserve(files.size());
            std::vector<int> labels; labels.reserve(files.size());
            for (const auto& file : files){
                const auto filePath = file.absoluteFilePath().toStdString();
                this->appendTrainnedModelNames(filePath,indexOf);
            }
            this->read_csv(DATASET_CSV,images,labels);
            const auto future = QtConcurrent::run([images,labels,this](){
                std::cout << "Started Trainning..." << std::endl;
                this->model->train(images, labels);
                this->model->save(RECOGNITION_MODEL);
                //cv::waitKey(1000);
                std::cout << "Trainning finished!!!" << std::endl;
            });
            response.insert("success","L'entrainement a était lancer en succes");
            response.insert("file",identifier.c_str());
        }
    }
    else{
        response.insert("Error","Ce dossier n'a pas était retrouver");
        response.insert("file",identifier.c_str());
    }
    return response;
}

const QJsonObject FaceDetect::predictFace(const std::string& filename)
{
    QDir dir(this->testingDataset.c_str());
    const auto files = dir.entryInfoList(QDir::Files);
    const auto it = std::find_if(files.begin(),files.end(),[filename](const QFileInfo& file){
        return filename == file.fileName().toStdString();
        // return filename.compare(file.fileName().toStdString());
    });
    std::cout << "Test filename: " << it->absoluteFilePath().toStdString() << std::endl;
    QJsonObject response;
    if (it != files.end()){
        std::vector<cv::Mat> images;
        std::vector<int> labels;
        try
        {
            const auto frame = cv::imread(it->absoluteFilePath().toStdString(), 0);
            int predictedLabel = this->model->predict(frame);
            if (predictedLabel != -1){
                std::cout << predictedLabel << std::endl;
                const auto name = this->findNameByClassLabel(predictedLabel);
                std::cout << "Predicted Label: " << predictedLabel << std::endl;
                std::cout << "Class Name: " << name << std::endl;
                response.insert("found",name.c_str());
                return response;
            }
            else {
                response.insert("found","Uknown");
                return response;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            response.insert("found","Uknown");
            return response;
        }
        catch(const cv::Exception& e)
        {
            std::cerr << e.what() << '\n';
            response.insert("found","Uknown");
            return response;
        }
    }
    else{
        response.insert("Error","Ce fichier n'a pas pu etre retrouvé...");
        return response;
    }
}

const std::string FaceDetect::findNameByClassLabel(int& predictedLabel)
{
    std::vector<std::string> images;
    std::vector<int> labels;
    try {
        this->read_csv_as_filenames(DATASET_CSV,images,labels);
    } catch (const cv::Exception& e) {
        std::cerr << "Error opening file \"" << DATASET_CSV << "\". Reason: " << e.msg << std::endl;
        exit(1);
    }
    const auto it = std::find(labels.begin(),labels.end(),predictedLabel);
    if (it != labels.end()){
        const auto image = images[it - labels.begin()];
        const QFileInfo info(image.c_str());
        return info.fileName().toStdString();
    }
    else{
        return "Unknown";
    }
}


// const std::string FaceDetect::predictFace(const std::string& filename)
// {
//     QDir dir(this->testingDataset.c_str());
//     const auto files = dir.entryInfoList(QDir::Files);
//     const auto it = std::find_if(files.begin(),files.end(),[filename](const QFileInfo& file){
//         return filename.compare(file.fileName().toStdString()) == true;
//     });
//     if (it != files.end()){
//         std::vector<cv::Mat> images;
//         std::vector<int> labels;
//         try
//         {
//             cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
//             model->read(RECOGNITION_MODEL);
//             const auto frame = cv::imread(it->absoluteFilePath().toStdString(), 0);
//             int predictedLabel = model->predict(frame);
//             if (predictedLabel != -1){
//                 return this->findNameByClassLabel(predictedLabel);
//             }
//             else {
//                 return "Unknown";
//             }
//         }
//         catch(const std::exception& e)
//         {
//             std::cerr << e.what() << '\n';
//             return "Unknown";
//         }
//         catch(const cv::Exception& e)
//         {
//             std::cerr << e.what() << '\n';
//             return "Unknown";
//         }
//     }
//     else{
//         return "File not found";
//     }
// }

