#include "ofApp.h"

void ofApp::setup() {
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
                ofNoFill();
                ofSetColor(0, 200, 0);
                ofSetLineWidth(4);
                ofDrawRectangle(rect);
                ofPopStyle();
            }
        }
        
    }
}

void ofApp::keyPressed(int key) {
    switch (key){
        case ' ':
            vid.capture();
            break;
    }
}
