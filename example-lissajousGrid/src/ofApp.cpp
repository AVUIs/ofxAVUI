//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    //ENVIRONMENT AND MAXIMILIAN
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);
    sampleRate 	= 44100; /* Audio sampling rate */
    bufferSize	= 512; /* Audio buffer size */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    //ZONE 0 SETUP
    //parameters: name, x, y, width, background color, foreground color, sound filename, sound buffer size
    zones[0].setup("zone1", 30, 150, 600, ofColor(100,100,100, 150), ofColor(255,255,255, 255), "synth.wav", bufferSize);
    ofxAVUIXYPad *pad1 = new ofxAVUIXYPad("", "triggerPlay",  "toggleLooping", "volume", "pitch");
    zones[0].addUI(pad1, 150);
    ofxAVUIToggle *toggle1 = new ofxAVUIToggle("Looping", "toggleLooping");
    zones[0].addUI(toggle1, 100);
    ofxAVUIButton *button1 = new ofxAVUIButton("Trigger", "triggerPlay");
    zones[0].addUI(button1, 100);
    ofxAVUIVisualLissajous *visual1 = new ofxAVUIVisualLissajous();
    zones[0].addVisual(visual1, ofColor(255,255,255));

    zones[1].setup("zone2", 660, 150, 600, ofColor(100,100,100, 150), ofColor(255,255,255, 255), "drumloop.wav", bufferSize);
    ofxAVUIXYPad *pad2 = new ofxAVUIXYPad("", "triggerPlay",  "toggleLooping", "volume", "pitch");
    zones[1].addUI(pad2, 150);
    ofxAVUIToggle *toggle2 = new ofxAVUIToggle("Looping", "toggleLooping");
    zones[1].addUI(toggle2, 100);
    ofxAVUIButton *button2 = new ofxAVUIButton("Trigger", "triggerPlay");
    zones[1].addUI(button2, 100);
    ofxAVUIVisualGrid *visual2 = new ofxAVUIVisualGrid();
    zones[1].addVisual(visual2, ofColor(255,255,255));
    
    
    
    //START SOUND
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup*/
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    //get individual parameters and use them outside of the zone, together with their min/max limits
    ofParameter<float> x = zones[0].getParamValueFloat("volume");
    int coordX = ofMap(x, x.getMin(), x.getMax(), 0, ofGetWidth());
    ofParameter<float> y = zones[0].getParamValueFloat("pitch");
    int coordY = ofMap(y, y.getMin(), y.getMax(), 0, ofGetHeight());
    ofDrawLine(coordX, 0, coordX, ofGetHeight());
    ofDrawLine(0, coordY, ofGetWidth(), coordY);

    for(int i = 0; i < 3; i++) {
        zones[i].draw();
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        output[i*nChannels    ] = 0;
        output[i*nChannels + 1] = 0;

        for (int k=0; k<3; k++) {
            zones[k].play(i);
            output[i*nChannels    ] += zones[k].getOutput(0);
            output[i*nChannels + 1] += zones[k].getOutput(1);
        }
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
