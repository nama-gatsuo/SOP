#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetFrameRate(60);
    
    ofBackground(0);
    
    receiver.setup(port);
    
    dmxOn[0] = 255;  dmxOn[1] = 255;  dmxOn[2] = 255;  dmxOn[3] = 0;
    dmxOff[0] = 255; dmxOff[1] = 0; dmxOff[2] = 0; dmxOff[3] = 0;
    
    for (int i = 4; i < 512; i++) {
    
        dmxOn[i] = 0;
        dmxOff[i] = 0;
    
    }
    
    artnet.setup("127.0.0.1");
//    artnet.setup("192.168.1.184");
    
    sender.setup("127.0.0.1", 7400);
    
    cam.setNearClip(0.1);
    
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<BloomPass>();

}

//--------------------------------------------------------------
void ofApp::update(){
    
    cam.update();
    
    ground.update();
    tree.update();
    arc.update();
    grass.update();
    sp.update();
    lc.update();
    clm.update();
    
    while (receiver.hasWaitingMessages()) {
    
        ofxOscMessage m;
        receiver.getNextMessage(m);
        string address = m.getAddress();
        
        vector<string> splitAddress = ofSplitString(address, "/");
        int inst = ofToInt(splitAddress.at(1));
        int note = ofToInt(splitAddress.at(2));
        
        switch (inst) {
            case 0:
                switch (note) {
                        
                    case 36: ground.triggerKick(); break;
                    case 39: grass.trigger(); break;
                    case 40: artnet.sendDmx("127.0.0.1", 0x0, 0x0, dmxOn, 512); bDmxOn = true; break;
//                    case 40: artnet.sendDmx("192.168.1.75",dmxOn, 512); bDmxOn = true; break;
                    case 42: tree.trigger(); break;
                    case 49: {
                        dmxState = 5;
                        sendDmx(dmxState);
                        bDmxOn = true;
                        break;
                    }
                    default: break;
                }
                
                break;
            case 1: sp.triggerNote(note); break;
            case 2: lc.triggerNote(note); break;
            case 3: clm.triggerNote(note); break;
            case 4: arc.updateNote(note); break;
            default: break;
        }

    }
    
    if (bDmxOn) {
//        artnet.sendDmx("192.168.1.75", 0x0, 0x0, dmxOff, 512);
        artnet.sendDmx("127.0.0.1", dmxOff, 512);
        
        dmxState -= 1;
        sendDmx(dmxState);
        
        if (dmxState < 0) bDmxOn = false;
        
    }
    
}

void ofApp::sendDmx(int state) {

    ofxOscMessage m1;
    m1.setAddress( "/ch2" );
    m1.addIntArg( 51 * state );
    sender.sendMessage( m1 );
    
    ofxOscMessage m2;
    m2.setAddress( "/ch3" );
    m2.addIntArg( 51 * state );
    sender.sendMessage( m2 );
    
};


//--------------------------------------------------------------
void ofApp::draw(){
    
    post.begin(cam);
    
    lissajous.draw();
    ground.draw();
    grass.draw();
    sp.draw();
    lc.draw();
    
    ofPushMatrix();
    ofTranslate(0.0, 9.0, 0.0);
    arc.draw();
    ofPopMatrix();
    
    ofSetHexColor(0xffffff);
    for (int i = 0; i < 10; i++) {
        
        float _t = TWO_PI / 10 * i;
        
        ofPushMatrix();
        ofTranslate(cos(_t) * 10, 0, sin(_t) * 10);
        tree.draw();
        ofPopMatrix();
    }
    
    for (int i = 0; i < 5; i++) {
        
        float _t = TWO_PI / 5 * i;
        
        ofPushMatrix();
        ofTranslate(cos(_t) * 6, 0, sin(_t) * 6);
        clm.draw();
        ofPopMatrix();
    }
    
    post.end();
    
//    ofDrawBitmapString(ofToString(ofGetFrameRate()), 100, 100);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case 'a': cam.toggleWaking(); break;
        case 's': cam.toggleRadiusChange(); break;
        case 'd': cam.toggleLookVertical(); break;
        case 'f': cam.toggleLookHorizontal(); break;
        default: break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
