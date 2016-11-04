//
//  JellyFish.cpp
//  w11_w11_of
//
//  Created by aim on 11/4/16.
//
//

#include "JellyFish.hpp"
// using the constructor to initialize all the variables
JellyFish::JellyFish(ofVec2f position) :
mPosition(position),
mVelocity(ofRandom(-2.f, 2.f), ofRandom(-2.f, 2.f)),
mAcceleration(ofVec2f(0)),
mLifeSpan(255.f)
{
    
}
//-------------------------------------
void JellyFish::resetForces()
{
    // reset the acceleration
    mAcceleration *= 0;
}
//-------------------------------------
void JellyFish::applyForce(ofVec2f force)
{
    // adding for to acceleration
    mAcceleration += force;
}
//-------------------------------------
void JellyFish::update(float multiplier)
{
    // apply accelearation to velocity
    mVelocity += mAcceleration;
    mPosition += mVelocity * multiplier;
    
    // decreasing the particle life
    if (mLifeSpan > 0){
        mLifeSpan -= 2.f;
    }
    
}
//-------------------------------------
void JellyFish::draw()
{
    
    int alpha = 150;
    if( mLifeSpan > 1000 ){
        // new born partilce will be brighter
        ofSetColor(mLifeSpan);
    }else if( mLifeSpan <= 1000 ){
        // do some sparkle!
        ofRotate(45);
        //        ofSetColor(ofRandom(0, 255));
        ofColor aqua(0, 252, 255, alpha);
        ofColor purple(198, 0, 205, alpha);
        ofColor inbetween = aqua.getLerped(purple, ofRandom(1.0));
        ofSetColor(inbetween);
    };
    
    // closer particle is smaller
    
    ofRotate(-0.1);
    ofDrawCircle(mPosition, 20.f * ofMap(mLifeSpan, 0, 255.f, 0, 1.f));
    
    
    //    ofDrawCircle(mPosition, 3.f * ofMap(mLifeSpan, 0, 255.f, 0, 1.f));
    
}