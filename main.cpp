#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include<string>
using namespace std;
using namespace cv;


class FaceDetector {    // FaceDetector class to detect faces in a webcam stream or image
private:
    CascadeClassifier faceDetector; // Cascade Classifier Class from OpenCV
public:
    FaceDetector(string classifier_location) // Constructor to load Specific CLassifier
    {
        faceDetector.load(classifier_location); 
    }

    void detectFaces(Mat &frame, vector<Rect> &faces) { // function to detect faces in a frame
        // detectMultiScale function to detect faces
        faceDetector.detectMultiScale(frame, faces, 1.1, 4, CASCADE_SCALE_IMAGE, Size(30, 30));
    }
    void draw(Mat &frame , vector<Rect> &faces){  // function to draw rectangles around the detected faces
        for (int i = 0; i < faces.size(); i++) {
            Mat faceROI = frame(faces[i]);
            int x = faces[i].x;
            int y = faces[i].y;
            int h = y + faces[i].height;
            int w = x + faces[i].width;
            rectangle(frame, Point(x, y), Point(w, h), Scalar(255, 0, 255), 2, 8, 0);
            }
    }
   
};
// function to display webcam stream and detect faces in real-time
void WebCam(){
    VideoCapture real_time(0); //using OpenCV HighGUI to use WebCam
    namedWindow("Face Detection"); 
    FaceDetector faceDetector("haarcascade_frontalface_alt.xml"); //Making Object of Class FaceDetector
    Mat frame;  // Defining Matrix From OpenCV Library
    vector<Rect> faces; //Defining Rectangle Class Vector using OpenCV Library
    while (true) {
        real_time.read(frame);  // Reading Frames Matrix From WebCam in RealTime.
        faceDetector.detectFaces(frame, faces); //For Detecting Faces from Matrix and managing Faces Data
        faceDetector.draw(frame,faces);         // For Drawing Rectangles on Spotted Faces
        imshow("Face Detection", frame);    //Showing Live WebCam Video 
        char c = (char)waitKey(10);         // Waiting 10 milliseconds to get next frames 
        if (c == 27 || c=='q'||c=='Q') {    //Break Condition Once Q is Pressed.
            break;
        }
    }
    destroyWindow("Face Detection");    // Destroying WebCam Streaming Window 
    
}

// function to detect faces in an image
void PicDetect(string location){
    Mat image;
    FaceDetector face_detect("haarcascade_frontalface_alt.xml");// object decleared for picture Detecting
    vector <Rect> faces;        
    char d;
    while (1){  // loop to read image until a valid image is loaded
        image= imread(location);
        if(!image.empty()|| location=="n"||location=="N"){
            break;
        }
        cout<<"Please Enter location again or type N to exit";
        cin>>location;
        
    }
    if(image.empty()){ // To Check if image is loaded before image processing
        cout<<"You Didn't Load Any image \n";
    }
    else{
        face_detect.detectFaces(image, faces);      //Giving image Matrix to Detect Face 
        face_detect.draw(image,faces);              // For Drawing Inserting Faces Detected and Image Matrix
        string name= "Image";           
        namedWindow(name);      
        imshow(name,image);                 // Showing Image of UI by using HighGUI of OpenCV
        waitKey(0);                         // Wait Command for Any Key 
        destroyWindow(name);                // Destroying Image Viewer 
        system("cls");                      // Clearing Screen 
        cout<<"Do You Want to Save That Image (Y/N)  :";
        cin>>d;
        if(d=='y'||d=='Y'){
            cout<<"Type the Location for saving file \n ";
            cout<<"If you want to save it in same folder just type name.format of image :";
            cin>>location;
            bool test = imwrite(location,image);        // OpenCV library imwrite to Save image 
            if(!test){                                  // Condition to Check if File is saved or not
                cout<<"File saving Failed \n";  
                system("pause");                        // System Pause Command to wait for user to see the message
            }
        }
    }

}



int main() {
    char a;
    string location;
    while(1){           // Infinite Loop for multiple Runs
        system("color 5e"); //To change CMD Color 
        system("cls"); // clear screen after every iteration. 
        cout<<"Choose following options to start the program: "<<endl;
        cout<<"\tType 1 for starting the Webcam For Face Detection. "<<endl;
        cout<<"\tType 2 for Detecting face from an Image. "<<endl;
        cout<<"\tType 3 for Exiting the Program. "<<endl;
        cin>>a;         // It will Take Input for Required Option. 
        if(a=='1'||a=='2'||a=='3')          //Condition to check if User has Typed Correct Options.
        {
        switch (a)
        {
            case '1':
                system("color a");// changing color to green text
                WebCam();
                break;
            case '2':
                system("color 30"); // changing the color again.
                cout<<"Please Type in Location \n\tIf it is in same Folder then just type name.format :";
                cin>>location;      // getting location
                PicDetect(location);
                break;
            case '3':
                system("cls");
                exit (1);
                break;        
            default:
                break;
           }
           }
        else{
            cout<<"Wrong Input...U had Three Choices 1,2,3. "<<endl;
            system("pause");
           }
    }
    
}

