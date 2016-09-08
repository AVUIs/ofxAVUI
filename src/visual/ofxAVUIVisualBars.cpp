//
//  ofxAVUIVisualBars.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIVisualBars.h"

ofxAVUIVisualBars::ofxAVUIVisualBars(int nRects){
    numRects=nRects;
}

void ofxAVUIVisualBars::draw(float * buffer, float amplitude){
        ofPushStyle();
        ofFill();
        ofSetColor(visColor);
        for(int i=0; i<numRects; i++){
            float y1 = shape.height/2;
            int bufferSlice=myBufferSize/numRects;
            float y2 = buffer[bufferSlice*i] * (shape.height);
            float rectWidth = shape.width/numRects;
            float x = i*rectWidth;
            ofDrawRectangle(x, y1, rectWidth, y2);
        }
        ofPopStyle();
}
