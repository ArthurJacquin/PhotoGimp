#pragma once
#include <iostream>
#include <vector>

struct CoteActif {
private:
	float y_max; //ordonnée maximale du côté
	float curr_x; //abscisse de l'intersection
	float coeff_dir; //coefficient directeur
	CoteActif* next_cote; //côté actif suivant
	
public:
	CoteActif();
	CoteActif(CoteActif& const copy);
	CoteActif(float yMax, float currX, float coeff);
	CoteActif(float yMax, float currX, float coeff, CoteActif& nextCote);
	~CoteActif();

	void SetCurrX(float const currX);
	void SetNextCote(CoteActif& const cote);
	float GetYMax() const { return y_max; };
	float GetCurrX() const { return curr_x; };
	float GetCoeff() const { return coeff_dir; };
	float GetInverseCoeff() const { return (1/coeff_dir); };
	CoteActif* GetNextCote() const { return next_cote; };

	friend std::ostream& operator <<(std::ostream& os, const CoteActif& obj);
};
