#pragma once

#include "ofMain.h"
#include "ofAppEGLWindow.h"
#include "TerminalListener.h"
#include "ofxRPiCameraVideoGrabber.h"
#include "CameraState.h"

class ofApp : public ofBaseApp, public KeyListener{

	public:

		void setup();
		void update();
		void draw();
		void keyPressed(int key);

	void onCharacterReceived(KeyListenerEventData& e);
	TerminalListener consoleListener;
	ofxRPiCameraVideoGrabber videoGrabber;
	
    CameraState cameraState;
	
	bool doDrawInfo;
    ofDirectory dataFolder;	
    vector<ofFile> configFiles;
    int currentConfigFileIndex;
    bool doSwitchConfig;
};

