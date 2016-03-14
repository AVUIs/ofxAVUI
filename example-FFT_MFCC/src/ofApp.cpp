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
    zones[0].setup("zone1", 50, 100, 200, ofColor(100,100,100, 150), ofColor(0,255,255, 255), "synth.wav", bufferSize);
    //ZONE 0 UI
    //pad parameters: caption, trigger (single tap) parameter name, toggle (double tap) parameter name, x parameter name, y parameter name
    
    ofxAVUIXYPad *pad1 = new ofxAVUIXYPad("", ofxAVUIZone::TRIGGER_PLAY,  ofxAVUIZone::TRIGGER_LOOPING, ofxAVUIZone::VOLUME, ofxAVUIZone::PITCH);
    //pad additional parameter: height
    zones[0].addUI(pad1, 150);
    //toggle parameters: caption, toggle (double tap) parameter name
    ofxAVUIToggle *toggle1 = new ofxAVUIToggle("Looping", ofxAVUIZone::TOGGLE_LOOPING);
    zones[0].addUI(toggle1, 100);
    //button parameters: caption, trigger (single tap) parameter name
    ofxAVUIButton *button1 = new ofxAVUIButton("Trigger", ofxAVUIZone::TOGGLE_PLAY);
    zones[0].addUI(button1, 100);
    
    zones[0].addParameterFloat("hueMin", 0,255,200);
    zones[0].addParameterFloat("hueMax", 0,255,50);
    //slider parameters: caption, x min parameter name, x max parameter name
    ofxAVUIRangeSlider *rsl1 = new ofxAVUIRangeSlider("Hue","hueMin", "hueMax");
    //pad additional parameter: height
    zones[0].addUI(rsl1, 150);

    //ZONE 0 AUDIO EFFECTS
    //empty
    //ZONE 0 VISUALS


    
    ofxAVUIFFT *visual1 = new ofxAVUIFFT(bufferSize);
    zones[0].addVisual(visual1, ofColor(0,0,255));
    
    
    //ZONE 1 SETUP
    zones[1].setup("zone2", 300, 150, 150, ofColor(100,100,100, 150), ofColor(255,255,0, 255), "drumloop.wav", bufferSize);
    //ZONE 1 UI
    ofxAVUIEmpty *empty1 = new ofxAVUIEmpty("Empty");
    zones[1].addUI(empty1, 50);
    ofxAVUIXYPad *pad2 = new ofxAVUIXYPad("Pad", ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::PITCH, ofxAVUIZone::VOLUME);
    zones[1].addUI(pad2, 100);
    ofxAVUIEmpty *empty2 = new ofxAVUIEmpty("");
    zones[1].addUI(empty2, 75);
    //slider parameters: caption, trigger (single tap) parameter name, toggle (double tap) parameter name, x parameter name
    ofxAVUISlider *slider1 = new ofxAVUISlider("Slider", ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::TOGGLE_LOOPING, ofxAVUIZone::PITCH);
    zones[1].addUI(slider1, 100);
    ofxAVUIToggle *toggle2 = new ofxAVUIToggle("Looping", ofxAVUIZone::TOGGLE_LOOPING);
    zones[1].addUI(toggle2, 50);
    //ZONE 1 AUDIO EFFECTS
    //empty
    //ZONE 1 VISUALS

    
    ofxAVUIMFCC *visual2 =  new ofxAVUIMFCC(bufferSize);
    zones[1].addVisual(visual2, ofColor(0,0,255));
    
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

    //DRAW ZONES
    for (int k=0; k<4; k++) {
        zones[k].draw();
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
