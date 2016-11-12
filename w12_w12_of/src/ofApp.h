#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    
    ofVideoGrabber cam;
    ofPixels previous;
    ofImage diff;
    cv::Mat columnMean;
    ofxCv::ContourFinder contourFinder;
    
    ofxPanel gui;
    ofParameter<float> minArea, maxArea, threshold;
    ofParameter<bool> holes;
    ofParameter<float> fbPyrScale, lkQualityLevel, fbPolySigma;
    ofParameter<int> fbLevels, lkWinSize, fbIterations, fbPolyN, fbWinSize, lkMaxLevel, lkMaxFeatures, lkMinDistance;
    ofParameter<bool> fbUseGaussian, usefb;
    
    ofxCv::FlowFarneback fb;
    ofxCv::FlowPyrLK lk;
    
    ofxCv::Flow* curFlow;
    

  

    
  
};