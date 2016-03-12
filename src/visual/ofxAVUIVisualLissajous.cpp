//
//  ofxAVUIVisualLissajous.cpp
//  AVUIApp2
//
//  Created by jayson on 12/03/2016.
//
//

#include "ofxAVUIVisualLissajous.h"

ofxAVUIVisualLissajous::ofxAVUIVisualLissajous()
{
    syphonOut.setName("ofxAVUIVisual");
    
    pointCount = 500;
    
    offset = 0.0;
    
    
    smooth = 0.75;
    totalAmplitude = 0.0;
}

void ofxAVUIVisualLissajous::draw(float * buffer, float amplitude)
{
    
    visualFbo.allocate(shape.width, shape.height);
    
    visualFbo.begin();
    ofClear(0,0,0);
    
    ofPushStyle();
    // Calculate total amplitude
    float newAmplitude = 0.0;
    for(int i = 0; i < myBufferSize; i++)
    {
        newAmplitude += abs(buffer[i]) * amplitude;
    }
    newAmplitude /= (float)myBufferSize;
    
    totalAmplitude = totalAmplitude * smooth + newAmplitude * (1.0-smooth);
    
    float freqX =ofMap(totalAmplitude, 0, 0.2, 1, 8 * (shape.height/ shape.width),true);
    float freqY =ofMap(totalAmplitude, 0, 0.2, 1, 8 * (shape.width/ shape.height),true);
    
    
    float modFreqX = 5.0 * amplitude;
    float modFreqY = 5.0 * amplitude;
    
    ofSetColor(visColor);
    ofNoFill();
    ofBeginShape();
    
    for(float angle = 0.0; angle <= TWO_PI; angle += (TWO_PI / (float)pointCount))
    {
        float x = sin(angle * freqX + offset) * cos(angle * modFreqX);
        float y = sin(angle * freqY + offset) * cos(angle * modFreqY+ offset);
        
        x = shape.width/2 + x * (shape.width/2  - 30);
        y = shape.height/2+ y * (shape.height/2 - 30);
        
        ofVertex(x,y);
        
    }
    ofEndShape();
    
    offset+= DEFAULT_SPEED + totalAmplitude * 0.1;
    ofPopStyle();
    
    visualFbo.end();
    visualFbo.draw(0,0);
    syphonOut.publishTexture(&visualFbo.getTexture());
}
