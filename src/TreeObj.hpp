#include "ofMain.h"

class TreeObj {
public:
    TreeObj() {
    
        pos.push_back(ofVec3f(0,0,0));
        
        ofMatrix4x4 mat = ofMatrix4x4(1.0, 0, 0, 0,
                                      0, 1.0, 0, 0,
                                      0, 0, 1.0, 0,
                                      0, 0, 0, 1.0 );
        
        ofVec3f v = ofVec3f(0,1.2,0);
        pos.push_back(v);
        
        fractalLoop(&v, &mat, 0.8, 0);
        
    };
    
    void fractalLoop(ofVec3f * p, ofMatrix4x4 * mat, float r, int level) {
        
        if (level == MAX_LEVEL) return;
        
        for (int i = 0; i < 3; i++) {
        
            ofVec3f _p = ofVec3f(0, r, 0);
            
            float rad = TWO_PI / 3 * i;
            ofMatrix4x4 _m1 = ofMatrix4x4(cos(rad), 0.0, sin(rad), 0,
                                          0.0,      1.0, 0.0,      0,
                                          -sin(rad),0.0, cos(rad), 0,
                                          0,        0,   0,        0 );
            
            
            rad = PI / 3;
            ofMatrix4x4 _m2 = ofMatrix4x4(cos(rad), -sin(rad), 0.0, 0,
                                          sin(rad), cos(rad),  0.0, 0,
                                          0.0,      0.0,       1.0, 0,
                                          0,        0,         0,   0 );
            
            
            ofMatrix4x4 _m3 = *mat * _m1 * _m2;
            
            ofVec4f v = ofVec4f(_p.x, _p.y, _p.z, 1.0);
            v = _m3 * v;
            
            pos.push_back( *p );
            _p.set(p->x + v.x, p->y + v.y, p->z + v.z);
            pos.push_back( _p );
            
            fractalLoop(&_p, &_m3, r * 0.6, level+1);
        }
        
        mesh.setVertexData(pos.data(), pos.size(), GL_DYNAMIC_DRAW);
        
    };
    
    void update() {
        
        life -= 0.1;
        if (life < 0.1) life = 0.1;
        if (life > 1.1) life = 1.1;
        
    };
    
    void trigger() {
        
        life += 0.8;
    
    };
    
    void draw() {
        
        glPointSize(5.0 * life);
        mesh.draw(GL_LINES, 0, pos.size());
        mesh.draw(GL_POINTS, 0, pos.size());
    };
    
    ofVbo mesh;
    vector<ofVec3f> pos;

    int MAX_LEVEL = 5;
    float life = 0.1;
};
