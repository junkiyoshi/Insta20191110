#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void setStarToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius);

	ofEasyCam cam;
	vector<ofColor> color_list;
	ofMesh face_mesh, frame_mesh;
	float noise_seed;
};