#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(2);
	
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int i = 0; i < 1500; i++) {

		this->radius_list.push_back(ofRandom(500));
		this->deg_list.push_back(ofRandom(360));
	}
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	int threshold_radius = 300;
	int max_radius = 500;
	this->line.clear();

	for (int i = 0; i < this->radius_list.size(); i++){

		int speed = 5;
		int radius_start = ((int)(this->radius_list[i] + speed) % max_radius);
		int radius = max_radius - radius_start;
		float deg_start = this->deg_list[i] + (radius > threshold_radius ? 1 : ofMap(radius, 0, threshold_radius, pow(speed, ofMap(radius, 0, threshold_radius, 2, 1)), 1));
		float deg = deg_start;
		int color_value = ofRandom(0, 192);

		for (int k = 0; k < 5; k++) {

			radius = ((int)(this->radius_list[i] + speed * k) % max_radius);
			radius = max_radius - radius;

			deg += (radius > threshold_radius ? 1 : ofMap(radius, 1, threshold_radius, pow(speed, ofMap(radius, 0, threshold_radius, 2, 1)), 1));

			auto z = radius > threshold_radius ? 0 : ofMap(radius, 0, threshold_radius, -1 * pow(threshold_radius - radius, 1.01), 0);
			auto vertex = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z + 2);
			this->line.addVertex(vertex);
			this->line.addColor(ofColor(color_value));

			if (k > 0 && radius < max_radius - 10) {

				this->line.addIndex(this->line.getNumVertices() - 1);
				this->line.addIndex(this->line.getNumVertices() - 2);
			}

		}

		this->radius_list[i] = radius_start;
		this->deg_list[i] = deg_start;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(100);

	ofSetColor(0);
	//this->face.draw();
	ofSetColor(255);
	this->line.drawWireframe();

	this->cam.end();

}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}