//
//  ofxAVUIXYCanvas.h
//  Developed by Berkan Eskikaya
//
//  Part of ofxAVUI addon, developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIXYCanvas_h
#define ofxAVUIXYCanvas_h

#include "ofMain.h"
#include "ofxAVUIBase.h"
#include "ofxAVUIXYPad.h"


class ofxAVUIXYCanvas : public ofxAVUIXYPad {
public:
    ofxAVUIXYCanvas(string _title, string _paramBool2, string _paramBoolTrigger, string _paramBoolToggle, string _paramFloat2);
    ofxAVUIXYCanvas(string _title, string _paramBool2, string _paramBoolTrigger, string _paramBoolToggle, string _paramFloat2, string bgImagePath);
    virtual ~ofxAVUIXYCanvas();

    void mouseMoved(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args);

    void draw();

    ofImage bgImage;
    ofFbo   fbo;

};

#endif /* ofxAVUIXYCanvas_h */
