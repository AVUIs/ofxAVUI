//
//  ofxAVUIEvents.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIEvents_h
#define ofxAVUIEvents_h

#include "ofRectangle.h"
#include "ofEvents.h"

class ofxAVUIEvents : public ofEventArgs {
    
    public:
    
        ofxAVUIEvents() {}
        void addRestrictionRect(ofRectangle _rect);
    
        static ofEvent<ofMouseEventArgs> sequencerEvent;
        static std::vector<ofRectangle>  restrictions;
};


#endif /* ofxAVUIEvents_h */
