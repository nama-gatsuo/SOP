#include "ofMain.h"

class NoteSign {
public:
    NoteSign(int _note){
        note = _note;
    };
    void update(){
        life--;
    };
    void draw(){
        float h = (note - 53) * 0.2;
        ofDrawBox(0.0, h, 0.0, 0.2, 0.2, 0.2);
    };
    
    int note;
    int life = 5;

};


class ColumnObj {
public:
    ColumnObj(){};
    
    void update(){
        
        if (notes.empty()) return;
        
        vector<NoteSign>::iterator it;
        for (it = notes.begin(); it < notes.end(); it++) {
            
            it->update();
            if (it->life == 0) notes.erase(it);
            
        }
    
    };
    void triggerNote(int _note){
        
        notes.push_back( NoteSign(_note) );
    
    };
    void draw(){
        
        if (notes.empty()) return;
        
        vector<NoteSign>::iterator it;
        for (it = notes.begin(); it < notes.end(); it++) {
            it->draw();
        }
        
    };

private:
    vector<NoteSign> notes;

};