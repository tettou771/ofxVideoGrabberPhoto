#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundAuto(true);

    vid.setDeviceID(1);
    vid.setup(1280, 720);
    vid.setCaptureTryNum(8);
}

void ofApp::update() {
    if (vid.isInitialized()) {
        vid.update();
    }
}

void ofApp::draw() {
    if (vid.isInitialized()) {
        ofRectangle rect;
        rect.x = 0;
        rect.y = 0;
        rect.width = ofGetWidth() / 3;
        rect.height = rect.width * vid.getHeight() / vid.getWidth();
        vid.draw(rect);
        
        if (vid.isCaptured()) {
            auto mostFine = vid.getPicture();
            
            for (auto p : vid.getPictures()) {
                rect.x += rect.width;
                if (rect.x + rect.width > ofGetWidth()) {
                    rect.x = 0;
                    rect.y += rect.height;
                }
                
                ofSetColor(255);
                p->draw(rect);
                
                if (p == mostFine) {
                    ofPushStyle();
                    ofColor c(0, 200, 0);
                    
                    ofDrawBitmapStringHighlight("Most fine", rect.x + 10, rect.y + 20, ofColor(0, 120), c);

                    ofNoFill();
                    ofSetColor(c);
                    ofSetLineWidth(4);
                    ofDrawRectangle(rect);
                    ofPopStyle();
                }
            }
        } else {
            ofDrawBitmapStringHighlight("Space key to take picture.", 20, rect.height + 30);
        }
    } else {
        ofDrawBitmapStringHighlight("Video is not initialized.\nPlease check video ID in setup().", 20, 30);
    }
}

void ofApp::keyPressed(int key) {
    switch (key){
        case ' ':
            vid.capture();
            break;
    }
}
