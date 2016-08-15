#pragma once

#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "ofxMaxim.h" 
#include "ofxAVUI.h"

#define NUM_ZONES 3
class ofApp : public ofxiOSApp {
	
public:
    void setup();
    void update();
    void draw();
    void exit();

    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);

    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);

    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut(float * output, int bufferSize, int nChannels);    
    
    float 	* lAudioOut; /* outputs */
    float   * rAudioOut;
    
    float * lAudioIn; /* inputs */
    float * rAudioIn;
    
    int		bufferSize;
    int		sampleRate;
    
    //ofxAVUI
    ofxAVUIZone     zones[NUM_ZONES];

    ofDirectory     DIR;
    int             numFiles;
    int             files[NUM_ZONES];

};


