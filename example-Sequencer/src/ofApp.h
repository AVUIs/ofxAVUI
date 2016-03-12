//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAVUI.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Audio output and input methods
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);

        int		bufferSize;
        int		sampleRate;

    //ofxAVUI
    ofxAVUIZone             zonePad,zoneSequencer;
    
    //UI positions and dimensions
    ofRectangle padBounds;
    int sequencerX,sequencerY,sequencerW,sequencerStepH,sequencerToggleH;
    
    //pad
    string xParamName,yParamName;
    ofPolyline gesture;
    ofPoint gestureCurrentPoint;
    float gestureTraversal;
    
    //sequencer
    int now,delay;
    int numSequencerSteps;
    int currentSequencerStep;
    string playbackParamName;
    string sequencerTogglePrefix;
    string timerParamName;
    string filterSpeedParamName;
    string resetParamName;
    
};
