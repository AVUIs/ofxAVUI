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
    itemHeight = ofGetHeight()/22;
    resetItems();
    topPositionSpecial = false;
    resetItems();
}

ofxAVUIDropDown::~ofxAVUIDropDown(){

}

void ofxAVUIDropDown::setTakeoverPosition(int _x, int _y, int _width, int _height) {
    takeoverShape.x = _x;
    takeoverShape.y = _y;
    takeoverShape.width = _width;
    takeoverShape.height = _height;
    topPositionSpecial = false;
    if (shape.y == takeoverShape.y) {  //top of the zone? => special draw
        topPositionSpecial = true;
    }
    
    int itemsPerHeight = (takeoverShape.height - (topPositionSpecial?shape.height:0)) / itemHeight;
    itemHeight = (takeoverShape.height - (topPositionSpecial?shape.height:0)) / itemsPerHeight;
    itemsPerPage = itemsPerHeight - (topPositionSpecial?1:2);      //top and bottom items reserved for nav
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
    float padding = ofGetHeight()/75;
    int maxWidthChar = (shape.width-padding) / (customFont ? uifont->getStringBoundingBox("8", 0, 0).width : getBitmapStringBoundingBox("8").width);
    if (_stringToFit.length() > maxWidthChar) _stringToFit = _stringToFit.substr(0, maxWidthChar-2) + "..";
    return _stringToFit;
}

void ofxAVUIDropDown::addItem(string _item) {
    items.push_back(fitString(_item));
    if (selection<0) selection = 0;   //set default selection when at least 1 item added
}

void ofxAVUIDropDown::draw(){
    float padding = ofGetHeight()/150;
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
        int mid = itemHeight/2 + (customFont ? uifont->getStringBoundingBox("1",0,0).height : getBitmapStringBoundingBox("1").height) / 2;
        if (selection!=-1)  {
            if (!customFont) ofDrawBitmapString(fitString("< " + items[selection]), takeoverShape.x + 5, (topPositionSpecial?(shape.y + shape.height - 5):(takeoverShape.y + mid)));
                else uifont->drawString(fitString("< " + items[selection]), takeoverShape.x + padding, (topPositionSpecial?(shape.y + shape.height - padding):(takeoverShape.y + mid)));
            if (!topPositionSpecial) {  //draw top line if not top of the zone
                ofDrawLine(takeoverShape.x, takeoverShape.y + itemHeight, takeoverShape.x + takeoverShape.width*0.25, takeoverShape.y + itemHeight);
                ofDrawLine(takeoverShape.x + takeoverShape.width*0.75, takeoverShape.y + itemHeight, takeoverShape.x + takeoverShape.width, takeoverShape.y + itemHeight);
            }
            //other items in current page
            int itemsCount = itemsPerPage;
            if ((currentPage==numPages-1) && items.size()%itemsPerPage > 0) itemsCount = items.size()%itemsPerPage;
            for(std::size_t i = 0; i < itemsCount; i++){
                if (!customFont) ofDrawBitmapString(items[i+currentPage*itemsPerPage], takeoverShape.x + 5, takeoverShape.y + (i+1)*itemHeight+mid);
                    else uifont->drawString(items[i+currentPage*itemsPerPage], takeoverShape.x + padding, takeoverShape.y + (i+1)*itemHeight+mid);
//            ofDrawLine(takeoverShape.x, takeoverShape.y + (i+2)*itemHeight, takeoverShape.x + takeoverShape.width*0.25, takeoverShape.y + (i+2)*itemHeight);
//            ofDrawLine(takeoverShape.x + takeoverShape.width*0.75, takeoverShape.y + (i+2)*itemHeight, takeoverShape.x + takeoverShape.width, takeoverShape.y + (i+2)*itemHeight);
            }
        }
        //pages nav
//        ofDrawLine(takeoverShape.x, takeoverShape.y + (itemsPerPage+1)*itemHeight, takeoverShape.x + shape.width, takeoverShape.y + (itemsPerPage+1)*itemHeight);
        ofDrawLine(takeoverShape.x, takeoverShape.y + (itemsPerPage+1)*itemHeight, takeoverShape.x + takeoverShape.width*0.25, takeoverShape.y + (itemsPerPage+1)*itemHeight);
        ofDrawLine(takeoverShape.x + takeoverShape.width*0.75, takeoverShape.y + (itemsPerPage+1)*itemHeight, takeoverShape.x + takeoverShape.width, takeoverShape.y + (itemsPerPage+1)*itemHeight);
        if (!customFont) ofDrawBitmapString("<", takeoverShape.x + 15, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
            else uifont->drawString("<", takeoverShape.x + padding*3, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
        if (!customFont) ofDrawBitmapString(">", takeoverShape.x + takeoverShape.width-15-getBitmapStringBoundingBox(">").width, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
            else uifont->drawString(">", takeoverShape.x + takeoverShape.width-padding*3-uifont->getStringBoundingBox(">",0,0).width, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
        if (!customFont) ofDrawBitmapString(ofToString(currentPage+1)+"/"+ofToString(numPages), takeoverShape.x + (takeoverShape.width-getBitmapStringBoundingBox("8/8").width)/2, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
            else uifont->drawString(ofToString(currentPage+1)+"/"+ofToString(numPages), takeoverShape.x + (takeoverShape.width-uifont->getStringBoundingBox("8/8",0,0).width)/2, takeoverShape.y + (itemsPerPage+1)*itemHeight + mid);
        ofPopStyle();
    } else {
        ofPushStyle();
        ofSetColor(bgColor);
        ofDrawRectangle(shape.x,shape.y,shape.width,shape.height);
        ofSetColor(fgColor);
        drawContour();
//        drawTitle();
        if (selection!=-1) {
            if (!customFont) ofDrawBitmapString(fitString("> " + items[selection]), shape.x + 5, shape.y + shape.height - 5);
                else uifont->drawString(fitString("> " + items[selection]), shape.x + padding, shape.y + shape.height - padding);
        }
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
    if (!takeover && selection>-1 && shape.inside(args.x, args.y)) {
        takeover = true;
    } else if (takeover  && selection>-1 && takeoverShape.inside(args.x, args.y)) {
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
