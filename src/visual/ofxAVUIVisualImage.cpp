//
//  ofxAVUIVisualImage.cpp
//  Developed by Berkan Eskikaya
// 
//  Part of ofxAVUI addon, developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#include "ofxAVUIVisualImage.h"

ofxAVUIVisualImage::ofxAVUIVisualImage(string path, int _alpha){
  image.load(path);
  alpha = _alpha;
}

ofxAVUIVisualImage::ofxAVUIVisualImage(string path){
  image.load(path);
  alpha = DEFAULT_ALPHA;
}

void ofxAVUIVisualImage::draw(float * buffer, float amplitude){
  ofPushStyle();
  ofSetColor(255,255,255,alpha);
  image.draw(0,0, shape.width, shape.height);

  ofSetColor(visColor);
  for(int i=0; i<myBufferSize; i++){
    float p = i / (float)(myBufferSize);
    float y1 = shape.height/2;
    float y2 = buffer[i] * (shape.height);
    float x = p * shape.width;
    float rectWidth = shape.width/myBufferSize;
    ofDrawRectangle(x, y1, rectWidth, y2);
  }
  
  ofPopStyle();
}
