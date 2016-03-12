//
//  ofxAVUISoundFxBase.h
//
//  Part of ofxAVUI addon. Developed by Nuno Correia and Borut Kumperscak in 2016.
//  https://github.com/AVUIs/ofxAVUI
//

#ifndef ofxAVUISoundFxBase_h
#define ofxAVUISoundFxBase_h

#include "ofMain.h"

class ofxAVUISoundFxBase {

public:
    ofxAVUISoundFxBase();
    virtual ~ofxAVUISoundFxBase();
    void setup(string _fxName, bool _enabledByDefault, string _paramName1, float _min1, float _max1, float _default1,
                                                       string _paramName2, float _min2, float _max2, float _default2);
    void toggle(bool _enabled);
    bool isEnabled();
    void setParameter(string param, float _val);
    string getName();
    ofParameter<float> *getParameter(int _paramNo);
    ofParameter<bool> *getToggle();
    void param1Changed(float & _param1);
    void param2Changed(float & _param2);
    void toggled(bool & _enabled);
    
    virtual double compute(double _sampleIn) = 0;   //every child needs to implement this
    
protected:
    string  name;
    ofParameter<float>  param1;
    ofParameter<float>  param2;
    ofParameter<bool>   enabled;
};

#endif /* ofxAVUISoundFxBase_h */
