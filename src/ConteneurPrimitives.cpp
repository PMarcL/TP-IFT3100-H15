#include "ConteneurPrimitives.h"
#include <cfloat>

ConteneurPrimitives::ConteneurPrimitives(void)
	:primitiveSelectionnee(NULL)
{
	shader = Shader("Shaders/shaderMateriaux.vert", "Shaders/shaderMateriaux.frag");
	shader.charger();
}


ConteneurPrimitives::~ConteneurPrimitives(void)
{
}

void ConteneurPrimitives::ajouterPrimitive(PrimitiveGeometrique primitive)
{
	primitives.push_back(primitive);
}

void ConteneurPrimitives::afficher(ofMatrix4x4 projection, ofMatrix4x4 model, ofMatrix4x4 view, Lumiere lumiere)
{
	glUseProgram(shader.getProgramID());

		lumiere.chargerValeursIlluminationStruct(shader.getProgramID());
		chargerMatricesMVPUniforms(projection, model, view);
		ofMatrix4x4 modelSave = model;
		for(int i = 0; i < primitives.size(); i++)
		{
			model.glTranslate(primitives[i].getPosition());
			glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
			primitives[i].chargerMateriauxUniforms(shader.getProgramID());
			primitives[i].afficher();
			model = modelSave;
		}

	glUseProgram(0);
}

void ConteneurPrimitives::chargerMatricesMVPUniforms(const ofMatrix4x4& projection, const ofMatrix4x4& model, const ofMatrix4x4& view)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, projection.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "view"), 1, GL_FALSE, view.getPtr());
	glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "model"), 1, GL_FALSE, model.getPtr());
}

void ConteneurPrimitives::selectionnerPrimitive(ofVec3f position, float rayon)
{
	float distanceMinimum = FLT_MAX;
	for(int i = 0; i < primitives.size(); i++)
	{
		ofVec3f positionCourante = primitives[i].getPosition();
		if(positionDansRayon(position, positionCourante, rayon))
		{
			float distanceCourante = getDistanceEntreVecteur(position, positionCourante);
			if(distanceCourante < distanceMinimum)
			{
				distanceMinimum = distanceCourante;
				primitiveSelectionnee = &primitives[i];
			}
		}
	}
	materiauxPrimitiveSelectionnee = primitiveSelectionnee->getMateriaux();
	primitiveSelectionnee->setMateriaux(SELECTION);
}

bool ConteneurPrimitives::positionDansRayon(const ofVec3f& positionRef, const ofVec3f& positionCible, float rayon)
{
	return positionRef.x - positionCible.x < rayon && positionRef.y - positionCible.y < rayon && positionRef.z - positionCible.z < rayon;
}

float ConteneurPrimitives::getDistanceEntreVecteur(const ofVec3f& positionRef, const ofVec3f& positionCible)
{
	return sqrt(pow(positionRef.x - positionCible.x, 2) + pow(positionRef.y - positionCible.y, 2) + pow(positionRef.z - positionCible.z, 2));
}

void ConteneurPrimitives::relacherPrimitiveSelectionnee()
{
	primitiveSelectionnee->setMateriaux(materiauxPrimitiveSelectionnee);
	primitiveSelectionnee = NULL;
}

void ConteneurPrimitives::deplacerPrimitiveSelectionnee(ofVec3f position)
{
	if(primitiveSelectionnee != NULL)
		primitiveSelectionnee->setPosition(position);
}