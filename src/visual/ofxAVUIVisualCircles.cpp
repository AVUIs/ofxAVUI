//
//  ofxAVUIVisualCircles.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIVisualCircles.h"

ofxAVUIVisualCircles::ofxAVUIVisualCircles(int nCircles){
    numCircles=nCircles;
}

void ofxAVUIVisualCircles::draw(float * buffer, float amplitude){
        ofPushStyle();
        ofFill();
        ofSetColor(visColor);
        for(int i=0; i<numCircles; i++){
            float y1 = shape.height/2;
            int bufferSlice=myBufferSize/numCircles;
            float y2 = buffer[bufferSlice*i] * (shape.height);
            float circleSpacing = shape.width/numCircles;
            float x = i*circleSpacing+circleSpacing/2;
            ofDrawCircle(x, y1, y2);
        }
        ofPopStyle();
}
