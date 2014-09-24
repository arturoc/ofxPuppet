#pragma once

#include "ofMain.h"
#define WML_INSTANTIATE_BEFORE
#include "RigidMeshDeformer2D.h"

class ofxPuppet {
protected:
	ofMesh originalMesh;
	ofVboMesh deformedMesh;
	rmsmesh::RigidMeshDeformer2D deformer;
	bool needsUpdating;
	set<unsigned int> controlPoints;
	int nSelected;
	
public: 
	ofxPuppet();
	
	void setup(const ofMesh & mesh);
	void update();

	void draw();
	void drawFaces();
	void drawWireframe();
	void drawControlPoints();
	
	void setControlPoint(int i);
	void setControlPoint(int i, const ofVec2f& position);
	void moveControlPoint(int i, const ofVec2f& position);
	void removeControlPoint(int i);
	const set<unsigned int> & getControlPoints(){ return controlPoints; }
	const ofMesh& getOriginalMesh();
	const ofMesh& getDeformedMesh();
};


