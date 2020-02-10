#include "CoteActif.h"

CoteActif::CoteActif() 
{
	y_max = 0.0f;
	curr_x = 0.0f;
	coeff = 0.0f;
}

CoteActif::CoteActif(float yMax, float currX, float coeff)
{
	y_max = yMax;
	curr_x = currX;
	coeff = coeff;
}

void CoteActif::SetCurrX(float const currX)
{

}

