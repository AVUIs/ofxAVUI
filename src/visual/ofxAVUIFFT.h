//
//  ofxAVUIVisualBars.h
//
//  Part of ofxAVUI addon. Developed by Francisco Bernardo in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAVUIVisualBase.h"

class ofxAVUIFFT : public ofxAVUIVisualBase {
public:
    // put any setup code in a custom constructor
    ofxAVUIFFT(int nRects);
    
    void draw(float *buffer, float amplitude);
    
private:
    ofxMaxiFFT mfft;
    int numRects;
    int fftSize;

};


