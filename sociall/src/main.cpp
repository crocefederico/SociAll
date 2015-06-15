// Sets how confident the Face Verification algorithm should be to decide if it is an unknown person or a known person.
// A value roughly around 0.5 seems OK for Eigenfaces or 0.7 for Fisherfaces, but you may want to adjust it for your
// conditions, and if you use a different Face Recognition algorithm.
// Note that a higher threshold value means accepting more faces as known people,
// whereas lower values mean more faces will be classified as "unknown".
const float UNKNOWN_PERSON_THRESHOLD = 0.5f;

// Set the desired face dimensions. Note that "getPreprocessedFace()" will return a square face.
const int faceWidth = 70;
const int faceHeight = faceWidth;

// Cascade Classifier file, used for Face Detection.
const char *faceCascadeFilename = "/var/www/html/sociall/lib/lbpcascade_frontalface.xml";     // LBP face detector.
//const char *faceCascadeFilename = "haarcascade_frontalface_alt_tree.xml";  // Haar face detector.
//const char *eyeCascadeFilename1 = "haarcascade_lefteye_2splits.xml";   // Best eye detector for open-or-closed eyes.
//const char *eyeCascadeFilename2 = "haarcascade_righteye_2splits.xml";   // Best eye detector for open-or-closed eyes.
//const char *eyeCascadeFilename1 = "haarcascade_mcs_lefteye.xml";       // Good eye detector for open-or-closed eyes.
//const char *eyeCascadeFilename2 = "haarcascade_mcs_righteye.xml";       // Good eye detector for open-or-closed eyes.
const char *eyeCascadeFilename1 = "/var/www/html/sociall/lib/haarcascade_eye.xml";               // Basic eye detector for open eyes only.
const char *eyeCascadeFilename2 = "/var/www/html/sociall/lib/haarcascade_eye_tree_eyeglasses.xml"; // Basic eye detector for open eyes if they might wear glasses.

const bool preprocessLeftAndRightSeparately = true;   // Preprocess left & right sides of the face separately, in case there is stronger light on one side.

#include <vector>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

// Include OpenCV's C++ Interface
#include "opencv2/opencv.hpp"

// Include the other headers
#include "/var/www/html/sociall/include/detectObject.h"       // Easily detect faces or eyes (using LBP or Haar Cascades).
#include "/var/www/html/sociall/include/preprocessFace.h"     // Easily preprocess face images, for face recognition.
#include "/var/www/html/sociall/include/recognition.h"     // Train the face recognition system and recognize a person from an image.

#include "/var/www/html/sociall/include/ImageUtils.h"      // Shervin's handy OpenCV utility functions.

using namespace cv;
using namespace std;

//cartella in cui vengono create le cartelle per ogni utente
const string modelsaved="/var/www/html/sociall/modelli";

// C++ conversion functions between integers (or floats) to std::string.
template <typename T> string toString(T t)
{
    ostringstream out;
    out << t;
    return out.str();
}

template <typename T> T fromString(string t)
{
    T out;
    istringstream in(t);
    in >> out;
    return out;
}

// Load the face and 1 or 2 eye detection XML classifiers.
void initDetectors(CascadeClassifier &faceCascade, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2)
{
    // Load the Face Detection cascade classifier xml file.
    try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
        faceCascade.load(faceCascadeFilename);
    } catch (cv::Exception &e) {}
    if ( faceCascade.empty() ) {
        cerr << "ERROR: Could not load Face Detection cascade classifier [" << faceCascadeFilename << "]!" << endl;
        cerr << "Copy the file from your OpenCV data folder (eg: '~/OpenCV/share/OpenCV/lbpcascades') into the folder you are using." << endl;
        exit(1);
    }
    //cout << "Loaded the Face Detection cascade classifier [" << faceCascadeFilename << "]." << endl;

    // Load the Eye Detection cascade classifier xml file.
    try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
        eyeCascade1.load(eyeCascadeFilename1);
    } catch (cv::Exception &e) {}
    if ( eyeCascade1.empty() ) {
        cerr << "ERROR: Could not load 1st Eye Detection cascade classifier [" << eyeCascadeFilename1 << "]!" << endl;
        cerr << "Copy the file from your OpenCV data folder (eg: '~/OpenCV/share/OpenCV/lbpcascades') into the folder you are using.." << endl;
        exit(1);
    }
    //cout << "Loaded the 1st Eye Detection cascade classifier [" << eyeCascadeFilename1 << "]." << endl;

    // Load the Eye Detection cascade classifier xml file.
    try {   // Surround the OpenCV call by a try/catch block so we can give a useful error message!
        eyeCascade2.load(eyeCascadeFilename2);
    } catch (cv::Exception &e) {}
    if ( eyeCascade2.empty() ) {
        cerr << "Could not load 2nd Eye Detection cascade classifier [" << eyeCascadeFilename2 << "]." << endl;
        // Dont exit if the 2nd eye detector did not load, because we have the 1st eye detector at least.
        //exit(1);
    }
    //else
        //cout << "Loaded the 2nd Eye Detection cascade classifier [" << eyeCascadeFilename2 << "]." << endl;
}
//La funzione inserisce dentro il vettore "files" l'elenco dei file e cartelle contenuti nella cartella dir ad eccezione di eventuali cartelle "." e ".."
int getdir (string dir, vector<string> &files){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
    	if((strcmp(dirp->d_name,".")!=0 && strcmp(dirp->d_name,"..")!=0))
        	files.push_back(dir+"/"+string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void trainUsingFile(string folderpath, int username, CascadeClassifier &faceCascade, CascadeClassifier &eyeCascade1, CascadeClassifier &eyeCascade2){
	string directory=modelsaved+toString("/")+toString(username);
	const char* formkdir=directory.c_str();
	int status = mkdir(formkdir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	printf("%s",formkdir);
	if(status==-1){
		cerr<<"ERROR: Couldn't make directory"<<endl;
		exit(1);
	}
    Ptr<BasicFaceRecognizer> model=createEigenFaceRecognizer();
    vector<Mat> preprocessedFaces;
    vector<int> faceLabels;
    vector<string> images;
    //prendo tutti i nomi delle immagini
    getdir(folderpath,images);
    vector<string>::size_type n_images;
    n_images=images.size();

    for(uint i=0;i<n_images;i++){
    	 Mat imageOriginal;
    	 imageOriginal=imread(images[i]);
    	 if(imageOriginal.empty()){
    	 	cerr << "ERROR: Couldn't read the file" << endl;
    	    exit(1);
    	 }

 	    // Get a copy of the camera frame that we can draw onto.
   	    Mat displayedFrame;
    	imageOriginal.copyTo(displayedFrame);
 	    // Find a face and preprocess it to have a standard size and contrast & brightness.
  	    Rect faceRect;  // Position of detected face.
   	    Rect searchedLeftEye, searchedRightEye; // top-left and top-right regions of the face, where eyes were searched.
   	    Point leftEye, rightEye;    // Position of the detected eyes.
   	    Mat preprocessedFace = getPreprocessedFace(displayedFrame, faceWidth, faceCascade, eyeCascade1, eyeCascade2, preprocessLeftAndRightSeparately, &faceRect, &leftEye, &rightEye, &searchedLeftEye, &searchedRightEye);
        bool gotFaceAndEyes = false;
        if (preprocessedFace.data)
            gotFaceAndEyes = true;
        if(gotFaceAndEyes){
        	//aggiungo la foto solo se sono riuscito a trovare entrambi gli occhi e una faccia
        	preprocessedFaces.push_back(preprocessedFace);
           	faceLabels.push_back(username);
        }
    }
    model->train(preprocessedFaces,faceLabels);
    string nomeModello="modelsaved_"+toString(username)+"_.xml";
    string dest=directory+toString("/")+nomeModello;
    model->save(dest);
}

int predictUsingFile(string folderpath,CascadeClassifier faceCascade,CascadeClassifier eyeCascade1,CascadeClassifier eyeCascade2){

	Ptr<BasicFaceRecognizer> model;
	vector<string> folders;
	vector<string> models;
	int identity=-1;

	//riempio con tutte le sottocartelle
	getdir(modelsaved,folders);
	vector<string>::size_type n_folder=folders.size();
	for(uint i=0;i<n_folder;i++){
		getdir(folders[i],models);
	}
	//riempio con i path assoluti per i tutti i modelli salvati
	vector<string>::size_type n_models=models.size();
	for(uint i=0;i<n_models;i++){
		getdir(folders[i],models);
	}

	Mat imageOriginal=imread(folderpath);
	if(imageOriginal.empty()){
		cerr << "ERROR: Couldn't read the file." << endl;
	    exit(1);
	}
	// Get a copy of the camera frame that we can draw onto.
	Mat displayedFrame;
	imageOriginal.copyTo(displayedFrame);

    // Find a face and preprocess it to have a standard size and contrast & brightness.
    Rect faceRect;  // Position of detected face.
    Rect searchedLeftEye, searchedRightEye; // top-left and top-right regions of the face, where eyes were searched.
    Point leftEye, rightEye;    // Position of the detected eyes.
    Mat preprocessedFace = getPreprocessedFace(displayedFrame, faceWidth, faceCascade, eyeCascade1, eyeCascade2, preprocessLeftAndRightSeparately, &faceRect, &leftEye, &rightEye, &searchedLeftEye, &searchedRightEye);
    bool gotFaceAndEyes = false;
    if (preprocessedFace.data)
       gotFaceAndEyes = true;
	Mat reconstructedFace;
    string outputStr="Unknown";
    double similarity=100.0;
    bool trovato=false;

    if(gotFaceAndEyes){
    	for(unsigned int i=0;i<n_models && !trovato;i++){
    		model=createEigenFaceRecognizer();
    		string next=models[i];
    		model->load(next);
    		// Generate a face approximation by back-projecting the eigenvectors & eigenvalues.
    		reconstructedFace = reconstructFace(model, preprocessedFace);
    		// Verify whether the reconstructed face looks like the preprocessed face, otherwise it is probably an unknown person.
    		similarity = getSimilarity(preprocessedFace, reconstructedFace);
    		if(similarity<UNKNOWN_PERSON_THRESHOLD){
    			// Identify who the person is in the preprocessed face image.
    			identity = model->predict(preprocessedFace);
    			outputStr = toString(identity);
    			trovato=true;
    		}
    		model.~Ptr();
    	}
    }
   	// Since the confidence is low, assume it is an unknown person.
    //cout << "Identity: " << "§"<<outputStr<<"§" << ". Similarity: " << similarity << endl;
    cout<<outputStr<<endl;
	if(outputStr.compare("Unknown")==0)
		return -2;
	else
		return atoi(outputStr.c_str());
}
int main(int argc, char *argv[]){

    CascadeClassifier faceCascade;
    CascadeClassifier eyeCascade1;
    CascadeClassifier eyeCascade2;

    if(argc<4){
    	if(argc<2){
    		cout<<"Usage: "<<argv[0]<<" [OPTION]"<<"\n"<<"--train <path-to-image> <name>"<<"\n"<<"--recog <path-to-image>"<<endl;
    		exit(1);
    	}
    	else if(strcmp(argv[1],"--train")==0){
    		cout<<"Usage: "<<argv[0]<<" [OPTION]"<<"\n"<<"--train <path-to-image> <name>"<<"\n"<<"--recog <path-to-image>"<<endl;
    		exit(1);
    	}
    	else if(argc<3){
    		cout<<"Usage: "<<argv[0]<<" [OPTION]"<<"\n"<<"--train <path-to-image> <name>"<<"\n"<<"--recog <path-to-image>"<<endl;
    		exit(1);
    	}
    }
    // Load the face and 1 or 2 eye detection XML classifiers.
    initDetectors(faceCascade, eyeCascade1, eyeCascade2);

    //cout << endl;

    if(strcmp(argv[1],"--train")==0)
    	trainUsingFile(argv[2],atoi(argv[3]),faceCascade,eyeCascade1,eyeCascade2);
    if(strcmp(argv[1],"--recog")==0){
    	int ret= predictUsingFile(argv[2],faceCascade,eyeCascade1,eyeCascade2); //int > 0 (id utente) oppure -2 se Unknown
    }
    return 0;
}
