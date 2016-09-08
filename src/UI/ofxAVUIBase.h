//
//  ofxAVUIBase.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIBase_h
#define ofxAVUIBase_h

#include "ofMain.h"

class ofxAVUIBase {

public:
    ofxAVUIBase();
    virtual ~ofxAVUIBase();
    virtual void setPosition(int _x, int _y, int _width, int _height);
    void  setFont(ofTrueTypeFont *_font);
    ofRectangle  getPosition();
    virtual void setTakeoverPosition(int _x, int _y, int _width, int _height);
    void setColor(ofColor _bgColor, ofColor _fgColor);
    void setTitle(string _title);
    void bindProperties(ofParameterGroup *_soundProperties);
    void drawContour(); //specific ofxAVUI contour shape
    void drawTitle();
    bool takingOver();
    void unregisterMouse();
    void registerMouse();
    virtual void update() {};
    virtual void draw() = 0;
    
    virtual void mouseMoved(ofMouseEventArgs & args) = 0;
    virtual void mousePressed(ofMouseEventArgs & args) = 0;
    virtual void mouseDragged(ofMouseEventArgs & args) = 0;
    virtual void mouseReleased(ofMouseEventArgs & args) = 0;
    virtual void mouseScrolled(ofMouseEventArgs & args) = 0;
    virtual void mouseEntered(ofMouseEventArgs & args) {}
    virtual void mouseExited(ofMouseEventArgs & args) {}

protected:
    ofRectangle         getBitmapStringBoundingBox(string text);
    ofRectangle         shape, takeoverShape;
    ofColor             bgColor, fgColor;
    string              title;
    ofParameterGroup   *soundProperties;
    bool                synced;
    bool                takeover;   //TRUE => this UI takes over the whole Zone
    ofTrueTypeFont     *uifont;
    bool                customFont;
};

#endif /* ofxAVUIBase_h */
