//
//  ofxAVUIRangeSlider.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIRangeSlider_h
#define ofxAVUIRangeSlider_h

#include "ofMain.h"
#include "ofxAVUIBase.h"

class ofxAVUIRangeSlider : public ofxAVUIBase {
public:
    ofxAVUIRangeSlider() {};
    ofxAVUIRangeSlider(string _title, string _paramFloat1, string _paramFloat2);
    virtual ~ofxAVUIRangeSlider();
    virtual void setPosition(int _x, int _y, int _width, int _height);   //polymorhing so we can set the starting position for cursor

    void mouseMoved(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args);

    void update();  //set UI state based on parameters
    void draw();

private:
    int              x1, x2; //range
    bool             dragging;
    string           param1, param2;

};

#endif /* ofxAVUISlider_h */
