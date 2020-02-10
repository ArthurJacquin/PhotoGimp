#pragma once
#include <vector>

struct CoteActif {
private :

public :
	float y_max; //ordonnée maximale du côté
	float curr_x; //abscisse de l'intersection
	float coeff_dir; //coefficient directeur
	CoteActif* next_cote; //côté actif suivant

	CoteActif();
	CoteActif(float yMax, float currX, float coeff);
	CoteActif(float yMax, float currX, float coeff, CoteActif& nextCote);

	void SetCurrX(float const currX);
	float GetYMax() const { return y_max; };
	float GetCurrX() const { return curr_x; };
	float GetCoeff() const { return coeff_dir; };
};
