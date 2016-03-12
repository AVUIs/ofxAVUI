//
//  ofxAVUIToggle.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIToggle.h"

ofxAVUIToggle::ofxAVUIToggle(string _title, string _paramBool){
    title = _title;
    param1 = _paramBool;
}

ofxAVUIToggle::~ofxAVUIToggle(){

}

void ofxAVUIToggle::draw(){
    ofPushStyle();
    ofSetColor(bgColor);
//    ofDrawRectangle(0,0,shape.width,shape.height);
    ofDrawRectangle(shape.x,shape.y,shape.width,shape.height);
    ofSetColor(fgColor);
    drawContour();
    drawTitle();
    ofSetColor(fgColor, 196);
    ofEnableAlphaBlending();
    (soundProperties->getBool(param1))? ofFill() : ofNoFill();
//    ofDrawCircle(shape.width/2, shape.height /2, shape.height /4) ;
    ofDrawCircle(shape.x + shape.width/2, shape.y + shape.height /2, shape.height /4) ;
    ofDisableAlphaBlending();
    ofPopStyle();
}

void ofxAVUIToggle::mouseMoved(ofMouseEventArgs & args) {
}

void ofxAVUIToggle::mousePressed(ofMouseEventArgs & args) {
    if (shape.inside(args.x, args.y)) {
        soundProperties->getBool(param1) = !soundProperties->getBool(param1);
    }
}

void ofxAVUIToggle::mouseDragged(ofMouseEventArgs & args) {
}

void ofxAVUIToggle::mouseReleased(ofMouseEventArgs & args) {
}

void ofxAVUIToggle::mouseScrolled(ofMouseEventArgs & args) {
}
