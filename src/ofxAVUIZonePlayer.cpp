//
//  ofxAVUIZonePlayer.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIZonePlayer.h"

ofxAVUIZonePlayer::ofxAVUIZonePlayer() {
}

ofxAVUIZonePlayer::~ofxAVUIZonePlayer() {
}

void ofxAVUIZonePlayer::setup(string _sound, int bufferSize){
    myBufferSize=bufferSize;
    buffer = new float[bufferSize];
    sound.load(ofToDataPath(_sound));
    //properties
    speed=1;
    amplitude=0.5;
    looping=false;
    playing = false;
    sampleOut = 0;
}

void ofxAVUIZonePlayer::reset(){
    sound.clear();
    sound.reset();      //reset position to start as we dont know the upcoming sound's size
}

void ofxAVUIZonePlayer::addSoundFx(ofxAVUISoundFxBase * _fxElement) {
    fxs.push_back(_fxElement);
}

void ofxAVUIZonePlayer::trigger(float _speed, float _amplitude){
    sampleTrigger = 1;
    speed = _speed;
    amplitude = _amplitude;
    playing = true;
    stopping = false;
}

void ofxAVUIZonePlayer::stop(){
    stopping = true;
}

void ofxAVUIZonePlayer::play(int pos, double pan){
    if (playing) {
        if (looping) {
            sampleOut=envelope.ar(sound.play(speed), 0.1, (stopping?0.9999:1), 1, sampleTrigger);
        } else {
            if (sampleTrigger==1) sound.trigger();
//            sampleOut=envelope.ar((speed<0?sound.play(speed):sound.playOnce(speed)), 0.1, (stopping?0.9999:1), 1, sampleTrigger);
            sampleOut=envelope.ar(sound.playOnce(speed), 0.1, (stopping?0.9999:1), 1, sampleTrigger);
        }
    
        for(std::size_t i = 0; i < fxs.size(); i++){
            if (fxs[i]->isEnabled()) sampleOut = fxs[i]->compute(sampleOut);
        }
        
        buffer[pos]=sampleOut;
    }   else {
        buffer[pos]=0;
    }

    bus.stereo(sampleOut*amplitude, outputs, pan);
    sampleTrigger = 0;
}

