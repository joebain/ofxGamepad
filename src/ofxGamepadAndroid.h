#ifndef OFXGAMEPADANDROID_H
#define OFXGAMEPADANDROID_H

#include "ofMain.h"

#ifdef TARGET_ANDROID

#include "ofxGamepad.h" // Base class: ofxGamepad

class ofxGamepadAndroid : public ofxGamepad
{

public:
	int deviceId;


	ofxGamepadAndroid(int deviceId);
	~ofxGamepadAndroid();
	void update();
	void exit();
private:

};

#endif //TARGET ANDROID

#endif // OFXGAMEPADANDROID_H
