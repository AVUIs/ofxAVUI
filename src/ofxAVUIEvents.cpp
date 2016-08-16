//
//  ofxAVUIEvents.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIEvents.h"

ofEvent <ofMouseEventArgs> ofxAVUIEvents::sequencerEvent;
std::vector<ofRectangle>   ofxAVUIEvents::restrictions;

void ofxAVUIEvents::addRestrictionRect(ofRectangle _rect) {
    restrictions.push_back(_rect);
}
