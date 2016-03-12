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
    ofxAVUIVisualWave *visual1 = new ofxAVUIVisualWave();
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
    ofxAVUIVisualBars *visual2 = new ofxAVUIVisualBars(5);
    zones[1].addVisual(visual2, ofColor(255,0,0));

    //ZONE 2 SETUP
    zones[2].setup("zone3", 500, 100, 200, ofColor(100,100,100, 150), ofColor(255,0,255, 255), "bass.wav", bufferSize);
    //ZONE 2 UI
    ofxAVUIXYPad *pad3 = new ofxAVUIXYPad("Pad", ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::PITCH, ofxAVUIZone::VOLUME);
    zones[2].addUI(pad3, 100);
    ofxAVUIXYPad *pad4 = new ofxAVUIXYPad("Filter Pad", "filterTrigger", "filterToggle", "frequency", "resonance");
    zones[2].addUI(pad4, 100);
    ofxAVUIToggle *toggle3 = new ofxAVUIToggle("Filter Toggle", "filterToggle");
    zones[2].addUI(toggle3, 50);
    ofxAVUIXYPad *pad5 = new ofxAVUIXYPad("Delay Pad", "delayTrigger", "delayToggle", "size", "feedback");
    zones[2].addUI(pad5, 100);
    ofxAVUIToggle *toggle4 = new ofxAVUIToggle("Delay Toggle", "delayToggle");
    zones[2].addUI(toggle4, 50);
    //ZONE 2 AUDIO EFFECTS
    ofxAVUISoundFxFilter *filter1 = new ofxAVUISoundFxFilter();
    //sound fx parameters:
    //- filter enabled toggle name (will be linked to any toggle UI with same name), start value
    //- 1st parameter float name (will be linked to any toggle UI with same name), min value, max value, start value
    //- 2nd parameter float name (will be linked to any toggle UI with same name), min value, max value, start value
    filter1->setup("filterToggle", false, "frequency", 200, 20000, 200, "resonance", 0, 100, 10);
    zones[2].addSoundFx(filter1);
    ofxAVUISoundFxDelay *delay1 = new ofxAVUISoundFxDelay();
    delay1->setup("delayToggle", false, "size", 10000, 40000, 20000, "feedback", 0.5, 1.0, 0.75);
    zones[2].addSoundFx(delay1);
    //ZONE 2 VISUALS
    ofxAVUIVisualCircles *visual3 = new ofxAVUIVisualCircles(10);
    zones[2].addVisual(visual3, ofColor(0,255,0, 196));

    //ZONE 3 SETUP
    zones[3].setup("zone4", 725, 100, 50, ofColor(100,200,100, 150), ofColor(0,255,255, 255), "bass.wav", bufferSize);
    //ZONE 3 UI
    //
    //example of parameter addition for routing ouside of the zone
    zones[3].addParameterBool("trigger4", false);
    zones[3].addParameterFloat("pitch4", 0,1,0.5);
    zones[3].addParameterFloat("volume4", 0,1,0.5);
    ofxAVUIXYPad *pad11 = new ofxAVUIXYPad("test", "trigger4", "trigger4", "pitch4", "volume4");
    zones[3].addUI(pad11, 50);
    zones[3].addParameterBool("trigger5", false);
    zones[3].addParameterFloat("pitch5", 0,1,0.5);
    zones[3].addParameterFloat("volume5", 0,1,0.5);
    ofxAVUIXYPad *pad12 = new ofxAVUIXYPad("test", "trigger5", "trigger5", "pitch5", "volume5");
    zones[3].addUI(pad12, 50);


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
