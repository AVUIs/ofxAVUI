//
//  ofxAVUIVisualBars.cpp
//
//  Part of ofxAVUI addon. Developed by Francisco Bernardo in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIFFT.h"

ofxAVUIFFT::ofxAVUIFFT(int nRects){
   
    numRects=nRects;
    mfft.setup(numRects, 512, 256);
}

void ofxAVUIFFT::draw(float * buffer, float amplitude){
    
    //wave
    ofPushStyle();
    ofFill();
    ofSetColor(visColor);
    float x;
    for(int i=0; i<512; i++){
        
        mfft.process(buffer[i]);
        float y2 = mfft.magnitudes[i] * (shape.height)/3;
        float rectWidth = shape.width/512*2;
        x = i*rectWidth;
        ofDrawRectangle(x, shape.height/2, rectWidth, y2);
        ofDrawRectangle(x, shape.height/2, rectWidth, -y2);
    }
    ofPopStyle();
    
}
