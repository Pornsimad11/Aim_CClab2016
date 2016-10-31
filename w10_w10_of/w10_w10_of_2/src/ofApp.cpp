#include "ofApp.h"
//credits--https://github.com/openframeworks/ofBook/blob/master/chapters/intro_to_graphics/chapter.md
//--------------------------------------------------------------
void ofApp::setup(){
    minDistance = 10;
    leftMouseButtonPressed = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (leftMouseButtonPressed) {
        ofVec2f mousePos(ofGetMouseX(), ofGetMouseY());
        if (lastPoint.distance(mousePos) >= minDistance) {
            // a.distance(b) calculates the Euclidean distance between point a and b.  It's
            // the length of the straight line distance between the points.
            currentPolyline.curveTo(mousePos);  // Here we are using an ofVec2f with curveTo(...)
            lastPoint = mousePos;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    for (int i=0; i<polylines.size(); i++) {
        ofPolyline polyline = polylines[i];
        polyline.draw();
    }
    
    ofSetColor(255);
    currentPolyline.draw();
    vector<ofVec3f> vertices = currentPolyline.getVertices();
    for (int vertexIndex=0; vertexIndex<vertices.size(); vertexIndex++) {
        ofVec3f vertex = vertices[vertexIndex];  // ofVec3f is like ofVec2f, but with a third dimension, z
        ofDrawCircle(vertex, 5);
        ofSetColor(ofRandom(50, 255));
        float width = ofRandom(5, 20);
        float height = ofRandom(5, 20);
        float xOffset = ofRandom(-40, 40);
        float yOffset = ofRandom(-40, 40);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'e') {
        leftMouseButtonPressed = false;

        currentPolyline.clear();  // Erase the vertices, allows us to start a new brush stroke
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (button == OF_MOUSE_BUTTON_LEFT) {
        leftMouseButtonPressed = true;
        currentPolyline.curveTo(x, y);  // Remember that x and y are the location of the mouse
        currentPolyline.curveTo(x, y);  // Necessary duplicate for first control point
        lastPoint.set(x, y);  // Set the x and y of a ofVec2f in a single line
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (button == OF_MOUSE_BUTTON_LEFT) {
        leftMouseButtonPressed = false;
        currentPolyline.curveTo(x, y);
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
