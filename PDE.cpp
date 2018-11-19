#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

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

double dx = 50.0/n; //pasos en el eje x
double dy = 50.0/n;	//pasos en el eje y
double nu = (double(k)/double(Cp*rho))*(double(dt)/double(dx*dx));

double Tpre[N][N], Tfut[N][N], p[sal];	//arreglos para pasos en el tiempo

//funciones
void inicial(double,double,double);
void extremos(string);
void fijos(double,double,double);
void libres(double,double,double);
void periodica(double,double,double);
void todo(void (*f) (double,double,double),double,double,double,string,string,string,string,double,double);

int main()
{
	double mitad = (n*dx)/2.0;
	double distancia_x = 0.0;
	double distancia_y = 0.0;
	string f0 = "inicialesFijos.dat";
	string f1 = "fijos1.dat";
	string f2 = "fijos2.dat";
	string f3 = "fijos3.dat";
	string f4 = "temFijos.dat";
	string l0 = "inicialesLibres.dat";
	string l1 = "libres1.dat";
	string l2 = "libres2.dat";
	string l3 = "libres3.dat";
	string l4 = "temLibres.dat";
	string p0 = "inicialesPeriodica.dat";
	string p1 = "periodica1.dat";
	string p2 = "periodica2.dat";
	string p3 = "periodica3.dat";
	string p4 = "temPeriodica.dat";
	double r1 = 20.0;
	double r2 = 10.0;
	double r3 = 6.25;
	double r4 = 2.0;
	
	inicial(mitad,distancia_x,distancia_y);
	extremos(f0);
	todo(fijos,mitad,distancia_x,distancia_y,f1,f2,f3,f4,r1,r2);
	
	inicial(mitad,distancia_x,distancia_y);
	extremos(l0);
	todo(libres,mitad,distancia_x,distancia_y,l1,l2,l3,l4,r3,r4);
	
	inicial(mitad,distancia_x,distancia_y);
	extremos(p0);
	todo(periodica,mitad,distancia_x,distancia_y,p1,p2,p3,p4,r3,r4);
	
	return 0;
}

//arreglo inicial del sistema
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

//extremos del sistema
void extremos(string a)
{
	ofstream inicio;
	inicio.open(a);
	
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

//condiciones para el sistema con extremos fijos
void fijos(double mitad,double distancia_x,double distancia_y)
{
	double eje_x = 0;
	double eje_y = 0;
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
}

//condiciones para el sistema con extremos libres
void libres(double mitad,double distancia_x,double distancia_y)
{
	double eje_x = 0;
	double eje_y = 0;
	for_i
	{
		for_j
		{
			distancia_x=((i*dx)-mitad)*((i*dx)-mitad);
			distancia_y=((j*dy)-mitad)*((j*dy)-mitad);
			
			if(i==0)
			{
				Tpre[i][j] = Tpre[i+1][j];
				Tfut[i][j] = Tpre[i][j];
			}
			else if(i==(N-1))
			{
				Tpre[i][j] = Tpre[i-1][j];
				Tfut[i][j] = Tpre[i][j];
			}
			else if(j==0)
			{
				Tpre[i][j] = Tpre[i][j+1];
				Tfut[i][j] = Tpre[i][j];
			}
			else if(j==(N-1))
			{
				Tpre[i][j] = Tpre[i][j-1];
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
}

//condiciones para el sistema periodico
void periodica(double mitad,double distancia_x,double distancia_y)
{
	double eje_x = 0;
	double eje_y = 0;
	for_i
	{
		for_j
		{
			distancia_x=((i*dx)-mitad)*((i*dx)-mitad);
			distancia_y=((j*dy)-mitad)*((j*dy)-mitad);
			
			if(i==0)
			{
				Tpre[i][j] = Tpre[i+N-2][j];
				Tfut[i][j] = Tpre[i][j];
			}
			else if(i==(N-1))
			{
				Tpre[i][j] = Tpre[i-N+2][j];
				Tfut[i][j] = Tpre[i][j];
			}
			else if(j==0)
			{
				Tpre[i][j] = Tpre[i][j+N-2];
				Tfut[i][j] = Tpre[i][j];
			}
			else if(j==(N-1))
			{
				Tpre[i][j] = Tpre[i][j-N+2];
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
}

//sistema en distintos casos
void todo(void(*f)(double,double,double),double mitad,double distancia_x,double distancia_y,string a,string b,string c, string d,double r,double s)
{
	double t = 0;
	int eje_z = 0;

	while(t<(sal*dt))
	{
		double pr = 0.0;
		
		f(mitad,distancia_x,distancia_y);
		
		
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
		
		//hace la primera grafica dependiendo del caso
		if(eje_z==(sal/r))
		{
			ofstream sistema0;
			sistema0.open(a);
			
			for_i
			{
				for_j
				{
					sistema0<<Tpre[i][j]<<",";
					
					if(j==(N-1))
					{
						sistema0<<Tpre[i][j]<<endl;
					}
				}
			}
			sistema0.close();
		}
		//hace la segunda grafica dependiendo del caso
		else if(eje_z==(sal/s))
		{
			ofstream sistema1;
			sistema1.open(b);
			
			for_i
			{
				for_j
				{
					sistema1<<Tpre[i][j]<<",";
					
					if(j==(N-1))
					{
						sistema1<<Tpre[i][j]<<endl;
					}
				}
			}
			sistema1.close();
		}
		//hace la tercera grafica dependiendo del caso
		else if(eje_z==(sal-3))
		{
			ofstream sistema2;
			sistema2.open(c);
			
			for_i
			{
				for_j
				{
					sistema2<<Tpre[i][j]<<",";
					
					if(j==(N-1))
					{
						sistema2<<Tpre[i][j]<<endl;
					}
				}
			}
			sistema2.close();
		}
	}
	//hace la grafica de la temperatura del sistema dependiendo del caso
	ofstream tem;
	tem.open(d);
	for(int i=0;i<sal;i++)
	{
		tem<<p[i]<<endl;
	}
	tem.close();
}
