#include "CoteActif.h"

CoteActif::CoteActif() 
{
	y_max = 0.0f;
	curr_x = 0.0f;
	coeff_dir = 0.0f;
	next_cote = nullptr;
}

CoteActif::CoteActif(float yMax, float currX, float coeff)
{
	y_max = yMax;
	curr_x = currX;
	coeff_dir = coeff;
	next_cote = nullptr;
}

CoteActif::CoteActif(float yMax, float currX, float coeff, CoteActif& nextCote)
{
	y_max = yMax;
	curr_x = currX;
	coeff_dir = coeff;
	next_cote = &nextCote;
}

void CoteActif::SetCurrX(float const currX)
{

}

