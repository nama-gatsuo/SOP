#include "ofMain.h"

class CameraMan : public ofCamera {
public:
    void update(){
        
        float r = radius;
        
        if ( bWalking ) t += 0.002;
        if ( bRadiusChange ) radiusTheta+= 0.01;
        
        r += sin(radiusTheta);
        
        setPosition( r * cos(t) , 0.5, r * sin(t) );
        
        ofVec3f lv = ofVec3f((r-2.0) * cos(t + 0.5), 1.4, (r-2.0) * sin(t + 0.5));
                
        if (bLookHorizontal) xAxisTheta += 0.007;
        if (bLookVertical)   yAxisTheta += 0.01;
        
        lv.y += 1.5 * sin(xAxisTheta);
        lv.x += 5.0 * sin(yAxisTheta);
        
        ofVec3f uv = ofVec3f(.0, 1.0, .0);
        lookAt( lv, uv );
        
    };
    
    void toggleWaking(){ bWalking = !bWalking; };
    
    void toggleLookHorizontal(){ bLookHorizontal = !bLookHorizontal; };

    void toggleLookVertical(){ bLookVertical = !bLookVertical; };

    void toggleRadiusChange(){ bRadiusChange = !bRadiusChange; };


private:
    bool bWalking = false;
    bool bRadiusChange = false;
    bool bLookHorizontal = false;
    bool bLookVertical = false;
    
    float t = 0.0; // theta
    const float radius = 8.0;
    
    float xAxisTheta = 0.0;
    float yAxisTheta = 0.0;
    float radiusTheta = 0.0;
};