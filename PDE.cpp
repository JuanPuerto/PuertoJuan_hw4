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
#define sal 50000 //movimientos en el tiempo
#define T_CALCITA 10.0
#define T_VARILLA 100.0

#define for_i for(int i=0;i<N;i++) //loop de i para no tener que escribirlo todas las veces
#define for_j for(int j=0;j<N;j++) //loop de j para no tener que escribirlo todas las veces

double nu = (double(k)/double(Cp*rho))*(double(dt)/double(dx*dx));
double dx = 50.0/n;
double dy = 50.0/n;

double Tpre[N][N], Tfut[N][N];

void inicial(double,double,double);

int main()
{
	double mitad = (n*dx)/2.0;
	double distancia_x = 0.0;
	double distancia_y = 0.0;
	
	return 0;
}

void inicial(double mitad, double distancia_x, double distancia_y)
{
	for_i
	{
		for_j
		{
			distancia_x=((i*dx)-mitad)*((i*dx)-mitad);
			distancia_y=((j*dy)-mitad)*((j*dy)-mitad);
			
			if(sqrt(distancia_x+distancia_y)<5.0)
			{
				Tpre[i][j] = 100.0;
			}
			else
			{
				Tpre[i][j] = 10.0;
			}
		}
	}
}
