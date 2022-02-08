#include "ofxVideoGrabberPhoto.h"

ofxVideoGrabberPhoto::ofxVideoGrabberPhoto(){
    //ofVideoGrabber();
}

ofxVideoGrabberPhoto::~ofxVideoGrabberPhoto(){
}

void ofxVideoGrabberPhoto::update() {
    ofVideoGrabber::update();
    
    if (capturing && isFrameNew()) {
        if (pictures.size() < tryNum) {
            auto picture = new ofImage();
            picture->allocate(getWidth(), getHeight(), OF_IMAGE_COLOR);
            picture->getPixels() = getPixels();
            picture->update();
            pictures.push_back(picture);
            
            if (pictures.size() >= tryNum) {
                capturing = false;
                execChoiceAlgorithm();
            }
        }
    }
}

void ofxVideoGrabberPhoto::capture() {
    clear();
    capturing = true;
}

ofImage *ofxVideoGrabberPhoto::getPicture(){
    return mostFinePicture;
}

vector<ofImage*> &ofxVideoGrabberPhoto::getPictures() {
    return pictures;
}

void ofxVideoGrabberPhoto::clear(){
    for (auto p : pictures) {
        p->clear();
        delete p;
    }
    pictures.clear();
    capturing = false;
    mostFinePicture = nullptr;
}

void ofxVideoGrabberPhoto::clearPicturesWithoutMostFinePicture() {
    if (mostFinePicture == nullptr) {
        clear();
        return;
    }
    
    for (auto p : pictures) {
        if (p != mostFinePicture) delete p;
    }
    pictures.clear();
    pictures.push_back(mostFinePicture);
}


void ofxVideoGrabberPhoto::setCaptureTryNum(int num){
    tryNum = MAX(num, 1);
}

int ofxVideoGrabberPhoto::getCaptureTryNum() {
    return tryNum;
}

void ofxVideoGrabberPhoto::execChoiceAlgorithm() {
    // if there is no picture, return;
    if (pictures.empty()) return;
    
    // if it has only a picture, choice it
    if (pictures.size() == 1) {
        mostFinePicture = pictures.front();
        return;
    }

    int i = 0;
    double pastFinnessScore = 0;
    int finestIndex = -1;
    for (auto pic : pictures) {
        double score = 0;
        ofPixels pix = pic->getPixels();
        
        auto sq = [](double x) {
            return x * x;
        };
        
        auto colorDistSquared = [=](ofColor a, ofColor b) {
            return (sq(a.r - b.r) + sq(a.g - b.g) + sq(a.b - b.b)) / 3. / 255. / 255.;
        };
        
        int skip = 4;
        for (int ix = 0; ix < pic->getWidth() - 1; ix += skip) {
            for (int iy = 0; iy < pic->getHeight() - 1; iy += skip) {
                double d = colorDistSquared(pix.getColor(ix, iy), pix.getColor(ix+1, iy));
                + colorDistSquared(pix.getColor(ix, iy), pix.getColor(ix, iy+1));
                score += d;
                //if (d > 0.1) score++;
            }
        }

        //ofLog() << i << " " << score;

        if (score > pastFinnessScore) {
            mostFinePicture = pic;
            pastFinnessScore = score;
            finestIndex = i;
        }
        ++i;
    }
    
    //ofLog() << "Finest is " << finestIndex << " " << pastFinnessScore;
}

bool ofxVideoGrabberPhoto::isCaptured() {
    bool !capturing && mostFinePicture;
}
