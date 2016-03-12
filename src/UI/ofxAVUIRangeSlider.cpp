//
//  ofxAVUIRangeSlider.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIRangeSlider.h"

ofxAVUIRangeSlider::ofxAVUIRangeSlider(string _title, string _paramFloat1, string _paramFloat2){
    x1 = 0;
    x2 = 1;
    dragging = false;
    title = _title;
    param1 = _paramFloat1;
    param2 = _paramFloat2;
}

ofxAVUIRangeSlider::~ofxAVUIRangeSlider(){

}

void ofxAVUIRangeSlider::setPosition(int _x, int _y, int _width, int _height) {
    shape.x = _x;
    shape.y = _y;
    shape.width = _width;
    shape.height = _height;
    x1 = 0;
    x2 = 1.0;
}

void ofxAVUIRangeSlider::update() {
    ofParameter<float>  p1 = soundProperties->getFloat(param1);
    ofParameter<float>  p2 = soundProperties->getFloat(param2);
    float horizVal1 = ofMap(p1, p1.getMin(), p1.getMax(), shape.x, shape.x + shape.width);
    float horizVal2 = ofMap(p2, p2.getMin(), p2.getMax(), shape.x, shape.x + shape.width);
    x1 = horizVal1;
    x2 = horizVal2;
    synced = true;
}

void ofxAVUIRangeSlider::draw(){
    if (synced) update();
    ofPushStyle();
    ofSetColor(bgColor);
    ofDrawRectangle(0,0,shape.width,shape.height);
    ofSetColor(fgColor);
    ofNoFill();
    drawContour();
    drawTitle();
    ofFill();
    ofSetColor(fgColor, 196);
    ofDrawRectangle(x1-shape.x, 0, x2-x1, shape.height);  //cursor
    ofPopStyle();
}

void ofxAVUIRangeSlider::mouseMoved(ofMouseEventArgs & args) {
}

void ofxAVUIRangeSlider::mousePressed(ofMouseEventArgs & args) {
    if (shape.inside(args.x, args.y)) {
        if (abs(x1-args.x) < abs(x2-args.x)) { //lower limit
            x1 = args.x;
            ofParameter<float>  p1 = soundProperties->getFloat(param1);
            float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, p1.getMin(), p1.getMax());
            p1 = horizVal;
        } else {    //higher limit
            x2 = args.x;
            ofParameter<float>  p2 = soundProperties->getFloat(param2);
            float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, p2.getMin(), p2.getMax());
            p2 = horizVal;
        }
        dragging = false;
    }
}

void ofxAVUIRangeSlider::mouseDragged(ofMouseEventArgs & args) {
    if (shape.inside(args.x, args.y)) {
        dragging = true;
        if (abs(x1-args.x) < abs(x2-args.x)) { //lower limit
            x1 = args.x;
            ofParameter<float>  p1 = soundProperties->getFloat(param1);
            float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, p1.getMin(), p1.getMax());
            p1 = horizVal;
        } else {    //higher limit
            x2 = args.x;
            ofParameter<float>  p2 = soundProperties->getFloat(param2);
            float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, p2.getMin(), p2.getMax());
            p2 = horizVal;
        }
    }
}

void ofxAVUIRangeSlider::mouseReleased(ofMouseEventArgs & args) {
    if (shape.inside(args.x, args.y)) {
        if (abs(x1-args.x) < abs(x2-args.x)) { //lower limit
            x1 = args.x;
            ofParameter<float>  p1 = soundProperties->getFloat(param1);
            float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, p1.getMin(), p1.getMax());
            p1 = horizVal;
        } else {    //higher limit
            x2 = args.x;
            ofParameter<float>  p2 = soundProperties->getFloat(param2);
            float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, p2.getMin(), p2.getMax());
            p2 = horizVal;
        }
        dragging = false;
    }
}

void ofxAVUIRangeSlider::mouseScrolled(ofMouseEventArgs & args) {
}
