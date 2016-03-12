//
//  ofxAVUIXYPad.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIXYPad_h
#define ofxAVUIXYPad_h

#include "ofMain.h"
#include "ofxAVUIBase.h"

#define DOUBLECLICK_MILLIS 200


class ofxAVUIXYPad : public ofxAVUIBase {
public:
    ofxAVUIXYPad() {};
    ofxAVUIXYPad(string _title, string _paramBool2, string _paramBoolTrigger, string _paramBoolToggle, string _paramFloat2);
    ~ofxAVUIXYPad();
    virtual void setPosition(int _x, int _y, int _width, int _height);   //polymorhing so we can set the starting position for cursor
    
    void mouseMoved(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args);
    
    void update();
    void draw();

protected:
    float            savedX, savedY;
    float            savedHorizVal, savedVertVal;
    ofRectangle      location;
    bool             dragging;
    long             doubleClickTimer;
    bool             clicking;
    ofMouseEventArgs mouseArgs;
    string           paramX, paramY, paramBoolTrigger, paramBoolToggle;
};

#endif /* ofxAVUIXYPad_h */
