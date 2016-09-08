//
//  ofxAVUIZoneSequencer.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIZoneSequencer_h
#define ofxAVUIZoneSequencer_h

#define SEQUENCE_DURATION   120   //counts

#include "ofMain.h"
#include "ofEvents.h"
#include "ofxAVUIEvents.h"

class ofxAVUIZoneSequencer {
    
    public:
        ofxAVUIZoneSequencer();
        ~ofxAVUIZoneSequencer();
        void setup(int _x, int _y, int _width, int _height);
        void update();
        void draw();
        void run();
        void stop();
        void reset();
        void addEvent(ofMouseEventArgs & args);
        void unregisterMouse();
        void registerMouse();

        void mouseMoved(ofMouseEventArgs & args);
        void mousePressed(ofMouseEventArgs & args);
        void mouseDragged(ofMouseEventArgs & args);
        void mouseReleased(ofMouseEventArgs & args);
        void mouseScrolled(ofMouseEventArgs & args) {}
        void mouseEntered(ofMouseEventArgs & args) {}
        void mouseExited(ofMouseEventArgs & args) {}

        ofRectangle shape;      //zone shape
        long        counter;
        bool        running;

        //list of events
        struct eventInfo {
            ofMouseEventArgs    mouseArgs;
            int                 time;
            bool                active;
        };
        vector<eventInfo> eventList;
    
        ofxAVUIEvents       sequencerEvents;
        ofMouseEventArgs    mouseArgs;
};


#endif /* ofxAVUIZoneSequencer_h */
