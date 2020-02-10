#pragma once
#include <vector>

struct CoteActif {
private :

public :
	float y_max; //ordonn�e maximale du c�t�
	float curr_x; //abscisse de l'intersection
	float coeff; //coefficient directeur

	CoteActif();
	CoteActif(float yMax, float currX, float coeff);

	void SetCurrX(float const currX);
	float GetYMax() const { return y_max; };
	float GetCurrX() const { return curr_x; };
	float GetCoeff() const { return coeff; };
};
