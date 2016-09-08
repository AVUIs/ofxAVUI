//
//  ofxAVUIVisualWave.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIVisualWave.h"

ofxAVUIVisualWave::ofxAVUIVisualWave(){
}

void ofxAVUIVisualWave::draw(float * buffer, float amplitude){
        ofPushStyle();
        ofFill();
        ofSetColor(visColor);
        for(int i=0; i<myBufferSize; i++){
        float p = i / (float)(myBufferSize);
        float y1 = shape.height/2;
        float y2 = buffer[i] * (shape.height);
            float x = p * shape.width;
            float rectWidth = shape.width/myBufferSize;
            ofDrawRectangle(x, y1, rectWidth, y2);
        }
        ofPopStyle();
}
