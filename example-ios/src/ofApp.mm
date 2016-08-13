#include "ofApp.h"
#include "ofxMaxim.h"



//--------------------------------------------------------------
void ofApp::setup(){
    //ENVIRONMENT AND MAXIMILIAN
    ofSetOrientation(OF_ORIENTATION_90_RIGHT);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);
    sampleRate 	= 44100; /* Audio sampling rate */
    bufferSize	= 512; /* Audio buffer size */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    //hack for OF not adjusting to iPad landscape mode correctly
    if(ofxiOSGetGLView().frame.origin.x != 0 ||
        ofxiOSGetGLView().frame.size.width != [[UIScreen mainScreen] bounds].size.width) {
        ofxiOSGetGLView().frame = CGRectMake(0,0,[[UIScreen mainScreen] bounds].size.width,[[UIScreen mainScreen] bounds].size.height);
    }
    
    //ZONE 0 SETUP
    //parameters: name, x, y, width, background color, foreground color, sound filename, sound buffer size
    zones[0].setup("zone1", 50, 100, 200, ofColor(100,100,100, 150), ofColor(0,255,255, 255), "synth.wav", bufferSize);
    //ZONE 0 UI
    //pad parameters: caption, trigger (single tap) parameter name, toggle (double tap) parameter name, x parameter name, y parameter name
    ofxAVUIXYPad *pad1 = new ofxAVUIXYPad("", "triggerPlay",  "toggleLooping", "volume", "pitch");
    //pad additional parameter: height
    zones[0].addUI(pad1, 150);
    //toggle parameters: caption, toggle (double tap) parameter name
    ofxAVUIToggle *toggle1 = new ofxAVUIToggle("Looping", "toggleLooping");
    zones[0].addUI(toggle1, 100);
    //button parameters: caption, trigger (single tap) parameter name
    ofxAVUIButton *button1 = new ofxAVUIButton("Trigger", "triggerPlay");
    zones[0].addUI(button1, 100);
    //dropdown parameters: caption, trigger (single tap) parameter name
    ofxAVUIDropDown *dropdown1 = new ofxAVUIDropDown("DropDown", "selection");
    zones[0].addUI(dropdown1, 50);
    for(int i=0;i<100;i++) dropdown1->addItem("Item " + ofToString(i));
    //ZONE 0 AUDIO EFFECTS
    //empty
    //ZONE 0 VISUALS
    ofxAVUIVisualWave *visual1 = new ofxAVUIVisualWave();
    zones[0].addVisual(visual1, ofColor(0,0,255));

    //ZONE 1 SETUP
    zones[1].setup("zone2", 325, 150, 150, ofColor(100,100,100, 150), ofColor(255,255,0, 255), "drumloop.wav", bufferSize);
    //ZONE 1 UI
    ofxAVUIEmpty *empty1 = new ofxAVUIEmpty("Empty");
    zones[1].addUI(empty1, 50);
    ofxAVUIXYPad *pad2 = new ofxAVUIXYPad("Pad", "triggerPlay", "triggerPlay", "pitch", "volume");
    zones[1].addUI(pad2, 100);
    ofxAVUIEmpty *empty2 = new ofxAVUIEmpty("");
    zones[1].addUI(empty2, 75);
    //slider parameters: caption, trigger (single tap) parameter name, toggle (double tap) parameter name, x parameter name
    ofxAVUISlider *slider1 = new ofxAVUISlider("Slider", "triggerPlay", "toggleLooping", "pitch");
    zones[1].addUI(slider1, 100);
    ofxAVUIToggle *toggle2 = new ofxAVUIToggle("Looping", "toggleLooping");
    zones[1].addUI(toggle2, 50);
    //ZONE 1 AUDIO EFFECTS
    //empty
    //ZONE 1 VISUALS
    ofxAVUIVisualBars *visual2 = new ofxAVUIVisualBars(5);
    zones[1].addVisual(visual2, ofColor(255,0,0));

    //ZONE 2 SETUP
    zones[2].setup("zone3", 550, 100, 200, ofColor(100,100,100, 150), ofColor(255,0,255, 255), "bass.wav", bufferSize);
    //ZONE 2 UI
    ofxAVUIXYPad *pad3 = new ofxAVUIXYPad("Pad", "triggerPlay", "triggerPlay", "pitch", "volume");
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

    //START SOUND
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup*/

}

//--------------------------------------------------------------
void ofApp::update(){
    //UPDATE ZONES
    for (int k=0; k<3; k++) {
        zones[k].update();
    }
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
    for (int k=0; k<3; k++) {
        zones[k].draw();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){
    
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
    for (int i = 0; i < bufferSize; i++){
        
        lAudioIn[i]=input[i*nChannels];
        rAudioIn[i]=input[i*nChannels +1];
    }
}


//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs &touch){
    
}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotFocus(){
    
}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){
    
}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}

