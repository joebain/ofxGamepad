#include "ofxGamepadAndroid.h"

#ifdef TARGET_ANDROID


ofxGamepadAndroid::ofxGamepadAndroid(int _deviceId) : ofxGamepad() {
    deviceId = _deviceId;

//    setNumAxis(6);
//    setNumButtons(13);
    setNumAxis(20);
    setNumButtons(108); // not really 108 but this is the top index
    name = "Ouya " + _deviceId;
    type = GAMEPAD_OUYA;
//    axisMinVal = 0;
//    axisMaxVal = 255;
}

ofxGamepadAndroid::~ofxGamepadAndroid() {
}

void ofxGamepadAndroid::update() {
}

void ofxGamepadAndroid::exit() {
}

#endif
