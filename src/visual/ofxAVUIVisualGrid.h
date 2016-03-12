//
//  ofxAVUIVisualLines.h
//  AVUIApp2
//
//  Created by jayson on 12/03/2016.
//
//

#ifndef __AVUIApp2__ofxAVUIVisualLines__
#define __AVUIApp2__ofxAVUIVisualLines__

#include "ofMain.h"
#include "ofxAVUIVisualBase.h"
#include "ofxSyphon.h"

class ofxAVUIVisualGrid : public ofxAVUIVisualBase {
public:
    // put any setup code in a custom constructor
    ofxAVUIVisualGrid();
    
    void draw(float *buffer, float amplitude);
    
private:
    
    ofFbo           visualFbo;
    ofxSyphonServer syphonOut;
    int numSquaresX, numSquaresY;
};

#endif /* defined(__AVUIApp2__ofxAVUIVisualLines__) */
