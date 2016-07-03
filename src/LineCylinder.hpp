#include "ofMain.h"

class LineCylinder {
public:
    LineCylinder(){
        power.assign(NOTE_NUM, 0.0);
        
        for (int i = 0; i < NOTE_NUM; i++) {
            
            float h = i * 1.0;
            
            ofVbo vbo;
            vector<ofVec3f> pv;
            vector<ofIndexType> iv;
            
            for (int j = 0; j < EDGE_NUM; j++) {
                
                float t1 = j * TWO_PI / EDGE_NUM;
                float t2 = (j+1) * TWO_PI / EDGE_NUM;
                
                pv.push_back(ofVec3f( r*sin(t1), 0., r*cos(t1) ));
                pv.push_back(ofVec3f( r*sin(t2), 0., r*cos(t2) ));
                
                float w;
                
                float coin = ofRandom(1.0);
                if (coin < 0.3) w = 1.25;
                else if (coin < 0.6) w = 0.75;
                else w = 1.0;
                
                pv.push_back(ofVec3f( r*sin(t1), w+h, r*cos(t1) ));
                pv.push_back(ofVec3f( r*sin(t2), w+h, r*cos(t2) ));
                
                iv.push_back( j*4 );
                iv.push_back( j*4+1 );
                iv.push_back( j*4+3 );
                iv.push_back( j*4+2 );
            }
            
            vbo.setVertexData(pv.data(), pv.size(), GL_DYNAMIC_DRAW);
            vbo.enableIndices();
            vbo.setIndexData(iv.data(), iv.size(), GL_DYNAMIC_DRAW);
            
            noteLayer.push_back(vbo);
            
            r += 0.01;
        }
    
    };
    
    void update(){
        if (noteLayer.empty()) return;
        for (int i = 0; i < NOTE_NUM; i++) {
            
            power[i] -= 0.01;
            if (power[i] < 0.0) power[i] = 0.0;
            
        }
        
    };
    
    void triggerNote(int note) {
        
        int n = note - 25;
        power[n] += 1.0;
        
    };
    
    void draw() {
        ofNoFill();
        if (noteLayer.empty()) return;
        
        for (int i = 0; i < NOTE_NUM; i++) {
            
            ofSetColor(200, 210, 255, 255 * power[i] );
            noteLayer[i].drawElements(GL_QUADS, EDGE_NUM * 4);
        }
        ofFill();
    };
    
    vector<ofVbo> noteLayer;
    vector<float> power;
    
    float r = 20;
    const int EDGE_NUM = 100;
    const int NOTE_NUM = 14;
};