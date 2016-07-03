#include "ofMain.h"

enum ArcColor { BLUE, WHITE };

enum ArcStyle { ARC, ARC_LINE, ARC_LINE_BAR };

struct ArcData {
    float rotX, rotY, deg, r, w;
    
    ArcStyle s;
    ArcColor c;
    ofVbo vbo;
    int vNum;
    
};

class ArcSphere {
public:
    ArcSphere(){
        
        int coin;
        for (int i = 0; i < num; i++) {
            
            ArcData d;
            d.rotX = ofRandom(360);
            d.rotY = ofRandom(360);
            
            if (ofRandom(100)>90) d.deg = floor(ofRandom(8,27) * 10);
            else d.deg = ofRandom(60, 80);
            
            d.r = ofRandom(0.5, 1.5);
            
            if (ofRandom(100)>90) d.w = ofRandom(0.1, 0.2);
            else d.w = ofRandom(0.3, 0.4);
            
            coin = (int)ofRandom(100) % 3;
            switch (coin) {
                case 0: d.s          = ARC; break;
                case 1: d.s     = ARC_LINE; break;
                case 2: d.s = ARC_LINE_BAR; break;
            }
            
            if (ofRandom(100)>90) d.c = WHITE;
            else d.c = BLUE;
            
            arcData.push_back( d );
        }
        
        for (int i = 0; i < num; i++) {
            
            switch (arcData[i].s) {
                case ARC: createArc( &arcData[i] ); break;
                case ARC_LINE: createArc( &arcData[i] ); break;
                case ARC_LINE_BAR: createArcLineBar( &arcData[i] ); break;
            }
        }
    };
    
    void update(){
        
        for (int i = 0; i < num; i++) {
            
            arcData[i].rotX += 0.2;
            arcData[i].rotY += 0.5;
            
        }
    
    };
    
    void updateNote(int val) {
        
        for (int i = 0; i < num; i++) {
            
            if (arcData[i].s == ARC) {
                
                ArcData * _d = &arcData[i];
                
                vector<ofVec3f> pv;
                _d->w = val * 0.075;
                
                for (int j = 0; j < _d->vNum / 2; j++) {
                    
                    pv.push_back( ofVec3f(cos( j * PI / 180 ) * _d->r,
                                          sin( j * PI / 180 ) * _d->r,
                                          0.0
                                          ) );
                    pv.push_back( ofVec3f(cos( j * PI / 180 ) * (_d->r + _d->w),
                                          sin( j * PI / 180 ) * (_d->r + _d->w),
                                          0.0
                                          ) );
                    
                }
                
                _d->vbo.updateVertexData(pv.data(), pv.size());
                
            }
            
        }
    
    }
    void draw(){
    
        for (int i = 0; i < num; i++) {
        
            ofPushMatrix();
            
            ofRotateX( arcData[i].rotX );
            ofRotateY( arcData[i].rotY );
            
            switch (arcData[i].s) {
                case ARC:
                    arcData[i].vbo.draw(GL_TRIANGLE_STRIP, 0, arcData[i].vNum);
                    break;
                case ARC_LINE:
                    ofNoFill();
                    arcData[i].vbo.draw(GL_TRIANGLE_STRIP, 0, arcData[i].vNum);
                    ofFill();
                    break;
                case ARC_LINE_BAR:
                    arcData[i].vbo.draw(GL_QUADS, 0, arcData[i].vNum);
                    break;
            }
            
            ofPopMatrix();
        }
    
    
    };

private:

    void createArcLine(ArcData * _arcData){};
    
    void createArcLineBar(ArcData * _d){
        
        int step = 4;
        
        ofFloatColor col;
        if (_d->c == BLUE) col = ofFloatColor(0.5, 0.9, 1.0, 0.8);
        else if (_d->c == WHITE) col = ofFloatColor(1.0, 1.0, 1.0, 0.8);
        
        vector<ofVec3f> pv;
        vector<ofFloatColor> cv;
        
        for (int i = 0; i < _d->deg; i += step*2) {
            
            pv.push_back( ofVec3f(cos( i * PI / 180 ) * _d->r,
                                  sin( i * PI / 180 ) * _d->r,
                                  0.0
                                  ) );
            pv.push_back( ofVec3f(cos( i * PI / 180 ) * (_d->r + _d->w),
                                  sin( i * PI / 180 ) * (_d->r + _d->w),
                                  0.0
                                  ) );
            pv.push_back( ofVec3f(cos( (i+step) * PI / 180 ) * (_d->r + _d->w),
                                  sin( (i+step) * PI / 180 ) * (_d->r + _d->w),
                                  0.0
                                  ) );
            pv.push_back( ofVec3f(cos( (i+step) * PI / 180 ) * _d->r,
                                  sin( (i+step) * PI / 180 ) * _d->r,
                                  0.0
                                  ) );
        }

        cv.assign(pv.size(), col);
        
        _d->vbo.setVertexData(pv.data(), pv.size(), GL_DYNAMIC_DRAW);
        _d->vbo.setColorData(cv.data(), cv.size(), GL_DYNAMIC_DRAW);
        
        _d->vNum = pv.size();
    };
    
    void createArc(ArcData * _d){
    
        ofFloatColor col;
        if (_d->c == BLUE) col = ofFloatColor(0.5, 0.9, 1.0, 0.8);
        else if (_d->c == WHITE) col = ofFloatColor(1.0, 1.0, 1.0, 0.8);
        
        vector<ofVec3f> pv;
        vector<ofFloatColor> cv;
        
        for (int i = 0; i < _d->deg; i += 4) {
            
            pv.push_back( ofVec3f(cos( i * PI / 180 ) * _d->r,
                                  sin( i * PI / 180 ) * _d->r,
                                  0.0
                                  ) );
            pv.push_back( ofVec3f(cos( i * PI / 180 ) * (_d->r + _d->w),
                                  sin( i * PI / 180 ) * (_d->r + _d->w),
                                  0.0
                                  ) );
        }
        
        cv.assign(pv.size(), col);
        
        _d->vbo.setVertexData(pv.data(), pv.size(), GL_DYNAMIC_DRAW);
        _d->vbo.setColorData(cv.data(), cv.size(), GL_DYNAMIC_DRAW);
        
        _d->vNum = pv.size();
        
    };
    
    float power;
    const static int num = 80;
    vector<ArcData> arcData;

};