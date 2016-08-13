//
//  ofxAVUIDropDown.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUIDropDown_h
#define ofxAVUIDropDown_h

#include "ofMain.h"
#include "ofxAVUIBase.h"


class ofxAVUIDropDown : public ofxAVUIBase {
public:
    ofxAVUIDropDown() {};
    ofxAVUIDropDown(string _title, string _paramSelection);
    virtual ~ofxAVUIDropDown();
    void addItem(string _item);
    void resetItems();
    void mouseMoved(ofMouseEventArgs & args);
    void mousePressed(ofMouseEventArgs & args);
    void mouseDragged(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);
    void mouseScrolled(ofMouseEventArgs & args);

    void draw();

private:
    string      paramSelection;
    std::vector <string> items;
    int         selection;
    int         itemHeight;
    int         currentPage;
    int         numPages;
    int         itemsPerPage;
};

#endif /* ofxAVUIDropDown_h */
