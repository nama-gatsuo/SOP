#include "ofMain.h"

class GroundObj {
public:
    
    GroundObj() {
    
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
            
                float x = j - w/2;
                float z = i - h/2;
                float y = 2.4 / (1 + pow(x/4, 2) + pow(z/4, 2));
                
                pos.push_back(ofVec3f(x , 0, z));
                maxY.push_back( y );
                
            }
        }
        
        mesh.setVertexData(pos.data(), pos.size(), GL_DYNAMIC_DRAW);
        
        for (int i = 0; i < h-1; i++) {
            for (int j = 0; j < w-1; j++) {
                
                index.push_back(ofIndexType(i * w + j));
                index.push_back(ofIndexType((i+1) * w + j));
                
                index.push_back(ofIndexType((i+1) * w + j));
                index.push_back(ofIndexType((i+1) * w + j + 1));

                index.push_back((i+1) * w + j + 1);
                index.push_back(i * w + j + 1);

                index.push_back(i * w + j + 1);
                index.push_back(i * w + j);
            }
        }
        
        mesh.enableIndices();
        mesh.setIndexData(index.data(), index.size(), GL_DYNAMIC_DRAW);
        
        acceleration.assign(pos.size(), 0);
        velocity.assign(pos.size(), 0);
        
        
    };
    
        
    void update() {
        
        // kick update
        for (int i = 0; i < pos.size(); i++) {
            
            velocity[i] -= 0.4;
            
            pos[i].y += velocity[i];
            if (pos[i].y < 0) {
                pos[i].y = 0;
                velocity[i] = 0;
            } else if (pos[i].y > 4.0) {
                pos[i].y = 4.0;
                
            }
            
        }
        mesh.updateVertexData(pos.data(), pos.size());
        
    };
    
    void triggerKick() {
        
        for (int i = 0; i < pos.size(); i++) {
        
            velocity[i] += maxY.at(i);
        
        }
        
    };
    
    void draw() {
        
        ofTranslate(0, -1.0, 0);
        ofSetColor(255, 255, 255);
        mesh.drawElements(GL_LINES, index.size());
        
        ofTranslate(0, -0.1, 0);
        ofSetColor(83, 150, 205, 190);
        mesh.drawElements(GL_QUADS, index.size());

    }
    
    ofVbo mesh;
    vector<ofVec3f> pos;
    vector<ofIndexType> index;
    vector<float> acceleration;
    vector<float> velocity;
    vector<float> maxY;
    
private:
    const int w = 32, h = 32;
    
};