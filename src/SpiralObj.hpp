#include "ofMain.h"

class SpiralNoteObj {
public:
    SpiralNoteObj(int _life, int _note){
        
        note = _note;
        life = _life;
        
        color = ofFloatColor((note-25)*0.02, 0.7, 1.0 );
        
//        d = floor(_note * 0.1);
        l = floor(2400 / _note);
        d = 4;
//        l = 50;
    };
    
    void update(){
        
        life -= d;
    
    };
    
    int note;
    int life;
    int d; // delta of life
    int l; // length
    ofFloatColor color;
    float size;
};


class SpiralObj {
public:
    SpiralObj(){
    
        vector<ofVec3f> pv;
        float theta = 0.0;
        for (int i = 0; i < VERT_NUM; i++) {
            
            float r = exp(0.4 * theta) * 0.1;
            float x = r * sin(theta);
            float z = r * cos(theta);
            float y = 2.0 - theta*0.4;
            
            pv.push_back( ofVec3f(x, y, z) );
            
            theta += 0.003;
            
        }
        
        spiral.setVertexData(pv.data(), pv.size(), GL_DYNAMIC_DRAW);
        
    };
    void triggerNote(int note){
    
        notes.push_back( SpiralNoteObj(VERT_NUM, note) );
        
    };
    void update(){
        
        if (notes.empty()) return;
        
        vector<SpiralNoteObj>::iterator it;
        for (it = notes.begin(); it < notes.end(); it++) {
            
            it->update();
            if (it->life - it->l < 0) notes.erase(it);
            
        }
        
    };
    void draw(){
        
        if (notes.empty()) return;
        
        vector<SpiralNoteObj>::iterator it;
        for (it = notes.begin(); it < notes.end(); it++) {
            
            ofPushMatrix();
            
            ofTranslate(0, it->note * 0.1, 0.0);
            ofSetColor(it->color);
            
            glPointSize(5.0);
            spiral.draw(GL_POINTS, it->life - it->l, 1);
            spiral.draw(GL_LINE_STRIP, it->life - it->l, it->l);
            
            ofPopMatrix();
        
        }
        
    };

    
private:
    vector<SpiralNoteObj> notes;
    ofVbo spiral;
    const float r0 = 10.;
    const int VERT_NUM = 5000;
};
