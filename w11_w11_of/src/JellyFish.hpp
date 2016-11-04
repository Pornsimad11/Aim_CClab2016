//
//  JellyFish.hpp
//  w11_w11_of
//
//  Created by aim on 11/4/16.
//
//

#pragma once
#include "ofMain.h"

class JellyFish{
public:
    // creating a constructor
    JellyFish(ofVec2f pos);
    
    void resetForces();
    void applyForce(ofVec2f force);
    void update(float multiplier);
    void draw();
    
    ofVec2f mPosition, mVelocity, mAcceleration;
    float mLifeSpan;
};