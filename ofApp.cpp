#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	ofColor color;
	vector<int> hex_list = { 0x247BA0, /*0x70C1B3,*/ 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto radius = 100;
	for (auto x = -200; x <= 200; x += radius * 2) {

		for (auto y = -200; y <= 200; y += radius * 2) {

			for (auto z = -200; z <= 200; z += radius * 2) {

				this->setStarToMesh(this->face_mesh, this->frame_mesh, glm::vec3(x, y, z), radius * 0.85);
			}
		}
	}

	if (ofGetFrameNum() % 120 < 75) {

		// 受け入れるフレーム数よりも少ない数値のmodで処理すると止まる直前に動きが出る
		this->noise_seed += ofMap(ofGetFrameNum() % 60, 0, 75, 0.015, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);
	
	this->face_mesh.drawFaces();
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setStarToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius) {

	int deg_start = ofRandom(360);
	ofColor color = this->color_list[(int)ofMap(ofNoise(ofRandom(1000), this->noise_seed), 0, 1, 0, this->color_list.size())];

	auto deg_span = 72;
	for (auto deg = deg_start; deg < deg_start + 360; deg += deg_span) {

		auto angle_x = ofMap(ofNoise(ofRandom(1000), this->noise_seed), 0, 1, -PI, PI);
		auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));

		auto angle_y = ofMap(ofNoise(ofRandom(1000), this->noise_seed), 0, 1, -PI, PI);
		auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));

		auto angle_z = ofMap(ofNoise(ofRandom(1000), this->noise_seed), 0, 1, -PI, PI);
		auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

		int face_index = face_target.getVertices().size();

		face_target.addVertex(location + glm::vec4(radius * 0.05 * cos(deg * DEG_TO_RAD), radius * 0.05 * sin(deg * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		face_target.addVertex(location + glm::vec4(radius * 0.5 * cos((deg - deg_span * 0.35) * DEG_TO_RAD), radius * 0.5 * sin((deg - deg_span * 0.35) * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		face_target.addVertex(location + glm::vec4(radius * 0.5 * cos((deg + deg_span * 0.35) * DEG_TO_RAD), radius * 0.5 * sin((deg + deg_span * 0.35) * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		face_target.addVertex(location + glm::vec4(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		face_target.addVertex(location + glm::vec4(radius * 0.5 * cos(deg * DEG_TO_RAD), radius * 0.5 * sin(deg * DEG_TO_RAD), radius * 0.15, 0) * rotation_z * rotation_y * rotation_x);
		face_target.addVertex(location + glm::vec4(radius * 0.5 * cos(deg * DEG_TO_RAD), radius * 0.5 * sin(deg * DEG_TO_RAD), radius * -0.15, 0) * rotation_z * rotation_y * rotation_x);

		for (auto i = face_index; i < face_target.getVertices().size(); i++) {

			face_target.addColor(color);
		}

		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1);
		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 3);
		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);
		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 0);

		face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1);
		face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 3);
		face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);
		face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 0);

		int frame_index = frame_target.getVertices().size();

		frame_target.addVertex(location + glm::vec4(radius * 0.05 * cos(deg * DEG_TO_RAD), radius * 0.05 * sin(deg * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		frame_target.addVertex(location + glm::vec4(radius * 0.5 * cos((deg - deg_span * 0.35) * DEG_TO_RAD), radius * 0.5 * sin((deg - deg_span * 0.35) * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		frame_target.addVertex(location + glm::vec4(radius * 0.5 * cos((deg + deg_span * 0.35) * DEG_TO_RAD), radius * 0.5 * sin((deg + deg_span * 0.35) * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		frame_target.addVertex(location + glm::vec4(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0, 0) * rotation_z * rotation_y * rotation_x);
		frame_target.addVertex(location + glm::vec4(radius * 0.5 * cos(deg * DEG_TO_RAD), radius * 0.5 * sin(deg * DEG_TO_RAD), radius * 0.15, 0) * rotation_z * rotation_y * rotation_x);
		frame_target.addVertex(location + glm::vec4(radius * 0.5 * cos(deg * DEG_TO_RAD), radius * 0.5 * sin(deg * DEG_TO_RAD), radius * -0.15, 0) * rotation_z * rotation_y * rotation_x);

		for (auto i = frame_index; i < frame_target.getVertices().size(); i++) {

			frame_target.addColor(ofColor(0));
		}

		frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
		frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 2);
		frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 1);
		frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 2);

		frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 0);
		frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 1);
		frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 2);
		frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 3);

		frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 0);
		frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 1);
		frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 2);
		frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 3);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}