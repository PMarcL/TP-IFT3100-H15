#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Shader.h"
#include "camera.h"
#include "Axes.h"
#include "MousePositionHandler.h"
#include "Paysage.h"
#include "MusiqueSFX.h"
#include "CubeMap.h"
#include "Lumiere.h"
#include "ConteneurPrimitives.h"
#include "EffetPleinEcran.h"

#include <stack>

const static float VITESSE_ROTATION_DEFAUT = 2.0;
const static float VITESSE_CAMERA_DEFAUT = 3.0;
const static float FAR_PLANE_DISTANCE = 3000.0;
const static float VERTIGO_DEGREE_PAR_FRAME = 1.0;
const static float ANGLE_VISION_NORMAL = 70.0;
const static float RAYON_DE_SELECTION = 50.0;
const static float DIMENSION_PAR_DEFAUT = 20.0f;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		

		~ofApp();

	private:
		void configurerUI();
		void zoomIn();
		void zoomOut();
		void pushMatrix();
		void popMatrix();
		void pauseToggled(bool & paused);
		void vertigoToggled(bool & enabled);
		void lampeDePocheToggled(bool & enabled);
		void vitesseCameraChanged(float& vitesse);
		void initializeFrameBuffers();
		ofVec3f getPositionDevantCamera();

		stack<ofMatrix4x4> matrices;
		Shader shaderOrigine;
		Shader shaderTex;
		Camera camera;
		Axes origineDuMonde;
		ofMatrix4x4 projection;
		ofMatrix4x4 model;
		ofMatrix4x4 view;
		MusiqueSFX son;
		Paysage paysage;
		CubeMap cubeMap;
		Lumiere lumiere;
		ConteneurPrimitives primitives;
		EffetPleinEcran effetPleinEcran;

		GLuint framebuffer;
		GLuint genererTexturePleinEcran(int, int);

		int centreXFenetre;
		int centreYFenetre;
		int nbCaptureEcran;
		float angleChampDeVision;
		MousePositionHandler* mouseHandler;

		bool showMenu;
		ofxFloatSlider vitesseCamera;
		ofxToggle vertigoEnFonction;
		ofxToggle paused;
		ofxToggle lampeDePoche;
		ofxLabel guiMessage;
		ofxLabel fps;
		ofxLabel usageMessage;
		ofxPanel gui;

		Shader shaderLampe;
		PrimitiveGeometrique positionLampe;
		PrimitiveGeometrique positionPonctuelle;
};
