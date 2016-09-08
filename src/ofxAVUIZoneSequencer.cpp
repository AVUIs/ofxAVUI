//
//  ofxAVUIZoneSequencer.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIZoneSequencer.h"

ofxAVUIZoneSequencer::ofxAVUIZoneSequencer() {
}

ofxAVUIZoneSequencer::~ofxAVUIZoneSequencer() {
}

void ofxAVUIZoneSequencer::setup(int _x, int _y, int _width, int _height){
    shape = ofRectangle(_x, _y, _width, _height);
    reset();
}

void ofxAVUIZoneSequencer::unregisterMouse() {
	ofUnregisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);
}

void ofxAVUIZoneSequencer::registerMouse() {
    ofRegisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);
}

void ofxAVUIZoneSequencer::reset(){
    counter = 0;
    running = false;
    eventList.clear();
}

void ofxAVUIZoneSequencer::run(){
    if (!running) {
        reset();      //reset on first run, don't reset if already running
        registerMouse();
    }
    running = true;
}

void ofxAVUIZoneSequencer::stop(){
    reset();
	unregisterMouse();
}

void ofxAVUIZoneSequencer::update(){
    if (running) {
        counter++;
        if (counter >= SEQUENCE_DURATION) counter = 0;
//        ofUnregisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);
        for(int i=0;i<eventList.size();i++){
            eventList[i].active = (counter == eventList[i].time)?true:false;
            if (eventList[i].active) {
                ofNotifyEvent(sequencerEvents.sequencerEvent, eventList[i].mouseArgs, this);
            }
        }
//        ofRegisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);
    }
}

void ofxAVUIZoneSequencer::draw(){
    if (running) {
        ofPushStyle();
        //cursor
        float timeX = ofMap(counter, 0, SEQUENCE_DURATION-1, shape.x, shape.x + shape.width);
        ofSetColor(255, 0, 0);
        ofDrawLine(timeX, shape.y, timeX, shape.y + shape.height);
        //points
        for(int i=0;i<eventList.size();i++){
            timeX = ofMap(eventList[i].time, 0, SEQUENCE_DURATION-1, shape.x, shape.x + shape.width);
            float radius;
            if(eventList[i].active){
                ofSetColor(255,200);
                 radius = 200;
            }else{
                ofSetColor(127);
                 radius = 20;
            }
            ofFill();
            ofDrawCircle(eventList[i].mouseArgs.x, eventList[i].mouseArgs.y, radius);
            ofNoFill();
            ofDrawRectangle(timeX-radius/2, shape.y + shape.height/2 - radius/2, radius, radius*2);
            ofDrawLine(eventList[i].mouseArgs.x, eventList[i].mouseArgs.y, timeX, shape.y + shape.height/2);
        }
        ofPopStyle();
    }
}

void ofxAVUIZoneSequencer::addEvent(ofMouseEventArgs & args) {
    if (running && shape.inside(args.x, args.y)) {
        bool safe = false;
        for (int i=0;i<sequencerEvents.restrictions.size();i++) {
            if (sequencerEvents.restrictions[i].inside(args.x, args.y)) { safe = true; break; }
        }
        if (safe) {
            eventInfo newEvent;
            newEvent.mouseArgs = args;
            newEvent.time = counter;
            newEvent.active = false;
            eventList.push_back(newEvent);
        }
    }
}

void ofxAVUIZoneSequencer::mousePressed(ofMouseEventArgs & args) {
//    addEvent(args);
}
void ofxAVUIZoneSequencer::mouseMoved(ofMouseEventArgs & args) {
//    addEvent(args);
}
void ofxAVUIZoneSequencer::mouseDragged(ofMouseEventArgs & args) {
//    addEvent(args);
}
void ofxAVUIZoneSequencer::mouseReleased(ofMouseEventArgs & args) {
    addEvent(args);
}



