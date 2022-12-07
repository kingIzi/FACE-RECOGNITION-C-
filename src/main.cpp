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
    //FaceDetect detect(argv[1],argv[2]);
    // detect.trainDataset();
    // const auto t = detect.predictFace("/home/coco/Documents/c++/projects/vs-code-c++/lbph_face_recognition/testDataset/Scott Izi Kapampa-6.jpg");
    // std::cout << t << std::endl;
    QCoreApplication app(argc,argv);
    RequestHandler requests(argv);
    requests.initialize();
    requests.startListening();
    return app.exec();
}





// static void read_csv(const std::string& filename, std::vector<cv::Mat>& images, std::vector<int>& labels, char separator = ';') {
//     std::ifstream file(filename.c_str(), std::ifstream::in);
//     if (!file) {
//         std::string error_message = "No valid input file was given, please check the given filename.";
//         std::cerr << error_message.c_str() << std::endl;
//         return;
//         //cv::CV_Error(Error::StsBadArg, error_message);
//     }
//     std::string line, path, classlabel;
//     while (std::getline(file, line)) {
//         std::stringstream liness(line);
//         std::getline(liness, path, separator);
//         std::getline(liness, classlabel);
//         std::cout << line << std::endl;
//         if(!path.empty() && !classlabel.empty()) {
//             images.push_back(cv::imread(path, 0));
//             labels.push_back(atoi(classlabel.c_str()));
//         }
//     }
// }

// int main(int argc,char* argv[])
// {
//     std::string dataset = argv[1];
//     std::vector<cv::Mat> images;
//     std::vector<int> labels;
//     // Read in the data. This can fail if no valid
//     // input filename is given.
//     try {
//         read_csv(DATASET_CSV,images,labels);
//     } catch (const cv::Exception& e) {
//         std::cerr << "Error opening file \"" << DATASET_CSV << "\". Reason: " << e.msg << std::endl;
//         // nothing more we can do
//         exit(1);
//     }
//     if(images.size() <= 1) {
//         std::string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
//         std::cerr << error_message.c_str() << std::endl;
//     }
//     cv::Mat testSample = images[images.size() - 1];
//     int testLabel = labels[labels.size() - 1];
//     images.pop_back();
//     labels.pop_back();
//     cv::Ptr<cv::face::LBPHFaceRecognizer> model = cv::face::LBPHFaceRecognizer::create();
//     model->train(images, labels);
//     int predictedLabel = model->predict(testSample);
//     std::string result_message = "Predicted class = " + std::to_string(predictedLabel) + "\n" + "Actual class = " + std::to_string(testLabel); 
//     std::cout << result_message << std::endl;
//     std::cout << "Radius" << model->getRadius() << std::endl;
//     std::cout << "Neighbors" << model->getNeighbors() << std::endl;
//     std::cout << "GridX" << model->getGridX() << std::endl;
//     std::cout << "GridY" << model->getGridY() << std::endl;
//     std::cout << "Threshold" << model->getThreshold() << std::endl;
//     return 0;
// }












// #include "opencv2/core.hpp"
// #include "opencv2/face.hpp"
// #include "opencv2/highgui.hpp"
// #include <iostream>
// #include <fstream>
// #include <sstream>
// using namespace cv;
// using namespace cv::face;
// using namespace std;
// static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
//     std::ifstream file(filename.c_str(), ifstream::in);
//     if (!file) {
//         string error_message = "No valid input file was given, please check the given filename.";
//         CV_Error(Error::StsBadArg, error_message);
//     }
//     string line, path, classlabel;
//     while (getline(file, line)) {
//         stringstream liness(line);
//         getline(liness, path, separator);
//         getline(liness, classlabel);
//         std::cout << line << std::endl;
//         if(!path.empty() && !classlabel.empty()) {
//             images.push_back(imread(path, 0));
//             labels.push_back(atoi(classlabel.c_str()));
//         }
//     }
// }
// int main(int argc, const char *argv[]) {
//     // Check for valid command line arguments, print usage
//     // if no arguments were given.
//     if (argc != 2) {
//         cout << "usage: " << argv[0] << " <csv.ext>" << endl;
//         exit(1);
//     }
//     // Get the path to your CSV.
//     std::cout << argv[1] << std::endl; 
//     string fn_csv = string(argv[1]);
//     // These vectors hold the images and corresponding labels.
//     vector<Mat> images;
//     vector<int> labels;
//     // Read in the data. This can fail if no valid
//     // input filename is given.
//     try {
//         read_csv(fn_csv, images, labels);
//     } catch (const cv::Exception& e) {
//         cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
//         // nothing more we can do
//         exit(1);
//     }
//     // Quit if there are not enough images for this demo.
//     if(images.size() <= 1) {
//         string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
//         CV_Error(Error::StsError, error_message);
//     }
//     // The following lines simply get the last images from
//     // your dataset and remove it from the vector. This is
//     // done, so that the training data (which we learn the
//     // cv::LBPHFaceRecognizer on) and the test data we test
//     // the model with, do not overlap.
//     Mat testSample = images[images.size() - 1];
//     int testLabel = labels[labels.size() - 1];
//     images.pop_back();
//     labels.pop_back();
//     // The following lines create an LBPH model for
//     // face recognition and train it with the images and
//     // labels read from the given CSV file.
//     //
//     // The LBPHFaceRecognizer uses Extended Local Binary Patterns
//     // (it's probably configurable with other operators at a later
//     // point), and has the following default values
//     //
//     //      radius = 1
//     //      neighbors = 8
//     //      grid_x = 8
//     //      grid_y = 8
//     //
//     // So if you want a LBPH FaceRecognizer using a radius of
//     // 2 and 16 neighbors, call the factory method with:
//     //
//     //      cv::face::LBPHFaceRecognizer::create(2, 16);
//     //
//     // And if you want a threshold (e.g. 123.0) call it with its default values:
//     //
//     //      cv::face::LBPHFaceRecognizer::create(1,8,8,8,123.0)
//     //
//     Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
//     model->train(images, labels);
//     // The following line predicts the label of a given
//     // test image:
//     int predictedLabel = model->predict(testSample);
//     //
//     // To get the confidence of a prediction call the model with:
//     //
//     //      int predictedLabel = -1;
//     //      double confidence = 0.0;
//     //      model->predict(testSample, predictedLabel, confidence);
//     //
//     string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
//     cout << result_message << endl;
//     // First we'll use it to set the threshold of the LBPHFaceRecognizer
//     // to 0.0 without retraining the model. This can be useful if
//     // you are evaluating the model:
//     //
//     model->setThreshold(0.0);
//     // Now the threshold of this model is set to 0.0. A prediction
//     // now returns -1, as it's impossible to have a distance below
//     // it
//     predictedLabel = model->predict(testSample);
//     cout << "Predicted class = " << predictedLabel << endl;
//     // Show some informations about the model, as there's no cool
//     // Model data to display as in Eigenfaces/Fisherfaces.
//     // Due to efficiency reasons the LBP images are not stored
//     // within the model:
//     cout << "Model Information:" << endl;
//     string model_info = format("\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
//             model->getRadius(),
//             model->getNeighbors(),
//             model->getGridX(),
//             model->getGridY(),
//             model->getThreshold());
//     cout << model_info << endl;
//     // We could get the histograms for example:
//     vector<Mat> histograms = model->getHistograms();
//     // But should I really visualize it? Probably the length is interesting:
//     cout << "Size of the histograms: " << histograms[0].total() << endl;
//     return 0;
// }