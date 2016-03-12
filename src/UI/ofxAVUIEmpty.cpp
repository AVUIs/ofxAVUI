//
//  ofxAVUIEmpty.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIEmpty.h"

ofxAVUIEmpty::ofxAVUIEmpty(string _title){
    title = _title;
}

ofxAVUIEmpty::~ofxAVUIEmpty(){

}

void ofxAVUIEmpty::draw(){
    ofPushStyle();
    ofSetColor(bgColor);
//    ofDrawRectangle(0,0,shape.width,shape.height);
    ofDrawRectangle(shape.x,shape.y,shape.width,shape.height);
    ofSetColor(fgColor);
    drawTitle();
    ofPopStyle();
}

void ofxAVUIEmpty::mouseMoved(ofMouseEventArgs & args) {
}

void ofxAVUIEmpty::mousePressed(ofMouseEventArgs & args) {
}

void ofxAVUIEmpty::mouseDragged(ofMouseEventArgs & args) {
}

void ofxAVUIEmpty::mouseReleased(ofMouseEventArgs & args) {
}

void ofxAVUIEmpty::mouseScrolled(ofMouseEventArgs & args) {
}
