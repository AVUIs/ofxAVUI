//
//  ofxAVUIZone.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumpersck in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIZone_h
#define ofxAVUIZone_h

#include "ofMain.h"
#include "ofxMaxim.h"

#include "ofxAVUIBase.h"
#include "ofxAVUIXYPad.h"
#include "ofxAVUIButton.h"
#include "ofxAVUIToggle.h"
#include "ofxAVUIEmpty.h"
#include "ofxAVUISlider.h"
#include "ofxAVUIRangeSlider.h"

#include "ofxAVUIVisualBase.h"
#include "ofxAVUIVisualWave.h"
#include "ofxAVUIVisualBars.h"
#include "ofxAVUIVisualCircles.h"
#include "ofxAVUIVisualLissajous.h"
#include "ofxAVUIVisualGrid.h"

#include "ofxAVUIZonePlayer.h"
#include "ofxAVUISoundFxBase.h"

class ofxAVUIZone {
	
public:
	ofxAVUIZone();
	~ofxAVUIZone();
    //zone is defined by position and width in pixels, the UI and visual elements are then stacked down from position
    ofxAVUIZone* setup(string _name, int _x, int _y, int _width, ofColor _backgroundColor, ofColor _foregroundColor, string _sound, int _bufferSize);
    void update();
    void draw();
    
    //sound
    void play(int pos);
    double getOutput(int channel);

    //event handlers for parameters
//    void nullChanged(char &_null);    //debug
    void pitchChanged(float &_pitch);
    void volumeChanged(float &_volume);
    void loopingChanged(bool &_looping);
    void triggerReceived(bool &_trigger);
    void toggleReceived(bool &_toggle);
    void frequencyChanged(float &_frequency);
    void resonanceChanged(float &_resonance);
    void filterOnChanged(bool &_filterOn);
    void sizeChanged(float &_size);
    void feedbackChanged(float &_feedback);
    void delayOnChanged(bool &_delayOn);

    //UI
    void addUI(ofxAVUIBase * _element, float _pixelHeight); //UI elements are stacked top->down
    void addSoundFx(ofxAVUISoundFxBase * _fxElement);
    void addVisual(ofxAVUIVisualBase * _element, ofColor visColor);
    void addParameterFloat(string _paramName, float _min, float _max, float _value);
    void addParameterBool(string _paramName, bool _val);
    void syncParameters();    //sync UI with parameters
    ofParameter<float> getParamValueFloat(string _param);
    ofParameter<bool> getParamValueBool(string _param);

private:
    bool                loaded;     //zone and sound initialised
    bool                synced;     //UI synced with parameters, happend at 1st draw
    ofRectangle         shape;      
    string              name;
    ofxAVUIZonePlayer   player;
    ofColor             fgColor, bgColor;
    ofFbo               FBO;
    //properties
    ofParameter<char>       devNull; //we don't use first parameter in the group, as it is returned by parameterGroup->get(param1) whenever param1 doesn't match any of the parameter namess
    ofParameter<float>  pitch; //speed;
    ofParameter<float>  volume; //amplitude;
    ofParameter<bool>   looping;
    ofParameter<bool>   trigger;
    ofParameter<bool>   toggle;
    ofParameter<float>  frequency;
    ofParameter<float>  resonance;
    ofParameter<float>  size;
    ofParameter<float>  feedback;
    ofParameterGroup    soundProperties;
    
    std::vector <ofxAVUIBase *> uis;
    std::vector <ofxAVUIVisualBase *> visuals;
};


#endif /* ofxAUVIZone_h */
