//
//  ofxAVUIZone.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIZone.h"

const string ofxAVUIZone::DEV_NULL = "null";
const string ofxAVUIZone::VOLUME = "volume";
const string ofxAVUIZone::PITCH = "pitch";
const string ofxAVUIZone::TOGGLE_LOOPING = "toggleLooping";
const string ofxAVUIZone::TRIGGER_PLAY = "triggerPlay";
const string ofxAVUIZone::SELECTION = "selection";
const string ofxAVUIZone::TOGGLE_SEQUENCER = "toggleSequencer";

ofxAVUIZone::ofxAVUIZone() {
    name = "";
    shape.x = 0;
    shape.y = 0;
    shape.width = 0;
    shape.height = 0;
    loaded = false;
    synced = false;
    takenOver = false;
    uiTakingOver = -1;
}

ofxAVUIZone::~ofxAVUIZone() {
}

ofxAVUIZone* ofxAVUIZone::setup(string _name, int _x, int _y, int _width, ofColor _backgroundColor, ofColor _foregroundColor,
                                string _sound, int _bufferSize) {
    ofSetCircleResolution(200);
    name = _name;
    shape.x = _x;
    shape.y = _y;
    shape.width = _width;
//    shape.height = _height;
    fgColor = _foregroundColor;
    bgColor = _backgroundColor;
    player.setup(ofToDataPath(_sound), _bufferSize);
    
    soundProperties.add(devNull.set(DEV_NULL, 1.0, 0.0, 2.0));

    soundProperties.add(pitch.set(PITCH, player.speed, 0.0, 2.0));
    pitch.addListener(this,&ofxAVUIZone::pitchChanged);

    soundProperties.add(volume.set(VOLUME, player.amplitude, 0.0, 2.0));
    volume.addListener(this,&ofxAVUIZone::volumeChanged);

    soundProperties.add(looping.set(TOGGLE_LOOPING, player.looping));
    looping.addListener(this,&ofxAVUIZone::loopingChanged);

/*    soundProperties.add(trigger.set(TRIGGER_PLAY, false));
    trigger.addListener(this,&ofxAVUIZone::triggerReceived);
*/
    soundProperties.add(toggle.set(TRIGGER_PLAY, false));
    toggle.addListener(this,&ofxAVUIZone::toggleReceived);

    soundProperties.add(selection.set(SELECTION, -1, -1, 10000));
    selection.addListener(this,&ofxAVUIZone::selectionReceived);

    soundProperties.add(sequencerRunning.set(TOGGLE_SEQUENCER, sequencer.running));
    sequencerRunning.addListener(this,&ofxAVUIZone::sequencerChanged);

//    sequencer.bindProperties(&soundProperties);

    loaded = true;
}

void ofxAVUIZone::loadSound(string _sound, int _bufferSize) {
    player.reset();
    player.sound.load(_sound);  //avoid player.setup() as that resets all parameters, bringing them out of sync with UI
}

void ofxAVUIZone::addSoundFx(ofxAVUISoundFxBase * _fxElement) {
    player.addSoundFx(_fxElement);
    soundProperties.add(*_fxElement->getParameter(0));
    soundProperties.add(*_fxElement->getParameter(1));
    soundProperties.add(*_fxElement->getToggle());
}

void ofxAVUIZone::pitchChanged(float & _pitch){
    player.speed = _pitch;
//    sequencer.addEvent(PITCH, _pitch, ofGetMouseX(), ofGetMouseY());
}

void ofxAVUIZone::volumeChanged(float & _volume){
    player.amplitude = _volume;
//    sequencer.addEvent(VOLUME, _volume, ofGetMouseX(), ofGetMouseY());
}
/*
void ofxAVUIZone::triggerReceived(bool &_trigger){
    player.trigger(pitch, volume);
    cout << "TRIGGER RECEIVED" << endl;
    sequencer.addEvent(TRIGGER_PLAY, _trigger, ofGetMouseX(), ofGetMouseY());
    trigger = false;
}
*/
void ofxAVUIZone::toggleReceived(bool &_toggle){
    if (toggle) player.trigger(pitch, volume); else player.stop();
//    sequencer.addEvent(TRIGGER_PLAY, _toggle, ofGetMouseX(), ofGetMouseY());
}

void ofxAVUIZone::loopingChanged(bool & _looping){
    player.looping = !player.looping;
//    sequencer.addEvent(TOGGLE_LOOPING, _looping, ofGetMouseX(), ofGetMouseY());
}

void ofxAVUIZone::selectionReceived(int &_selection){
//    cout << "selection -> " << selection << endl;
}

void ofxAVUIZone::sequencerChanged(bool & _sequencerRunning){
    if (_sequencerRunning) sequencer.run(); else sequencer.stop();
}


void ofxAVUIZone::update() {
    sequencer.update();

    takenOver = false;
    uiTakingOver = -1;
    for(std::size_t i = 0; i < uis.size(); i++){
        if (uis[i]->takingOver()) {
            takenOver = true;
            uiTakingOver = i;
            uisUnregisterMouse(i);
            uis[i]->setTakeoverPosition(shape.x, shape.y, shape.width, shape.height);
            break;
        }
    }
    if (!takenOver) {
        uisRegisterMouse();
    }
}

//void ofxAVUIZone::drawVisuals() {
//    if (!synced) syncParameters();
//    FBO.begin();
//        ofClear(255,255,255, 0);
//        ofPushStyle();
//        for(std::size_t i = 0; i < visuals.size(); i++){
//            if (loaded) visuals[i]->draw(player.buffer, player.amplitude);
//        }
//        ofPopStyle();
//    FBO.end();
//    FBO.draw(shape.x, shape.y);
//}

void ofxAVUIZone::draw() {
    if (!synced) syncParameters();
    ofPushStyle();
    ofSetLineWidth(1);
    if (takenOver) {
        uis[uiTakingOver]->draw();
    } else {
        for(std::size_t i = 0; i < uis.size(); i++){
            uis[i]->draw();
        }
    }
    sequencer.draw();
    FBO.begin();
        ofClear(255,255,255, 0);
        for(std::size_t i = 0; i < visuals.size(); i++){
            if (loaded) visuals[i]->draw(player.buffer, player.amplitude);
        }
        ofPopStyle();
    FBO.end();
    FBO.draw(shape.x, shape.y);
}

ofTexture &ofxAVUIZone::getVisualTexture() {
    return FBO.getTexture();
}

void ofxAVUIZone::syncParameters() {
    for(std::size_t i = 0; i < uis.size(); i++){
        uis[i]->update();
    }
    for(std::size_t i = 0; i < visuals.size(); i++){
        visuals[i]->setPosition(shape.x, shape.y, shape.width, shape.height);   //needed if we add a visual first and then the UIs
    }

    FBO.allocate(shape.width, shape.height, GL_RGBA);    //doing this here so we do it just once
    FBO.setUseTexture(true);
    synced = true;
}

void ofxAVUIZone::uisUnregisterMouse(int _exception) {
    for(std::size_t i = 0; i < uis.size(); i++){
        if (i!=_exception) uis[i]->unregisterMouse();
    }
}

void ofxAVUIZone::uisRegisterMouse() {
    for(std::size_t i = 0; i < uis.size(); i++){
        uis[i]->registerMouse();
    }
}

ofParameter<float> ofxAVUIZone::getParamValueFloat(string _param) {
    return soundProperties.getFloat(_param);
}

ofParameter<bool> ofxAVUIZone::getParamValueBool(string _param) {
    return soundProperties.getBool(_param);
}

ofParameter<int> ofxAVUIZone::getParamValueInt(string _param) {
    return soundProperties.getInt(_param);
}

void ofxAVUIZone::play(int pos) {
    if (loaded) player.play(pos, 0.5);
}

double ofxAVUIZone::getOutput(int channel) {
    return player.outputs[channel];
}

void ofxAVUIZone::addParameterFloat(string _paramName, float _min, float _max, float _value) {
    ofParameter<float>  param;
    param.set(_paramName, _value, _min, _max);
    soundProperties.add(param);
}

void ofxAVUIZone::addParameterBool(string _paramName, bool _val) {
    ofParameter<bool>  param;
    param.set(_paramName, _val);
    soundProperties.add(param);
}

void ofxAVUIZone::addUI(ofxAVUIBase * _element, float _pixelHeight) {
    uis.push_back(_element);
	_element->setPosition(shape.x, shape.y + shape.height, shape.width, _pixelHeight); //use previous zone height as new y pos
    _element->setColor(bgColor, fgColor);
    _element->bindProperties(&soundProperties);
    shape.height = shape.height + _pixelHeight; //update zone height
    sequencer.setup(shape.x, shape.y, shape.width, shape.height);   //sequencer needs to know about zone height
}

void ofxAVUIZone::addVisual(ofxAVUIVisualBase * _element, ofColor visColor) {
    visuals.push_back(_element);
    _element->setup(player.myBufferSize, visColor);
	_element->setPosition(shape.x, shape.y, shape.width, shape.height);
}



