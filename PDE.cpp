##include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#define k 1.62	//conductividad termica en m²*s⁻¹
#define Cp 820	//calor especifico en J*kg⁻¹*K⁻¹
#define rho 2710	//densidad en kg*m⁻³
#define dt 0.00003	//delta de tiempo en s
#define N 100	//espaciamiento en lugar
#define n 100.0	//espaciamiento
#define sal 50000 //movimientos en el tiempo

#define for_i for(int i=0;i<N;i++) //loop de i para no tener que escribirlo todas las veces
#define for_j for(int j=0;j<N;j++) //loop de j para no tener que escribirlo todas las veces

double dx = 50.0/n;
double dy = 50.0/n;
double nu = (double(k)/double(Cp*rho))*(double(dt)/double(dx*dx));

double Tpre[N][N], Tfut[N][N], p[sal];

void inicial(double,double,double);
void extremos();
void cerrados(double,double,double);

int main()
{
	double mitad = (n*dx)/2.0;
	double distancia_x = 0.0;
	double distancia_y = 0.0;
	
	inicial(mitad,distancia_x,distancia_y);
	extremos();
	cerrados(mitad,distancia_x,distancia_y);
	
	
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

void extremos()
{
	ofstream inicio;
	inicio.open("inicio.dat");
	
	for_i
	{
		for_j
		{
			inicio<<Tpre[i][j]<<",";
			
			if(j==(N-1))
			{
				inicio<<Tpre[i][j]<<endl;
			}
		}
	}
	inicio.close();
}

void cerrados(double mitad, double distancia_x, double distancia_y)
{
	double t = 0;
	double eje_x = 0;
	double eje_y = 0;
	int eje_z = 0;

	while(t<(sal*dt))
	{
		double pr = 0.0;
		
		for_i
		{
			for_j
			{
				distancia_x=((i*dx)-mitad)*((i*dx)-mitad);
				distancia_y=((j*dy)-mitad)*((j*dy)-mitad);
			
				if(i==0 || i==(N-1) || j==0 || j==(N-1))
				{
					Tpre[i][j] = 10.0;
					Tfut[i][j] = Tpre[i][j];
				}
				else if(sqrt(distancia_x+distancia_y)<5)
				{
					Tpre[i][j] = 100.0;
					Tpre[i][j] = Tpre[i][j];
				}
				else
				{
					eje_x = (Tpre[i+1][j]+Tpre[i-1][j]-2.0*Tpre[i][j]);
					eje_y = (Tpre[i][j+1]+Tpre[i][j-1]-2.0*Tpre[i][j]);
					Tfut[i][j] = Tpre[i][j]+nu*(eje_x+eje_y);
				}
			}
		}
		
		for_i
		{
			for_j
			{
				pr += Tpre[i][j];
				Tpre[i][j] = Tfut[i][j];
			}
		}
		
		p[eje_z] = (pr/(n*n));
		t += dt;
		eje_z ++;
		
		if(eje_z==2500)
		{
			ofstream cerrado0;
			cerrado0.open("cerrado0.dat");
			
			for_i
			{
				for_j
				{
					cerrado0<<Tpre[i][j]<<",";
					
					if(j==(N-1))
					{
						cerrado0<<Tpre[i][j]<<endl;
					}
				}
			}
			cerrado0.close();
		}
		else if(eje_z==5000)
		{
			ofstream cerrado1;
			cerrado1.open("cerrado1.dat");
			
			for_i
			{
				for_j
				{
					cerrado1<<Tpre[i][j]<<",";
					
					if(j==(N-1))
					{
						cerrado1<<Tpre[i][j]<<endl;
					}
				}
			}
			cerrado1.close();
		}
		else if(eje_z==(sal-3))
		{
			ofstream cerrado2;
			cerrado2.open("cerrado2.dat");
			
			for_i
			{
				for_j
				{
					cerrado2<<Tpre[i][j]<<",";
					
					if(j==(N-1))
					{
						cerrado2<<Tpre[i][j]<<endl;
					}
				}
			}
			cerrado2.close();
		}
	}
	
	ofstream pro;
	pro.open("pro.dat");
	for(int i=0;i<sal;i++)
	{
		pro<<p[i]<<endl;
	}
	pro.close();
}
