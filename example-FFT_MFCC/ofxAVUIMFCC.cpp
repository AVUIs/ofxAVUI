//
//  ofxAVUIVisualBars.cpp
//
//  Part of ofxAVUI addon. Developed by Francisco Bernardo in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIMFCC.h"

ofxAVUIMFCC::ofxAVUIMFCC(int nRects){
    numRects=nRects;
    
    mfft.setup(numRects, 512, 256);
    mfccs = (double*) malloc(sizeof(double) * 13);
    mfcc.setup(512, 42, 13, 20, 20000, 44100);
}

void ofxAVUIMFCC::draw(float * buffer, float amplitude){
    
    //wave
    ofPushStyle();
    ofFill();
    ofSetColor(visColor);
    float x;
    for(int i=0; i<13; i++){
        
        mfft.process(buffer[i]);
        mfcc.mfcc(mfft.magnitudes, mfccs);
        float y2 = mfccs[i] * 100;
        float rectWidth = shape.width/13;
        x = i*rectWidth;
        ofDrawRectangle(x, 0, rectWidth, y2);
    }
    ofPopStyle();

}
