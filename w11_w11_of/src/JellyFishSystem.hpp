//
//  JellyFishSystem.hpp
//  w11_w11_of
//
//  Created by aim on 11/4/16.
//
//

#pragma once
#include "ofMain.h"
#include "JellyFish.hpp"

class JellyFishSystem{
public:
   JellyFishSystem(ofVec2f position);
    void update(ofVec2f force);
    void draw();
    
    
    vector<JellyFish>    mParticleList;
    ofVec2f             mPosition;
    int                 mEmitRate;
    bool                mIsAddingParticles;
    
};