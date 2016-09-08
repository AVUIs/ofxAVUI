//
//  ofxAVUIVisualBase.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIVisualBase.h"

ofxAVUIVisualBase::ofxAVUIVisualBase(){
    shape.x = 0;
    shape.y = 0;
    shape.width = 0;
    shape.height = 0;
}

void ofxAVUIVisualBase::setup(int _bufferSize, ofColor _visColor) {
    myBufferSize = _bufferSize;
    visColor = _visColor;
}

void ofxAVUIVisualBase::setPosition(int _x, int _y, int _width, int _height) {
    shape.x = _x;
    shape.y = _y;
    shape.width = _width;
    shape.height = _height;
//    FBO.allocate(shape.width, shape.height);
}

