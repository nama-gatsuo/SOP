#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxPostProcessing.h"
#include "ofxArtnet.h"
//#include "ofxSyphon.h"

#include "GroundObj.hpp"
#include "LissajousObj.hpp"
#include "TreeObj.hpp"
#include "ArcSphere.hpp"
#include "GrassEmitter.hpp"
#include "SpiralObj.hpp"
#include "LineCylinder.hpp"
#include "CameraMan.hpp"
#include "ColumnObj.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void sendDmx(int state);
	
    GroundObj ground;
    LissajousObj lissajous;
    TreeObj tree;
    ArcSphere arc;
    GrassEmitter grass;
    SpiralObj sp;
    LineCylinder lc;
    ColumnObj clm;
    
    CameraMan cam;
    
    ofxArtnet artnet;
    ofxOscReceiver receiver;
    ofxOscSender sender;
    
    const int port = 7401;
    
    unsigned char dmxOn[512];
    unsigned char dmxOff[512];
    int dmxState = 0;
    bool bDmxOn = false;
    
    ofxPostProcessing post;
    
};
