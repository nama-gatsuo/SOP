#include "ofMain.h"

class GrassLine {
public:
    GrassLine(){
        x = ofRandom(-10, 10);
        z = ofRandom(-10, 10);
        h = ofRandom(1.0, 3.5);
        s = ofRandom(0.2, 0.4);
        life = ofRandom(1.0, 1.5);
    };
    
    void update(){
        life -= 0.02;
        y += s;
    };
    
    void draw(){
        
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(x, y, z);
        glVertex3f(x, y + h, z);
        glEnd();
    
    };
    float life;
    
private:
    float x, z;
    float s;
    float y = 0.0;
    float h;
};

class GrassEmitter {
public:
    GrassEmitter(){};
    void trigger(){
        
        for (int i = 0; i < 10; i++) {
        
            line.push_back(GrassLine());
            
        }
    
    };
    
    void update() {
        
        if (line.empty()) return;
        vector<GrassLine>::iterator it;
        for (it = line.begin(); it < line.end(); it++) {
            it->update();
            
            if (it->life < 0.0) {
                line.erase(it);
            }
        }
        
    }
    
    void draw(){
        
        vector<GrassLine>::iterator it;
        for (it = line.begin(); it != line.end(); it++) {
            it->draw();
        }
    
    };
    
private:
    vector<GrassLine> line;
    
};