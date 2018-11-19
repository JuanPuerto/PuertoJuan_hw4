#include <iostream>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

#define pi 3.14159	//definir constante pi
#define g 10.0	//aceleracion gravitacional en m*s⁻²
#define c 0.2	//coeficiente de friccion sin unidades
#define m 0.2	//masa del proyectil en kg
#define dt 0.0001	//avance en el tiempo
#define N 21000	//espaciamiento de lugar

#define for_i0 for(int i=0;i<N;i++)	//loop para todos los valores de los arreglos
#define for_i1 for(int i=1;i<N;i++)	//loop para valores internos de los arreglos

double x_dir[N], y_dir[N], vel_x[N], vel_y[N], t[N];	//arreglos necesarios para avanzar

double prim_derx(double);
double seg_derx(double,double);
double prim_dery(double);
double seg_dery(double,double);

using namespace std;

int main()
{
	
	
	return 0;
}

double prim_derx(double vel_x)
{
	return vel_x;
}

double seg_derx(double vel_x,double vel_y)
{
	return -(c/m)*vel_x*sqrt((vel_x*vel_x)+(vel_y*vel_y));
}

double prim_dery(double vel_y)
{
	return vel_y;
}

double seg_dery(double vel_x,double vel_y)
{
	return -g-(c/m)*vel_y*sqrt((vel_x*vel_x)+(vel_y*vel_y));
}
