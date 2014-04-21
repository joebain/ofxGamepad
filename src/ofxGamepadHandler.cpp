#include "ofxGamepadHandler.h"

#ifdef USE_OIS
using namespace OIS;
InputManager* oisInputManager;
class tempPad {
public:
	tempPad(JoyStick* s) {
		stick=s;
		handled=false;
	};
	JoyStick* stick;
	bool handled;
};
#endif

ofxGamepadHandler* ofxGamepadHandler::singleton;
bool ofxGamepadHandler::hasSingleton = false;

ofxGamepadHandler::ofxGamepadHandler():hasHotplug(false),hotplugNext(0) {
	ofAddListener(ofEvents().update, this, &ofxGamepadHandler::update);
	ofAddListener(ofEvents().exit, this, &ofxGamepadHandler::exit);
	ofAddListener(onGamepadPlug, this, &ofxGamepadHandler::onPlug);
	ofAddListener(onGamepadUnplug, this, &ofxGamepadHandler::onUnplug);

	updatePadList();
	gamepads.insert(gamepads.end(), gamepadsNew.begin(), gamepadsNew.end());
	gamepadsNew.clear();
}

ofxGamepadHandler::~ofxGamepadHandler() {
}

ofxGamepadHandler* ofxGamepadHandler::get() {
	if(!hasSingleton) {
		singleton=new ofxGamepadHandler();
		hasSingleton=true;
	}
	return singleton;
}

void ofxGamepadHandler::enableHotplug(int interval) {
	hasHotplug=true;
	hotplugInterval=interval;
	startThread(true, false);
}

void ofxGamepadHandler::threadedFunction() {
	while(isThreadRunning()) {

		updatePadList();
		lock();

#ifdef USE_OIS
		gamepads = gamepadsNew;
#else
		if(gamepadsNew.size() > 0) {
			gamepads.insert(gamepads.end(), gamepadsNew.begin(), gamepadsNew.end());
		}
#endif
		unlock();

		gamepadsNew.clear();
		ofSleepMillis(hotplugInterval);
	}
}

void ofxGamepadHandler::updatePadList() {
#ifdef USE_OIS
	try {
		
		ParamList pl;
		InputManager* inputManager=InputManager::createInputSystem(pl);

		gamepadList padsOld=gamepads;
		std::vector<tempPad> sticks;
		//gamepads.clear();

		int numPads = inputManager->getNumberOfDevices(OISJoyStick);
		for( int i = 0; i < numPads; i++ ) {
			JoyStick* js = (JoyStick*)inputManager->createInputObject(OISJoyStick, true );
			sticks.push_back(tempPad(js));
		}

		std::vector<tempPad>::iterator sIt = sticks.begin();
		while(sIt!=sticks.end()) {
			gamepadList::iterator gIt = padsOld.begin();
			while(gIt!=padsOld.end()) {
				if((*sIt).stick->vendor() == (*gIt)->name) {
					ofPtr<ofxGamepadOIS> p = *gIt;
					p->updateJoystick((*sIt).stick);
					gamepadsNew.push_back(p);
					padsOld.erase(gIt);
					(*sIt).handled = true;
					break;
				}
				++gIt;
			}
			++sIt;
		}

		sIt = sticks.begin();
		while(sIt!=sticks.end()) {
			if(!(*sIt).handled)
				gamepadsNew.push_back(ofPtr<ofxGamepadOIS>(new ofxGamepadOIS((*sIt).stick)));
			++sIt;
		}

		lock();
		if(oisInputManager != NULL) {
			oisInputManager->destroyInputSystem(oisInputManager);
		}
		unlock();

		oisInputManager = inputManager;
	} catch(OIS::Exception &ex) {
		stringstream msg;
		msg << "\nException raised on joystick creation: " << ex.eText << std::endl;
		ofLog(OF_LOG_ERROR, msg.str());
	}
#elif defined(TARGET_LINUX)
	//check for joysticks
	ofFile file;
	for(int i=0; i<32; i++) {
		file.open("/dev/input/js"+ofToString(i));
		if(file.exists() && find(activeIDs.begin(), activeIDs.end(), i) == activeIDs.end()) {
			try {
			    	ofxGamepadLinux *pad = new ofxGamepadLinux(file.getAbsolutePath());
				char *name = NULL;
				int n = 0;
				bool found_name = false;
				do {
				    name = KNOWN_CONTROLLER_NAMES[n++]; 
				    if (name == NULL) {
					break;
				    }
				    if (pad->name.compare(name) == 0) {
					found_name = true;
				    }
				} while (!found_name);
				if (found_name) {
				    activeIDs.push_back(i);
				    gamepadsNew.push_back(ofPtr<ofxGamepad>(pad));
//                                if (pad->getNumAxis() < 10 && pad->getNumButtons() < 20) {
//                                    gamepadsNew.push_back(ofPtr<ofxGamepad>(pad));
				} else {
//                                    ofLog(OF_LOG_ERROR) << "Unknown gamepad: " << pad->name;
				}
			} catch(std::exception& err) {
				ofLog(OF_LOG_ERROR, "could not create new gamepad");
			}
		}
	}
#elif defined(TARGET_ANDROID)
#else
	ofLog(OF_LOG_ERROR, "ofxGamepad says: sorry, looks like your system is not supported...");
#endif
}

void ofxGamepadHandler::update(ofEventArgs &args) {
	update();
}

void ofxGamepadHandler::update() {
//        lock();
	gamepadList::iterator it=gamepads.begin();
	while(it!=gamepads.end()) {
		(*it)->update();
		++it;
	}
//        unlock();
}

void ofxGamepadHandler::draw(int x, int y) {
	ofPushMatrix();
	ofTranslate(x, y);
	ofPoint offset(x, y);

	gamepadList::iterator it=gamepads.begin();
	while(it!=gamepads.end()) {
		(*it)->draw(offset.x, offset.y);
		offset+=ofPoint((*it)->drawSize.x+20, 0);
		++it;
	}

	ofPopMatrix();
}

void ofxGamepadHandler::exit(ofEventArgs& arg) {
	gamepadList::iterator it=gamepads.begin();
	while(it!=gamepads.end()) {
		(*it)->exit();
		++it;
	}
	delete this;
}

void ofxGamepadHandler::onPlug(ofxGamepadEvent &ev) {
    ofLog(OF_LOG_VERBOSE) << "game pad plugged!!";
}

void ofxGamepadHandler::onUnplug(ofxGamepadEvent &ev) {
    ofLog(OF_LOG_VERBOSE) << "game pad unplugged!!";
}

ofxGamepad* ofxGamepadHandler::getGamepadById(int id) {
//    ofLog(OF_LOG_VERBOSE) << "getGamepadById " << id;
    for (int i = 0 ; i < gamepads.size() ; i++) {
#if defined(TARGET_ANDROID)
	if (gamepads[i]->id == id || ((ofxGamepadAndroid*)(gamepads[i].get()))->deviceId == id) {
//            ofLog(OF_LOG_VERBOSE) << "returning a pad";
	    return gamepads[i].get();
	}
#else
	if (gamepads[i]->id == id) {
//            ofLog(OF_LOG_VERBOSE) << "returning a pad";
	    return gamepads[i].get();
	}
#endif
    }
    // couldn't find the pad
#if defined(TARGET_ANDROID)
//    ofLog(OF_LOG_VERBOSE) << "making a new android pad";
    ofPtr<ofxGamepad> gpPtr(new ofxGamepadAndroid(id));
		lock();
		gamepads.push_back(gpPtr);
		unlock();
    return gpPtr.get();
#else
    return NULL;
#endif
}

ofxGamepad* ofxGamepadHandler::getGamepad(int num) {
	if(getNumPads()>0)
		return gamepads[num].get();
	ofLog(OF_LOG_WARNING, "ofxGamepad::getGamepad(): WARNING NO GAMEPAD CONNECTED. GAMEPAD IS NULL.");
	return NULL;
}

int ofxGamepadHandler::getNumPads() {
	return gamepads.size();
}
