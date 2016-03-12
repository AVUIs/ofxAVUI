//
//  ofxAVUIXYCanvas.cpp
//  Developed by Berkan Eskikaya
//
//  Part of ofxAVUI addon, developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIXYCanvas.h"

ofxAVUIXYCanvas::ofxAVUIXYCanvas(string _title, string _paramBool2, string _paramBoolTrigger, string _paramBoolToggle, string _paramFloat2)
  : ofxAVUIXYPad(_title,  _paramBool2,  _paramBoolTrigger,  _paramBoolToggle,  _paramFloat2)
{
}

ofxAVUIXYCanvas::ofxAVUIXYCanvas(string _title, string _paramBool2, string _paramBoolTrigger, string _paramBoolToggle, string _paramFloat2, string bgImagePath)
  : ofxAVUIXYPad(_title,  _paramBool2,  _paramBoolTrigger,  _paramBoolToggle,  _paramFloat2)
{
  bgImage.load(bgImagePath);
}

ofxAVUIXYCanvas::~ofxAVUIXYCanvas(){

}

void ofxAVUIXYCanvas::draw(){
  ofxAVUIXYPad::draw();
  
  // TODO: add shape/gesture drawing
  
  ofPushStyle();
  ofSetColor(255,255,255,90);
  if (bgImage.isAllocated()) {
    bgImage.draw(0,0,shape.width, shape.height);
  }
  
  ofPopStyle();  

}

void ofxAVUIXYCanvas::mouseMoved(ofMouseEventArgs & args) {
  ofxAVUIXYPad::mouseMoved(args);
}

void ofxAVUIXYCanvas::mousePressed(ofMouseEventArgs & args) {
    ofxAVUIXYPad::mousePressed(args);
}

void ofxAVUIXYCanvas::mouseDragged(ofMouseEventArgs & args) {
  ofxAVUIXYPad::mouseDragged(args);
}

void ofxAVUIXYCanvas::mouseReleased(ofMouseEventArgs & args) {
  ofxAVUIXYPad::mouseReleased(args);
}

void ofxAVUIXYCanvas::mouseScrolled(ofMouseEventArgs & args) {
  ofxAVUIXYPad::mouseScrolled(args);
}
