//
//  ofxAVUIVisualLines.cpp
//  AVUIApp2
//
//  Created by jayson on 12/03/2016.
//
//

#include "ofxAVUIVisualGrid.h"


ofxAVUIVisualGrid::ofxAVUIVisualGrid(){

    
    syphonOut.setName("ofxAVUIVisual");
    visualFbo.allocate(shape.width, shape.height);
    numSquaresX = 20;
    numSquaresY = 20;
}

void ofxAVUIVisualGrid::draw(float * buffer, float amplitude){
  
    visualFbo.begin();
    ofClear(0,0,0);
    ofPushStyle();
    
    ofSetColor(visColor);
    
    
    float xSize = shape.width / numSquaresX;
    float ySize = shape.height / numSquaresY;
    
    for(int y = 0; y < numSquaresY; y++)
    {
        for(int x = 0; x < numSquaresX; x++)
        {
            int indx = ofMap(y * numSquaresX + x, 0, numSquaresX * numSquaresY, 0, myBufferSize);
            ofSetColor(visColor, ofClamp(buffer[indx] * 255.0 * amplitude,0,255));
            ofDrawRectangle(x * xSize, y * ySize, xSize, ySize);
        }
    }
    
    
    ofPopStyle();
    visualFbo.end();
    
    visualFbo.draw(0,0);
    syphonOut.publishTexture(&visualFbo.getTexture());

    
}
