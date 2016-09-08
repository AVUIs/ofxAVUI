//
//  ofxAVUIVisualBase.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIVisualBase_h
#define ofxAVUIVisualBase_h

#include "ofMain.h"


class ofxAVUIVisualBase {

public:
    ofxAVUIVisualBase();
    void setup(int _bufferSize, ofColor _visColor);
    void setPosition(int _x, int _y, int _width, int _height);
    
    virtual void draw(float *buffer, float amplitude) = 0;                   //every child needs to implement this

protected:
    ofRectangle     shape;
    int             myBufferSize;
    ofColor         visColor;
//    ofFbo           FBO;
};




#endif /* ofxAVUIVisualBase_h */
