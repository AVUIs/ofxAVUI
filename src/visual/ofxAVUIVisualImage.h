//
//  ofxAVUIVisualImage.h
//
//  Developed by Berkan Eskikaya
//
//  Part of ofxAVUI addon, developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIVisualImage_h
#define ofxAVUIVisualImage_h

#include "ofMain.h"
#include "ofxAVUIVisualBase.h"

const static int DEFAULT_ALPHA = 90;

class ofxAVUIVisualImage : public ofxAVUIVisualBase {
public:
    // put any setup code in a custom constructor
    ofxAVUIVisualImage(string path);
    ofxAVUIVisualImage(string path, int alpha);
    
    void draw(float *buffer, float amplitude);
    
private:
    int alpha;
    ofImage image;
    ofImage display;


};

#endif /* ofxAVUIVisualImage_h */
