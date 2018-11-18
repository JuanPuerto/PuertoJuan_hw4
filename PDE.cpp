#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define k 1.62	//conductividad termica en m²*s⁻¹
#define Cp 820	//calor especifico en J*kg⁻¹*K⁻¹
#define rho 2710	//densidad en kg*m⁻³
#define dt 0.00003	//delta de tiempo en s
#define N 100	//espaciamiento en lugar
#define n 100.0	//espaciamiento
#define T_CALCITA 10.0
#define T_VARILLA 100.0

double nu = (double(k)/double(Cp*rho))*(double(dt)/double(dx*dx));
double dx = 50.0/n;
double dy = 50.0/n;

double Tpre[N][N], Tfut[N][N];

int main()
{
	
	
	return 0;
}
