#include "ofMain.h"

class LissajousObj {
public:
    
    LissajousObj(){
    
        t = 0;
        
        for (int i = 0; i < 10000; i++) {
            
            float x = r * sin(a * t + pa);
            float y = r * sin(b * t + pb);
            float z = r * sin(a * t + pc);
            
            pv.push_back( ofVec3f(x, y, z) );
            cv.push_back( ofFloatColor(0.6, 1.0, 1.0, 0.05) );
            
            t += 0.5;
            
            r -= 0.004;
            
        }
        
        vbo.setVertexData(pv.data(), pv.size(), GL_DYNAMIC_DRAW);
        vbo.setColorData(cv.data(), cv.size(), GL_DYNAMIC_DRAW);
    
    };
    
    void update() {
        power -= 0.01;
        if (power < 0.0) power = 0.0;
    };
    
    void triggerNote(int note) {
        power += (note - 25) * 0.04;
        if (power < 1.0) power = 1.0;
    };
    
    void draw() {
        
        vbo.draw(GL_LINE_STRIP, 0, pv.size());
        
        
    };
    
    ofVbo vbo;
    vector<ofVec3f> pv;
    vector<ofFloatColor> cv;

    
    const float a = 1.000, b = 16.001, c = 1.000;
    const float pa = PI / 2, pb = PI / 4, pc = 0;
    
    float t;
    float r = 80;
    
    float power = 0.0;
};