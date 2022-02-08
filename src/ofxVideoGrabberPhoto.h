#pragma once
#include "ofMain.h"

class ofxVideoGrabberPhoto : public ofVideoGrabber {
public:
    ofxVideoGrabberPhoto();
    ~ofxVideoGrabberPhoto();
    
    void update() override;
    
    // exec capture
    void capture();
    
    // get most fine picture
    // return null if it doesn't have picture
    ofImage *getPicture();
    
    void clear();
    
    void clearPicturesWithoutMostFinePicture();
    
    // get all captured
    vector<ofImage*> &getPictures();
    
    void setCaptureTryNum(int num);
    int getCaptureTryNum();
    
    bool isCaptured();
    
private:
    int tryNum = 8; // minimum num is 1
    
    vector<ofImage *> pictures;
    ofImage *mostFinePicture = nullptr;
    
    bool capturing = false;
    
    // exec choice algorithm
    void execChoiceAlgorithm();
};
