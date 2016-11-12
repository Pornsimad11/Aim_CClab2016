#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofSetVerticalSync(true);
    cam.setup(320, 240);
    
    gui.setup();
    gui.add(minArea.set("Min area", 10, 1, 100));
    gui.add(maxArea.set("Max area", 200, 1, 500));
    gui.add(threshold.set("Threshold", 128, 0, 255));
    gui.add(holes.set("Holes", false));
    
    // imitate() will set up previous and diff
    // so they have the same size and type as cam
    imitate(previous, cam);
    imitate(diff, cam);
    
    
    gui.add(lkMaxLevel.set("lkMaxLevel", 3, 0, 8));
    gui.add(lkMaxFeatures.set("lkMaxFeatures", 200, 1, 1000));
    gui.add(lkQualityLevel.set("lkQualityLevel", 0.01, 0.001, .02));
    gui.add(lkMinDistance.set("lkMinDistance", 4, 1, 16));
    gui.add(lkWinSize.set("lkWinSize", 8, 4, 64));
    gui.add(usefb.set("Use Farneback", true));
    gui.add(fbPyrScale.set("fbPyrScale", .5, 0, .99));
    gui.add(fbLevels.set("fbLevels", 4, 1, 8));
    gui.add(fbIterations.set("fbIterations", 2, 1, 8));
    gui.add(fbPolyN.set("fbPolyN", 7, 5, 10));
    gui.add(fbPolySigma.set("fbPolySigma", 1.5, 1.1, 2));
    gui.add(fbUseGaussian.set("fbUseGaussian", false));
    gui.add(fbWinSize.set("winSize", 32, 4, 64));
    
    curFlow = &fb;
    
 
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        // take the absolute difference of prev and cam and save it inside diff
        absdiff(cam, previous, diff);
        diff.update();
        
        // like ofSetPixels, but more concise and cross-toolkit
        copy(cam, previous);
        
        // this is the key line: get the average of each column
        columnMean = meanCols(diff);
        
        contourFinder.setMinAreaRadius(minArea);
        contourFinder.setMaxAreaRadius(maxArea);
        contourFinder.setThreshold(threshold);
        contourFinder.findContours(cam);
        contourFinder.setFindHoles(holes);
        
        if(usefb) {
            curFlow = &fb;
            fb.setPyramidScale(fbPyrScale);
            fb.setNumLevels(fbLevels);
            fb.setWindowSize(fbWinSize);
            fb.setNumIterations(fbIterations);
            fb.setPolyN(fbPolyN);
            fb.setPolySigma(fbPolySigma);
            fb.setUseGaussian(fbUseGaussian);
        } else {
            curFlow = &lk;
            lk.setMaxFeatures(lkMaxFeatures);
            lk.setQualityLevel(lkQualityLevel);
            lk.setMinDistance(lkMinDistance);
            lk.setWindowSize(lkWinSize);
            lk.setMaxLevel(lkMaxLevel);
        }
        
        // you can use Flow polymorphically
        curFlow->calcOpticalFlow(cam);
        
    
    }
}

void ofApp::draw() {
    ofSetColor(255);
//    cam.draw(0, 0);

        
        ofPushMatrix();
        ofTranslate(250, 100);
        cam.draw(0,0,0,0);
    ofTranslate(320, 0);
    diff.draw(0, 0);
    // draw the mean for each channel
    for(int k = 0; k < 3; k++) {
        // use the correct color for each channel
        switch(k) {
            case 0: ofSetColor(ofColor::red); break;
            case 1: ofSetColor(ofColor::blue); break;
            case 2: ofSetColor(ofColor::green); break;
        }
        ofBackground(0);
        curFlow->draw(0,0,640,480);
                

        ofDrawBitmapStringHighlight(ofToString((int) ofGetFrameRate()) + "fps", 10, 20);
        ofPopMatrix();
        gui.draw();
        
       
      ;
    }
}

