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

//funciones
double prim_derx(double);
double seg_derx(double,double);
double prim_dery(double);
double seg_dery(double,double);
void inicial(double);
void avance(double(*f0)(double),double(*f1)(double,double),double(*f2)(double),double(*f3)(double,double));
void super_avance(double(*f0)(double),double(*f1)(double,double),double(*f2)(double),double(*f3)(double,double));
void otros_angulos(double(*f0)(double),double(*f1)(double,double),double(*f2)(double),double(*f3)(double,double));

using namespace std;

int main()
{
	double ang0 = (45*pi)/180;
	
	inicial(ang0);
	avance(prim_derx,seg_derx,prim_dery,seg_dery);
	super_avance(prim_derx,seg_derx,prim_dery,seg_dery);	
	otros_angulos(prim_derx,seg_derx,prim_dery,seg_dery);
	
	return 0;
}

//velocidad en el eje x que equivale a la primera derivada de la posicion
double prim_derx(double vel_x)
{
	return vel_x;
}

//aceleracion en el eje x que equivale a la segunda derivada de la posicion
double seg_derx(double vel_x,double vel_y)
{
	return -(c/m)*vel_x*sqrt((vel_x*vel_x)+(vel_y*vel_y));
}

//velocidad en el eje y que equivale a la primera derivada de la posicion
double prim_dery(double vel_y)
{
	return vel_y;
}

//aceleracion en el eje y que equivale a la segunda derivada de la posicion
double seg_dery(double vel_x,double vel_y)
{
	return -g-(c/m)*vel_y*sqrt((vel_x*vel_x)+(vel_y*vel_y));
}

//iniciamos el angulo de 45
void inicial(double ang0)
{
	x_dir[0] = 0.0;
	y_dir[0] = 0.0;
	vel_x[0] = (sin(ang0))*300.0;
	vel_y[0] = (cos(ang0))*300.0;
	t[0] = 0.0;
}

//avanzamos tanto en la direccion de x como en y
void avance(double(*f0)(double),double(*f1)(double,double),double(*f2)(double),double(*f3)(double,double))
{
	x_dir[1] = x_dir[0]+(dt*f0(vel_x[0]));
	y_dir[1] = y_dir[0]+(dt*f2(vel_y[0]));
	vel_x[1] = vel_x[0]+(dt*f1(vel_x[0],vel_y[0]));
	vel_y[1] = vel_y[0]+(dt*f3(vel_x[0],vel_y[0]));
	
	for_i1
	{
		x_dir[i+1] = x_dir[i-1]+(2.0*dt*f0(vel_x[i-1]));
		y_dir[i+1] = y_dir[i-1]+(2.0*dt*f2(vel_y[i-1]));
		vel_x[i+1] = vel_x[i-1]+(2.0*dt*f1(vel_x[i-1],vel_y[i-1]));
		vel_y[i+1] = vel_y[i-1]+(2.0*dt*f3(vel_x[i-1],vel_y[i-1]));
	}
	ofstream angulo0;
	angulo0.open("ang45.dat");
	for_i0
	{
		angulo0<<x_dir[i]<<" "<<y_dir[i]<<" "<<vel_x[i]<<" "<<vel_y[i]<<endl;
	}
}

//repetir el avance para el resto de posiciones
void super_avance(double(*f0)(double),double(*f1)(double,double),double(*f2)(double),double(*f3)(double,double))
{
	for_i1
	{
		x_dir[i] = x_dir[i-1]+(dt*f0(vel_x[i-1]));
		y_dir[i] = y_dir[i-1]+(dt*f2(vel_y[i-1]));
		vel_x[i] = vel_x[i-1]+(dt*f1(vel_x[i-1],vel_y[i-1]));
		vel_y[i] = vel_y[i-1]+(dt*f3(vel_x[i-1],vel_y[i-1]));
	}
	ofstream angulo1;
	angulo1.open("buenAng45.dat");
	for_i0
	{
		angulo1<<x_dir[i]<<" "<<y_dir[i]<<" "<<vel_x[i]<<" "<<vel_y[i]<<endl;
	}
	angulo1.close();
}

//avance para angulos de 10,20,30,40,50,60 y 70 grados
void otros_angulos(double(*f0)(double),double(*f1)(double,double),double(*f2)(double),double(*f3)(double,double))
{
	ofstream angulo2;
	angulo2.open("variosAng.dat");
	
	for(int i=1;i<8;i++)
	{		
		double angulo = (i*10*pi)/180;
		
		x_dir[0] = 0.0;
		y_dir[0] = 0.0;
		vel_x[0] = (sin(angulo))*300.0;
		vel_y[0] = (cos(angulo))*300.0;
		t[0] = 0.0;
		
		x_dir[1] = x_dir[0]+(dt*f0(vel_x[0]));
		y_dir[1] = y_dir[0]+(dt*f2(vel_y[0]));
		vel_x[1] = vel_x[0]+(dt*f1(vel_x[0],vel_y[0]));
		vel_y[1] = vel_y[0]+(dt*f3(vel_x[0],vel_y[0]));
	
		for_i1
		{
			x_dir[i+1] = x_dir[i-1]+(2.0*f0(vel_x[i-1]));
			y_dir[i+1] = y_dir[i-1]+(2.0*dt*f2(vel_y[i-1]));
			vel_x[i+1] = vel_x[i-1]+(2.0*dt*f1(vel_x[i-1],vel_y[i-1]));
			vel_y[i+1] = vel_y[i-1]+(2.0*dt*f3(vel_x[i-1],vel_y[i-1]));
		}
		
		for_i0
		{
			angulo2<<x_dir[i]<<" "<<y_dir[i]<<" "<<vel_x[i]<<" "<<vel_y[i]<<endl;
		}
	}
	angulo2.close();
	
	//hallados a mano y solo impresos en la terminal
	cout<<"La maxima distancia horizontal que alcanza el proyectil con el angulo de 45° es 4.23822 metros"<<endl;
	
	cout<<"La maxima distancia horizontal que alcanza el proyectil con uno de los otros angulos es 5.18812 metros y la alcanza con el angulo de 20°"<<endl;
}
