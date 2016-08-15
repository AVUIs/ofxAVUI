//
//  ofxAVUIDropDown.cpp
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIDropDown.h"

ofxAVUIDropDown::ofxAVUIDropDown(string _title, string _paramSelection){
    title = _title;
    paramSelection = _paramSelection;
    itemHeight = 35;
    resetItems();
}

ofxAVUIDropDown::~ofxAVUIDropDown(){

}

void ofxAVUIDropDown::setTakeoverPosition(int _x, int _y, int _width, int _height) {
    takeoverShape.x = _x;
    takeoverShape.y = _y;
    takeoverShape.width = _width;
    takeoverShape.height = _height;

    int itemsPerHeight = takeoverShape.height / itemHeight;
    itemHeight = takeoverShape.height / itemsPerHeight;
    itemsPerPage = itemsPerHeight - 2;      //top and bottom items reserved for nav
    numPages = items.size() / itemsPerPage;
    if (items.size()%itemsPerPage > 0) numPages+=1;
}

void ofxAVUIDropDown::resetItems() {
    items.clear();
    selection = -1;
    currentPage = 0;
    numPages = 0;
}

string ofxAVUIDropDown::fitString(string _stringToFit){
    int maxWidthChar = (shape.width-10) / getBitmapStringBoundingBox("8").width;
    if (_stringToFit.length() > maxWidthChar) _stringToFit = _stringToFit.substr(0, maxWidthChar-2) + "..";
    return _stringToFit;
}

void ofxAVUIDropDown::addItem(string _item) {
    items.push_back(fitString(_item));
    if (selection<0) selection = 0;   //set default selection when at least 1 item added
}

void ofxAVUIDropDown::draw(){
    if (takeover && takeoverShape.x==0 && takeoverShape.y==0 && takeoverShape.width==0 && takeoverShape.height==0) {
        cout << "WARNING: Takeover not possible without zone.update() invoked before zone.draw()" << endl;
        takeover = false;
    } else if (takeover) {
        ofPushStyle();
        ofSetColor(bgColor);
        ofDrawRectangle(takeoverShape.x,takeoverShape.y,takeoverShape.width,takeoverShape.height);
        ofSetColor(fgColor);
        drawContour();
        //current selection if any
        int mid = itemHeight/2 + getBitmapStringBoundingBox("1").height/2;
        if (selection!=-1)  ofDrawBitmapString(fitString("< " + items[selection]), takeoverShape.x + 15, takeoverShape.y + mid);
//        ofDrawLine(takeoverShape.x, takeoverShape.y + itemHeight, takeoverShape.x + shape.width, takeoverShape.y + itemHeight);
            ofDrawLine(takeoverShape.x, takeoverShape.y + itemHeight, takeoverShape.x + takeoverShape.width*0.25, takeoverShape.y + itemHeight);
            ofDrawLine(takeoverShape.x + takeoverShape.width*0.75, takeoverShape.y + itemHeight, takeoverShape.x + takeoverShape.width, takeoverShape.y + itemHeight);
        //other items in current page
        int itemsCount = itemsPerPage;
        if ((currentPage==numPages-1) && items.size()%itemsPerPage > 0) itemsCount = items.size()%itemsPerPage;
        for(std::size_t i = 0; i < itemsCount; i++){
            ofDrawBitmapString(items[i+currentPage*itemsPerPage], takeoverShape.x + 5, takeoverShape.y + (i+1)*itemHeight+mid);
//            ofDrawLine(takeoverShape.x, takeoverShape.y + (i+2)*itemHeight, takeoverShape.x + takeoverShape.width*0.25, takeoverShape.y + (i+2)*itemHeight);
//            ofDrawLine(takeoverShape.x + takeoverShape.width*0.75, takeoverShape.y + (i+2)*itemHeight, takeoverShape.x + takeoverShape.width, takeoverShape.y + (i+2)*itemHeight);
        }
        //pages nav
//        ofDrawLine(takeoverShape.x, takeoverShape.y + (itemsPerPage+1)*itemHeight, takeoverShape.x + shape.width, takeoverShape.y + (itemsPerPage+1)*itemHeight);
        ofDrawLine(takeoverShape.x, takeoverShape.y + (itemsPerPage+1)*itemHeight, takeoverShape.x + takeoverShape.width*0.25, takeoverShape.y + (itemsPerPage+1)*itemHeight);
        ofDrawLine(takeoverShape.x + takeoverShape.width*0.75, takeoverShape.y + (itemsPerPage+1)*itemHeight, takeoverShape.x + takeoverShape.width, takeoverShape.y + (itemsPerPage+1)*itemHeight);
        ofDrawBitmapString("<", takeoverShape.x + 15, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
        ofDrawBitmapString(">", takeoverShape.x + takeoverShape.width-15-getBitmapStringBoundingBox(">").width, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
        ofDrawBitmapString(ofToString(currentPage+1)+"/"+ofToString(numPages), takeoverShape.x + (takeoverShape.width-getBitmapStringBoundingBox("8/8").width)/2, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
        ofPopStyle();
    } else {
        ofPushStyle();
        ofSetColor(bgColor);
        ofDrawRectangle(shape.x,shape.y,shape.width,shape.height);
        ofSetColor(fgColor);
        drawContour();
//        drawTitle();
        ofDrawBitmapString(fitString("> " + items[selection]), shape.x + 15, shape.y + shape.height - 5);

        ofPopStyle();
    }
}

void ofxAVUIDropDown::mouseMoved(ofMouseEventArgs & args) {
}

void ofxAVUIDropDown::mousePressed(ofMouseEventArgs & args) {
}
void ofxAVUIDropDown::mouseDragged(ofMouseEventArgs & args) {
}

void ofxAVUIDropDown::mouseReleased(ofMouseEventArgs & args) {
    if (!takeover && shape.inside(args.x, args.y)) {
        takeover = true;
    } else if (takeover && takeoverShape.inside(args.x, args.y)) {
        if (ofRectangle(takeoverShape.x, takeoverShape.y, takeoverShape.width, itemHeight*1.2).inside(args.x, args.y)) {
            takeover = false;
        } else if (ofRectangle(takeoverShape.x, takeoverShape.y + takeoverShape.height-itemHeight*1.2, 45, itemHeight*1.2).inside(args.x, args.y)) {
            currentPage--;
            if (currentPage < 0) currentPage = 0;
        } else if (ofRectangle(takeoverShape.x + takeoverShape.width - 45, takeoverShape.y + takeoverShape.height-itemHeight*1.2, 45, itemHeight*1.2).inside(args.x, args.y)) {
            currentPage++;
            if (currentPage >= numPages) currentPage = numPages-1;
        } else {
            int itemsCount = itemsPerPage;
            if ((currentPage==numPages-1) && items.size()%itemsPerPage > 0) itemsCount = items.size()%itemsPerPage;
            for (int i=0;i<itemsCount;i++) if (ofRectangle(takeoverShape.x, takeoverShape.y + itemHeight*1.2 + itemHeight*i, takeoverShape.width, itemHeight).inside(args.x, args.y)) {
                selection = i+currentPage*itemsPerPage;
                soundProperties->getInt(paramSelection) = selection;
                takeover = false;
            }
        }
    }
}

void ofxAVUIDropDown::mouseScrolled(ofMouseEventArgs & args) {
}
