//
//  ofxAVUIZonePlayer.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIZonePlayer_h
#define ofxAVUIZonePlayer_h

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAVUISoundFxBase.h"
//#include "ofxAVUISoundFxFilter.h"
//#include "ofxAVUISoundFxDelay.h"

class ofxAVUIZonePlayer {
    
    public:
        ofxAVUIZonePlayer();
        ~ofxAVUIZonePlayer();
        void setup(string _sound, int bufferSize);
        void trigger(float _speed, float _amplitude);
        void stop();
        void filter(float _val1, float _val2);
        void delay(float _val1, float _val2);
        void play(int pos, double pan);
        void reset();

        void addSoundFx(ofxAVUISoundFxBase * _fxElement);
        void sendValue(string _param, float _val);
        
        //objects
        maxiEnv envelope;
        maxiSample sound;
        maxiMix bus;
    
        //audio streams
        double outputs[2];
        double sampleOut;
        double filtered;
        double delayed;
        float * buffer;
        int myBufferSize;

        //properties
        double speed;
        double amplitude;
        bool looping;
        bool playing;
        bool stopping;
        int sampleTrigger;

        //list of fx
        std::vector <ofxAVUISoundFxBase *> fxs;
};


#endif /* ofxAVUIZonePlayer_h */
