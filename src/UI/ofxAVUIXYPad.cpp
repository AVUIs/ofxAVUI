//
//  ofxAVUIXYPad.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIXYPad.h"

ofxAVUIXYPad::ofxAVUIXYPad(string _title, string _paramBoolTrigger, string _paramBoolToggle, string _paramFloat1, string _paramFloat2){
    location.x=0;
    location.y=0;
    dragging = false;
    doubleClickTimer = 0;
    clicking = false;
    title = _title;
    paramX = _paramFloat1;
    paramY = _paramFloat2;
    paramBoolTrigger = _paramBoolTrigger;
    paramBoolToggle = _paramBoolToggle;
    
    ofAddListener(sequencerEvents.sequencerEvent, this, &ofxAVUIXYPad::sequencerListener);       //receive Sequencer events
}

ofxAVUIXYPad::~ofxAVUIXYPad(){

}

void ofxAVUIXYPad::setPosition(int _x, int _y, int _width, int _height) {
    shape.x = _x;
    shape.y = _y;
    shape.width = _width;
    shape.height = _height;
    location.x = _x + _width/2;
    location.y = _y + _height/2;
    
    sequencerEvents.addRestrictionRect(ofRectangle(shape.x, shape.y, shape.width, shape.height));    //needed so sequencer can register events in this UI shape
}

void ofxAVUIXYPad::update(){
    ofParameter<float>  px = soundProperties->getFloat(paramX);
    ofParameter<float>  py = soundProperties->getFloat(paramY);
    float horizVal = ofMap(px, px.getMin(), px.getMax(), shape.x, shape.x + shape.width, true);
    float vertVal = ofMap(py,  py.getMin(), py.getMax(), shape.y, shape.y + shape.height, true);
    location.x = horizVal;
    location.y = vertVal;

    synced = true;
}
void ofxAVUIXYPad::draw(){
//this is here so we dont need to call update() every cycle
//    if (clicking && (ofGetElapsedTimeMillis() - doubleClickTimer > DOUBLECLICK_MILLIS)) {
//        location.x = mouseArgs.x;
//        location.y = mouseArgs.y;
//        ofParameter<float>  px = soundProperties->getFloat(paramX);
//        ofParameter<float>  py = soundProperties->getFloat(paramY);
//        float horizVal = ofMap(location.x, shape.x, shape.x + shape.width, px.getMin(), px.getMax());
//        float vertVal = ofMap(location.y, shape.y, shape.y + shape.height, py.getMin(), py.getMax());
//        px = horizVal;
//        py = vertVal;
//        clicking = false;
//    }
    if (synced) update();
    ofPushStyle();
    ofSetColor(bgColor);
//    ofDrawRectangle(0,0,shape.width,shape.height);
    ofDrawRectangle(shape.x,shape.y,shape.width,shape.height);
    ofSetColor(fgColor);
    ofNoFill();
    drawContour();
    drawTitle();
//    ofDrawLine(location.x-shape.x-5, location.y-shape.y, location.x-shape.x+5, location.y-shape.y); //subtract shape.x and shape.y bcos we are in FBO
//    ofDrawLine(location.x-shape.x, location.y-shape.y-5, location.x-shape.x, location.y-shape.y+5);
//    if(soundProperties->getBool(paramBoolToggle)) ofDrawCircle(location.x-shape.x,location.y-shape.y,10);   //draw toggle, not trigger
    ofDrawLine(location.x-5, location.y, location.x+5, location.y); //subtract shape.x and shape.y bcos we are in FBO
    ofDrawLine(location.x, location.y-5, location.x, location.y+5);
    if(soundProperties->getBool(paramBoolToggle)) ofDrawCircle(location.x,location.y,10);   //draw toggle, not trigger
    ofPopStyle();
}


void ofxAVUIXYPad::mouseMoved(ofMouseEventArgs & args) {
}

void ofxAVUIXYPad::mousePressed(ofMouseEventArgs & args) {
    dragging = false;
}

void ofxAVUIXYPad::mouseDragged(ofMouseEventArgs & args) {
    if (shape.inside(args.x, args.y)) {
        dragging = true;
        location.x = args.x;
        location.y = args.y;
        ofParameter<float>  px = soundProperties->getFloat(paramX);
        ofParameter<float>  py = soundProperties->getFloat(paramY);
        float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, px.getMin(), px.getMax());
        float vertVal = ofMap(args.y, shape.y, shape.y + shape.height, py.getMin(), py.getMax());
        px = horizVal;
        py = vertVal;
    }
}

void ofxAVUIXYPad::mouseReleased(ofMouseEventArgs & args) {
    if (shape.inside(args.x, args.y)) {
//        if (ofGetElapsedTimeMillis() - doubleClickTimer <= DOUBLECLICK_MILLIS) {
//            if (!dragging) soundProperties->getBool(paramBool) = !soundProperties->getBool(paramBool);    //no toggle activation
            if (!dragging) soundProperties->getBool(paramBoolTrigger) = true;                               //just trigger
            location.x = args.x;
            location.y = args.y;
            ofParameter<float>  px = soundProperties->getFloat(paramX);
            ofParameter<float>  py = soundProperties->getFloat(paramY);
            float horizVal = ofMap(args.x, shape.x, shape.x + shape.width, px.getMin(), px.getMax());
            float vertVal = ofMap(args.y, shape.y, shape.y + shape.height, py.getMin(), py.getMax());
            px = horizVal;
            py = vertVal;
//            clicking = false;
//        } else {
//            doubleClickTimer = ofGetElapsedTimeMillis();
//            clicking = true;
//            mouseArgs = args;
//        }
        dragging = false;
    }
}

void ofxAVUIXYPad::sequencerListener(ofMouseEventArgs & args) {
    if (args.type == ofMouseEventArgs::Moved) mouseMoved(args);
    else if (args.type == ofMouseEventArgs::Pressed) mousePressed(args);
    else if (args.type == ofMouseEventArgs::Released) mouseReleased(args);
    else if (args.type == ofMouseEventArgs::Dragged) mouseDragged(args);
}

void ofxAVUIXYPad::mouseScrolled(ofMouseEventArgs & args) {
}
