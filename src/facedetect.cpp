#include <algorithm>
#include <list>
#include <iterator>

#include <QtCore/QDir>
#include <QtConcurrent/QtConcurrent>
#include <QtCore/QDirIterator>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include "facedetect.hpp"

//constructor
FaceDetect::FaceDetect(const char* trainningDataset,const char* testingDataset) : 
    trainData(trainningDataset),
    testData(testingDataset),
    model(cv::face::LBPHFaceRecognizer::create(4, 8, 8, 8, 5000))
{
    if (QFileInfo::exists(RECOGNITION_MODEL)){
        this->model->read(RECOGNITION_MODEL);
    }
    else if (!this->trainData.exists() || !this->testData.exists()){
        throw std::invalid_argument("Une erreur c'est produite. Le Train dataset or test dataset est vide.");
    }
}

//read dataset.txt and append images as cv::Mat and labels as int[]
void FaceDetect::read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator)
{
    QFile file(filename.c_str());
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while (!in.atEnd()){
            const auto list = ((QString)in.readLine()).split(separator);
            images.emplace_back(cv::imread(list.first().toStdString(),0));
            labels.emplace_back(std::atoi(list.back().toStdString().c_str()));
        }
        file.close();
    }
}

//read dataset.txt and return filesnames as string list
void FaceDetect::read_csv_as_filenames(const std::string& filename, std::vector<std::string>& images, std::vector<int>& labels, char separator)
{
    QFile file(filename.c_str());
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while (!in.atEnd()){
            const auto list = ((QString)in.readLine()).split(separator);
            images.emplace_back(list.first().toStdString(),0);
            labels.emplace_back(std::atoi(list.back().toStdString().c_str()));
        }
        file.close();
    }
}

//append path and label to dataset.txt
void FaceDetect::appendTrainnedModelNames(const std::string& name,const int& classLabel) const
{
    QFile file(DATASET_CSV);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)){
        QTextStream out(&file);
        out << name.c_str() << ";" << classLabel << "\n";
        file.close();
    }
}

//get list of ready trained datasets
const QList<QString> FaceDetect::getDirNamesList(char separator) const
{
    QList<QString> dirNames;
    QFile file(DATASET_CSV);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while (!in.atEnd()){
            const auto list = ((QString)in.readLine()).split(separator);
            QDir dir(list.first());
            dir.cdUp();
            dirNames.emplace_back(dir.dirName());
        }
        file.close();
    }
    return dirNames;
}

//error response when dataset has already been trained
const QJsonObject FaceDetect::alreadyTrainedDataset(const std::string& identifier) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("error","Identifiant reconnu dans la base de donn??es");
    response.insert("message","Vous devez ins??rer un nouvel identifiant pour un apprentissage valide");
    response.insert("input",identifier.c_str());
    return response;
}

//error when trainning dataset is not found
const QJsonObject FaceDetect::trainningDatasetNotFound(const std::string& identifier) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("error","Aucun ensemble de donn??es trouv?? pour l'entra??nement");
    response.insert("message","Veuillez vous assurer qu'un identifiant valide est transmis pour un apprentissage valide");
    response.insert("input",identifier.c_str());
    return response;
}

//error when dataset is empty
const QJsonObject FaceDetect::emptyTrainningDataset(const std::string& identifier) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("error","Impossible d'entra??ner l'ensemble de donn??es car le dossier est vide.");
    response.insert("message","Veuillez vous assurer que l'ensemble de donn??es contient au moins 10 images");
    response.insert("input",identifier.c_str());
    return response;
}

//response when trainning successfull
const QJsonObject FaceDetect::trainDatasetSuccessfull(const std::string& identifier) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("error","L'entrainement a ??tait lancer en succes");
    response.insert("message","L'apprentissage a commenc?? et l'identifiant sera bient??t disponible pour la reconnaissance faciale");
    response.insert("input",identifier.c_str());
    return response;
}

//face detect thread
void FaceDetect::startTrainning(const std::vector<cv::Mat>& images,const std::vector<int>& labels)
{
    qDebug() << "Started Trainning...";
    if (!QFileInfo::exists(RECOGNITION_MODEL)){
        this->model->train(images, labels);
        this->model->save(RECOGNITION_MODEL);
    }
    else{
        this->model->update(images, labels);
        this->model->save(RECOGNITION_MODEL);
    }
    qDebug() << "Saving model please wait...";
    const short SECONDS = 10000;
    std::this_thread::sleep_for(std::chrono::milliseconds(SECONDS));
    qDebug() << "Trainning finished!!!";
    this->images.clear();
    this->labels.clear();
}

//start trainning data stored in dataset.txt in new tread
const QJsonObject FaceDetect::startTrainning(const QList<QFileInfo>& files,const std::string& identifier,const int indexOf,std::vector<cv::Mat>& images,std::vector<int>& labels)
{
    for (const auto& file : files){
        const auto filePath = file.absoluteFilePath().toStdString();
        this->appendTrainnedModelNames(filePath,indexOf);
    }
    this->read_csv(DATASET_CSV,images,labels);
    const auto future = QtConcurrent::run([images,labels,this]() {
        this->startTrainning(images,labels);
    });
    return this->trainDatasetSuccessfull(identifier);
}

const QJsonObject FaceDetect::trainDataset(const QList<QFileInfo>& directories,const QFileInfoList::const_iterator& it,const std::string& identifier)
{
    if (it != directories.end()){
        const auto distance = std::distance(directories.begin() , it);
        const auto file = directories[distance];
        this->trainData.cd(file.fileName());
        const auto files = this->trainData.entryInfoList(QStringList() << "*.jpg" << "*.png" << "*.jpeg",QDir::Files,QDir::Name);
        this->trainData.cdUp();
        if (files.isEmpty()){
            return this->emptyTrainningDataset(identifier);
        }
        const auto indexOf = directories.indexOf(file);
        // std::vector<cv::Mat> images; images.reserve(files.size());
        // std::vector<int> labels; labels.reserve(files.size());
        this->images.reserve(files.size()); 
        this->labels.reserve(files.size());
        return this->startTrainning(files,identifier,indexOf,images,labels);
    }
    return this->trainningDatasetNotFound(identifier);
}

//train dataset endpoint
const QJsonObject FaceDetect::trainDataset(const std::string& identifier)
{
    const auto names = this->getDirNamesList();
    if (names.contains(identifier.c_str())){
        return this->alreadyTrainedDataset(identifier);
    }
    const auto directories = this->trainData.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoDot);
    const auto it = std::find_if(directories.begin(),directories.end(),[identifier](const QFileInfo& dir){
        return identifier == dir.fileName().toStdString();
    });
    return this->trainDataset(directories,it,identifier);
}

//predict dataset error
const QJsonObject FaceDetect::predictFaceInvalidInputError(const std::string& name) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("input",name.c_str());
    response.insert("message","Le nom de fichier fourni ne correspond ?? aucun suffixe *.png, *.jpg, *.jpeg, *.pgm");
    response.insert("error","Veuillez envoyer le nom du fichier avec le suffixe");
    return response;    
}

//predict error identifier is unknown
const QJsonObject FaceDetect::predictFaceNameNotFound(const std::string& name) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("input",name.c_str());
    response.insert("message","Veuillez vous assurer que le fichier que vous avez envoy?? est pr??sent dans le dossier de test");
    response.insert("error","Ce fichier n'existe pas dans le dossier de test");
    return response;    
}

//response for successful predicton for known or unknown identifiers
const QJsonObject FaceDetect::predictionSuccessfull(const int predictedLabel,double confidence,const std::string name,const std::string input) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("input",input.c_str());
    response.insert("found",name.c_str());
    response.insert("predictedClassLabel",predictedLabel);
    response.insert("confidence",confidence);
    return response;    
}

//error response when model has not yet been trained
const QJsonObject FaceDetect::modelNotCreatedError(const std::string& identifier) const
{
    QJsonObject response;
    response.insert("code",200);
    response.insert("input",identifier.c_str());
    response.insert("message","Cet identifiant n'a pas ??t?? con??u pour l'apprentissage");
    response.insert("error","Pas de formation trouv??e pour la reconnaissance faciale");
    return response;    
}

//predict the identifier
const std::tuple<int,double,std::string> FaceDetect::makePrediction(const std::string& filePath)
{
    const auto frame = cv::imread(filePath,0);
    int predictedLabel = -1;
    double confidence = 0.0;
    const short C = 50; //confidence must be less than this for a matched recognition label
    this->model->predict(frame, predictedLabel, confidence);
    if (predictedLabel != -1 && confidence < C){
        const auto name = this->findNameByClassLabel(predictedLabel);
        return std::make_tuple(predictedLabel,confidence,name);
    }
    else{
        return std::make_tuple(predictedLabel,confidence,"Inconnue");
    }
}

const QJsonObject FaceDetect::predictFace(const QList<QFileInfo>& files,const QFileInfoList::const_iterator& it,const std::string& filename)
{
    if (!QFileInfo::exists(RECOGNITION_MODEL)){
        return this->modelNotCreatedError(filename);
    }
    else if (it != files.end()){
        const auto predict = this->makePrediction(it->absoluteFilePath().toStdString()); //predicted label,confidence, found
        return this->predictionSuccessfull(std::get<0>(predict),std::get<1>(predict),std::get<2>(predict),filename);
    }
    else{
        return this->predictFaceNameNotFound(filename);
    }
}

const bool FaceDetect::missingSuffix(const std::string& filename) const
{
    const auto isPng = filename.substr(filename.find_last_of(".") + 1) == "png";
    const auto isJpg = filename.substr(filename.find_last_of(".") + 1) == "jpg";
    const auto isJpeg = filename.substr(filename.find_last_of(".") + 1) == "jpeg";
    const auto isPgm = filename.substr(filename.find_last_of(".") + 1) == "pgm";
    return !(isPng || isJpg || isJpeg || isPgm);
}

//predict face endpoint
const QJsonObject FaceDetect::predictFace(const std::string& filename)
{
    if (this->missingSuffix(filename)){
        return this->predictFaceInvalidInputError(filename);
    }
    const auto files = this->testData.entryInfoList(QDir::NoDot | QDir::NoDotDot | QDir::Files);
    const auto it = std::find_if(files.begin(),files.end(),[filename](const QFileInfo& file){
        return filename == file.fileName().toStdString();
    });
    return this->predictFace(files,it,filename);
}

//get list of class labels and return label at given index
const std::string FaceDetect::findNameByClassLabel(int& predictedLabel)
{
    std::vector<std::string> images;
    std::vector<int> labels;
    this->read_csv_as_filenames(DATASET_CSV,images,labels);
    const auto it = std::find(labels.begin(),labels.end(),predictedLabel);
    if (it != labels.end()){
        const auto image = images[it - labels.begin()];
        const QFileInfo info(image.c_str());
        const QDir dir(info.absolutePath());
        return dir.dirName().toStdString();        
    }
    else{
        return "Inconnue";
    }
}


