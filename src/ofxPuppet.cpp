#include "ofxPuppet.h"

#define WML_INSTANTIATE_BEFORE

ofxPuppet::ofxPuppet()
:needsUpdating(false)
,nSelected(0) {
}

void ofxPuppet::setup(const ofMesh & mesh){
	originalMesh = mesh, deformedMesh = mesh;
	originalMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	deformedMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	deformer.InitializeFromMesh( &originalMesh );
	controlPoints.clear();
	needsUpdating = true;
}

void ofxPuppet::update(){
	if(needsUpdating) {
		set<unsigned int>::iterator cur(controlPoints.begin()), end(controlPoints.end());
		while ( cur != end ) {
			unsigned int nVertex = *cur++;
			ofVec3f vVertex = deformedMesh.getVertices()[nVertex];
			deformer.SetDeformedHandle( nVertex, ofVec2f( vVertex.x, vVertex.y ) );
		}
		deformer.ForceValidation();
		needsUpdating = false;
	}
	deformer.UpdateDeformedMesh( &deformedMesh, true );
}


void ofxPuppet::draw(){
	deformedMesh.draw();
}

void ofxPuppet::drawFaces(){	
	deformedMesh.drawFaces();
}

void ofxPuppet::drawWireframe() {
	deformedMesh.drawWireframe();
}

void ofxPuppet::drawControlPoints() {
	ofPushStyle();
	ofNoFill();
	ofSetColor(ofColor::red);
	for(set<unsigned int>::iterator itr = controlPoints.begin(); itr != controlPoints.end(); itr++) {
		ofCircle(deformedMesh.getVertex(*itr), 5); 
	}
	ofPopStyle();
}

void ofxPuppet::setControlPoint(int i) {
	setControlPoint(i, deformedMesh.getVertex(i));
}

void ofxPuppet::setControlPoint(int i, const ofVec2f& position) {
	if (controlPoints.find(i) == controlPoints.end()) {
		controlPoints.insert(i);
	}
	moveControlPoint(i,position);
}

void ofxPuppet::moveControlPoint(int i, const ofVec2f& position){
	if (controlPoints.find(i) == controlPoints.end()) {
		ofLogError() << "moveControl point cannot find control point " << i;
		return;
	}
	deformedMesh.getVertices()[i].set(position.x, position.y);
	needsUpdating = true; 
}

void ofxPuppet::removeControlPoint(int i) {
	controlPoints.erase(i);
	deformer.RemoveHandle(i);
	needsUpdating = true; 
}

const ofMesh& ofxPuppet::getOriginalMesh() {
	return originalMesh;
}

const ofMesh& ofxPuppet::getDeformedMesh() {
	return deformedMesh;
}
