//
//  ofxAVUIVisualLissajous.h
//  AVUIApp2
//
//  Created by jayson on 12/03/2016.
//
//

#ifndef __AVUIApp2__ofxAVUIVisualLissajous__
#define __AVUIApp2__ofxAVUIVisualLissajous__

#include <stdio.h>
#include "ofMain.h"
#include "ofxAVUIVisualBase.h"
#include "ofxSyphon.h"

#define DEFAULT_SPEED 0.025

class ofxAVUIVisualLissajous : public ofxAVUIVisualBase {
public:
    // put any setup code in a custom constructor
    ofxAVUIVisualLissajous();
    
    void draw(float *buffer, float amplitude);
    
private:
    int pointCount;
    
    float offset;
    
    //float offsetSpeed;
    float smooth;
    float totalAmplitude;
    
    
//    ofFbo           visualFbo;
//    ofxSyphonServer syphonOut;
};

#endif /* defined(__AVUIApp2__ofxAVUIVisualLissajous__) */
