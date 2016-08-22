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
    virtual void setTakeoverPosition(int _x, int _y, int _width, int _height);
    void addItem(string _item);
    string fitString(string _stringToFit);
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
    float       itemHeight;
    int         currentPage;
    int         numPages;
    int         itemsPerPage;
    bool        topPositionSpecial;
};

#endif /* ofxAVUIDropDown_h */
