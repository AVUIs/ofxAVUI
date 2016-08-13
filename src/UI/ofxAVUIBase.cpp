//
//  ofxAVUIBase.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIBase.h"

ofxAVUIBase::ofxAVUIBase(){
    registerMouse();
    synced = false;
    takeover = false;
    shape = ofRectangle(0,0,0,0);
    takeoverShape = ofRectangle(0,0,0,0);
}

ofxAVUIBase::~ofxAVUIBase(){
    unregisterMouse();
}

void ofxAVUIBase::setPosition(int _x, int _y, int _width, int _height) {
    shape.x = _x;
    shape.y = _y;
    shape.width = _width;
    shape.height = _height;
}

ofRectangle ofxAVUIBase::getPosition() {
    return shape;
}

void ofxAVUIBase::setTakeoverPosition(int _x, int _y, int _width, int _height) {
    takeoverShape.x = _x;
    takeoverShape.y = _y;
    takeoverShape.width = _width;
    takeoverShape.height = _height;
}

bool ofxAVUIBase::takingOver() {
    return takeover;
}

void ofxAVUIBase::unregisterMouse() {
	ofUnregisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);
}

void ofxAVUIBase::registerMouse() {
    ofRegisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);
}

void ofxAVUIBase::setColor(ofColor _bgColor, ofColor _fgColor) {
    bgColor = _bgColor;
    fgColor = _fgColor;
}

void ofxAVUIBase::bindProperties(ofParameterGroup *_soundProperties) {
    soundProperties = _soundProperties;
}

void ofxAVUIBase::drawContour() {
    //<contours>
    ofRectangle activeShape = (takeover?takeoverShape:shape);
    ofDrawLine(activeShape.x,activeShape.y,activeShape.x+activeShape.width*0.25,activeShape.y);
    ofDrawLine(activeShape.x+activeShape.width*0.75,activeShape.y,activeShape.x+activeShape.width,activeShape.y);
    ofDrawLine(activeShape.x,activeShape.y+activeShape.height,activeShape.x+activeShape.width*0.25,activeShape.y+activeShape.height);
    ofDrawLine(activeShape.x+activeShape.width*0.75,activeShape.y+activeShape.height,activeShape.x+activeShape.width,activeShape.y+activeShape.height);
    ofDrawLine(activeShape.x,activeShape.y,activeShape.x,activeShape.y+activeShape.height*0.25);
    ofDrawLine(activeShape.x+activeShape.width,activeShape.y,activeShape.x+activeShape.width,activeShape.y+activeShape.height*0.25);
    ofDrawLine(activeShape.x,activeShape.y+activeShape.height*0.75,activeShape.x,activeShape.y+activeShape.height);
    ofDrawLine(activeShape.x+activeShape.width,activeShape.y+activeShape.height*0.75,activeShape.x+activeShape.width,activeShape.y+activeShape.height);
    //</contours>

/*    //<contours>
    ofDrawLine(0,0,shape.width*0.25,0);
    ofDrawLine(shape.width*0.75,0,shape.width,0);
    ofDrawLine(0,shape.height,shape.width*0.25,shape.height);
    ofDrawLine(shape.width*0.75,0+shape.height,shape.width,shape.height);
    ofDrawLine(0,0,0,shape.height*0.25);
    ofDrawLine(shape.width,0,shape.width,shape.height*0.25);
    ofDrawLine(0,0+shape.height*0.75,0,shape.height);
    ofDrawLine(shape.width,shape.height*0.75,shape.width,shape.height);
    //</contours>
*/
}

void ofxAVUIBase::drawTitle() {
//centered, no fbo
//    ofRectangle titleBounds = getBitmapStringBoundingBox(title);
//    ofDrawBitmapString(title, shape.x + shape.width/2 - titleBounds.width/2, 0 + shape.height/2 - titleBounds.height/2 + 10);
//lover left, fbo
    ofRectangle activeShape = (takeover?takeoverShape:shape);
    ofDrawBitmapString(title, activeShape.x + 5, activeShape.y + activeShape.height - 5);
}

ofRectangle ofxAVUIBase::getBitmapStringBoundingBox(string text){
    vector<string> lines = ofSplitString(text, "\n");
    int maxLineLength = 0;
    for(int i = 0; i < (int)lines.size(); i++) {
        // tabs are not rendered
        const string & line(lines[i]);
        int currentLineLength = 0;
        for(int j = 0; j < (int)line.size(); j++) {
            if (line[j] == '\t') {
                currentLineLength += 8 - (currentLineLength % 8);
            } else {
                currentLineLength++;
            }
        }
        maxLineLength = MAX(maxLineLength, currentLineLength);
    }
    
    int padding = 4;
    int fontSize = 8;
    float leading = 1.7;
    int height = lines.size() * fontSize * leading - 1;
    int width = maxLineLength * fontSize;
    return ofRectangle(0,0,width, height);
}