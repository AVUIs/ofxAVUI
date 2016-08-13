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
    itemHeight = 30;
    resetItems();
}

ofxAVUIDropDown::~ofxAVUIDropDown(){

}

void ofxAVUIDropDown::resetItems() {
    items.clear();
    selection = -1;
    currentPage = 0;
    numPages = 0;
}

void ofxAVUIDropDown::addItem(string _item) {
    int maxWidthChar = (shape.width-30) / getBitmapStringBoundingBox("8").width;
    if (_item.length() > maxWidthChar) _item = _item.substr(0, maxWidthChar-1) + "..";
    items.push_back(_item);
    if (selection<0) selection = 0;   //do we need to set default selection?
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
//        drawTitle(); //no title for takover
        //current selection if any
        ofDrawLine(takeoverShape.x + 15,
                takeoverShape.y + (itemHeight+getBitmapStringBoundingBox("1").height)/2+4,
                takeoverShape.x + shape.width - 15,
                takeoverShape.y + (itemHeight+getBitmapStringBoundingBox("1").height)/2+4);
        if (selection!=-1)
            ofDrawBitmapString(items[selection],
                    takeoverShape.x + 15,
                    takeoverShape.y + (itemHeight+getBitmapStringBoundingBox("1").height)/2);
        //other items in current page
        //this is recalucated every cycle, might move somewhere else..
        itemsPerPage = (takeoverShape.height - 2*itemHeight) / itemHeight;
        numPages = items.size() / itemsPerPage;
        if (items.size()%itemsPerPage > 0) numPages+=1;
        int itemsCount = itemsPerPage;
        if ((currentPage==numPages-1) && items.size()%itemsPerPage > 0) itemsCount = items.size()%itemsPerPage;
        for(std::size_t i = 0; i < itemsCount; i++){
            ofDrawBitmapString(items[i+currentPage*itemsPerPage],
                    takeoverShape.x + 15,
                    takeoverShape.y + (2+i)*itemHeight-(itemHeight-getBitmapStringBoundingBox("1").height)/2);
        }
        
        //pages nav
        ofDrawLine(takeoverShape.x + 15,
                takeoverShape.y + takeoverShape.height-(itemHeight-getBitmapStringBoundingBox("1").height)/2-getBitmapStringBoundingBox("1").height-2,
                takeoverShape.x + shape.width - 15,
                takeoverShape.y + takeoverShape.height-(itemHeight-getBitmapStringBoundingBox("1").height)/2-getBitmapStringBoundingBox("1").height-2);
        ofDrawBitmapString("<",
                takeoverShape.x + 15,
                takeoverShape.y + takeoverShape.height-(itemHeight-getBitmapStringBoundingBox("1").height)/2);
        ofDrawBitmapString(">",
                takeoverShape.x + takeoverShape.width-15-getBitmapStringBoundingBox(">").width,
                takeoverShape.y + takeoverShape.height-(itemHeight-getBitmapStringBoundingBox("1").height)/2);
        ofDrawBitmapString(ofToString(currentPage+1)+"/"+ofToString(numPages),
                takeoverShape.x + (takeoverShape.width-getBitmapStringBoundingBox("8/8").width)/2,
                takeoverShape.y + takeoverShape.height-(itemHeight-getBitmapStringBoundingBox("1").height)/2);
        ofPopStyle();
    } else {
        ofPushStyle();
        ofSetColor(bgColor);
        ofDrawRectangle(shape.x,shape.y,shape.width,shape.height);
        ofSetColor(fgColor);
        drawContour();
        drawTitle();
        ofDrawLine(shape.x + 15, shape.y + shape.height/2+4, shape.x + shape.width - 15, shape.y + shape.height/2+4);
        if (selection!=-1)
            ofDrawBitmapString(items[selection], shape.x + 15, shape.y + shape.height/2);
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
