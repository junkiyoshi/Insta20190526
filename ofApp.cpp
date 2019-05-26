#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto len = 100.f;
	auto base = glm::vec3();
	vector<glm::vec3> rectangle;
	rectangle.push_back(glm::vec3(0, -len * 0.5, 0));
	rectangle.push_back(glm::vec3(len, -len * 0.5, 0));
	rectangle.push_back(glm::vec3(len, len * 0.5, 0));
	rectangle.push_back(glm::vec3(0, len * 0.5, 0));

	for (auto y = -len * 3; y <= len * 3; y += len) {

		base = glm::vec3(0, y, 0);
		for (int i = 0; i < 6; i++) {

			float noise_seed_y = ofRandom(1000);
			vector<glm::vec3> locations;
			for (auto rect : rectangle) {

				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, ofGetFrameNum() * 0.005), 0, 1, -PI * 0.25, PI * 0.25), glm::vec3(0, 1, 0));
				locations.push_back(base + glm::vec4(rect, 0) * rotation_y);
			}

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(locations);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertices(locations);
			ofEndShape(true);

			base = glm::vec3(locations[1].x, base.y, locations[1].z);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}