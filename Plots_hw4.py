import numpy as np
import matplotlib.pylab as plt
from mpl_toolkits.mplot3d.axes3d import Axes3D

#segundo punto (ODE)
ang45 = np.genfromtxt("ang45.dat")

x = ang45[:,0]
y = ang45[:,1]
vx = ang45[:,2]
vy = ang45[:,3]

tequila1=10
anguila45=0
for j in range(1000,len(x)):
	if(abs(y[j])<tequila1):
		tequila1=y[j]
		anguila45=x[j]


plt.figure()
plt.plot(x,y,label="45")
plt.title("Trayectoria del proyectil a 45°")
plt.ylabel("y (m)")
plt.xlabel("x (m)")
plt.legend()
plt.ylim(0,5)
plt.savefig("ang45.pdf")

ang_x=["x10","x20","x30","x40","x50","x60","x70"]
ang_y=["y10","y20","y30","y40","y50","y60","y70"]
ang=[10,20,30,40,50,60,70]

variosAng=np.genfromtxt("variosAng.dat")

n=int(np.shape(variosAng)[0]/len(ang_x))

plt.figure()
for i in range(len(ang_x)):
	ang_x[i]=variosAng[i*n:(i+1)*n,0]
	ang_y[i]=variosAng[i*n:(i+1)*n,1]
	plt.plot(ang_x[i],ang_y[i],label=(i+1)*10)
	
plt.plot(x,y,label="45")
plt.ylim(0,5)
plt.title("Trayectorias del proyectil entre 10° y 70°")
plt.ylabel("y (m)")
plt.xlabel("x (m)")
plt.legend()
plt.savefig("variosAng.pdf")


hola=np.linspace(10,100,7)

for i in range(len(ang_x)):
	no=100
	for j in range(1000,n):
		if(abs(ang_y[i][j])<no):
			no=ang_y[i][j]
			hola[i]=ang_x[i][j]

#tercer punto (PDE)

##condiciones iniciales de extremos fijos
iniFijos=np.genfromtxt("inicialesFijos.dat",delimiter=",")

y0=np.linspace(0,50,np.shape(iniFijos)[0])
x0=np.linspace(0,50,np.shape(iniFijos)[1])
x0,y0=np.meshgrid(x0,y0)

fig=plt.figure()
eje=fig.add_subplot(1,1,1, projection='3d')
eje.plot_wireframe(x0,y0,iniFijos)

plt.title("Condiciones iniciales en extremos fijos")
eje.set_xlabel("x(m)")
eje.set_ylabel("y(m)")
eje.set_zlabel("T(°C)")
eje.set_zlim(0,100)
plt.savefig("iniFijos.pdf")

##momento 1 en extremos fijos
fijos1=np.genfromtxt("fijos1.dat",delimiter=",")

y3=np.linspace(0,50,np.shape(fijos1)[0])
x3=np.linspace(0,50,np.shape(fijos1)[1])
x3,y3=np.meshgrid(x3,y3)

fig3=plt.figure()
eje3=fig3.add_subplot(1,1,1, projection='3d')
eje3.plot_wireframe(x3,y3,fijos1)

plt.title("Momento 1 con extremos fijos")
eje3.set_xlabel("x(m)")
eje3.set_ylabel("y(m)")
eje3.set_zlabel("T(°C)")
eje3.set_zlim(0,100)
plt.savefig("fijos1.pdf")

##momento 2 en extremos fijos
fijos2=np.genfromtxt("fijos2.dat",delimiter=",")

y4=np.linspace(0,50,np.shape(fijos2)[0])
x4=np.linspace(0,50,np.shape(fijos2)[1])
x4,y4=np.meshgrid(x4,y4)

fig4=plt.figure()
eje4=fig4.add_subplot(1,1,1, projection='3d')
eje4.plot_wireframe(x4,y4,fijos2)
eje4.set_zlim(0,100)

plt.title("Momento 2 con extremos fijos")
eje4.set_xlabel("x(m)")
eje4.set_ylabel("y(m)")
eje4.set_zlabel("T(°C)")
plt.savefig("fijos2.pdf")

##momento final con extremos fijos
fijos3=np.genfromtxt("fijos3.dat",delimiter=",")

y5=np.linspace(0,50,np.shape(fijos3)[0])
x5=np.linspace(0,50,np.shape(fijos3)[1])
x5,y5=np.meshgrid(x5,y5)

fig5=plt.figure()
eje5=fig5.add_subplot(1,1,1, projection='3d')
eje5.plot_wireframe(x5,y5,fijos3)
eje5.set_zlim(0,100)

plt.title("Momento final con extremos fijos")
eje5.set_xlabel("x(m)")
eje5.set_ylabel("y(m)")
eje5.set_zlabel("T(°C)")
plt.savefig("fijos3.pdf")


##condiciones iniciales de extremos libres
iniLibres=np.genfromtxt("inicialesLibres.dat",delimiter=",")

y1=np.linspace(0,50,np.shape(iniLibres)[0])
x1=np.linspace(0,50,np.shape(iniLibres)[1])
x1,y1=np.meshgrid(x1,y1)

fig1=plt.figure()
eje1=fig1.add_subplot(1,1,1, projection='3d')
eje1.plot_wireframe(x1,y1,iniLibres)

plt.title("Condiciones iniciales en extremos libres")
eje1.set_xlabel("x(m)")
eje1.set_ylabel("y(m)")
eje1.set_zlabel("T(°C)")
eje1.set_zlim(0,100)
plt.savefig("iniLibres.pdf")

##momento 1 con extremos libres 
libres1=np.genfromtxt("libres1.dat",delimiter=",")

y6=np.linspace(0,50,np.shape(libres1)[0])
x6=np.linspace(0,50,np.shape(libres1)[1])
x6,y6=np.meshgrid(x6,y6)

fig6=plt.figure()
eje6=fig6.add_subplot(1,1,1, projection='3d')
eje6.plot_wireframe(x6,y6,libres1)
eje6.set_zlim(0,100)

plt.title("Momento 1 con extremos libres")
eje6.set_xlabel("x(m)")
eje6.set_ylabel("y(m)")
eje6.set_zlabel("T(°C)")
plt.savefig("libres1.pdf")

##momento 2 con extremos libres
libres2=np.genfromtxt("libres2.dat",delimiter=",")

y7=np.linspace(0,50,np.shape(libres2)[0])
x7=np.linspace(0,50,np.shape(libres2)[1])
x7,y7=np.meshgrid(x7,y7)

fig7=plt.figure()
eje7=fig7.add_subplot(1,1,1, projection='3d')
eje7.plot_wireframe(x7,y7,libres2)
eje7.set_zlim(0,100)

plt.title("Momento 2 con extremos libres")
eje7.set_xlabel("x(m)")
eje7.set_ylabel("y(m)")
eje7.set_zlabel("T(°C)")
plt.savefig("libres2.pdf")

##momento final con extremos libres
libres3=np.genfromtxt("libres3.dat",delimiter=",")

y8=np.linspace(0,50,np.shape(libres3)[0])
x8=np.linspace(0,50,np.shape(libres3)[1])
x8,y8=np.meshgrid(x8,y8)

fig8=plt.figure()
eje8=fig8.add_subplot(1,1,1, projection='3d')
eje8.plot_wireframe(x8,y8,libres3)
eje8.set_zlim(0,100)

plt.title("Momento final con extremos libres")
eje8.set_xlabel("x(m)")
eje8.set_ylabel("y(m)")
eje8.set_zlabel("T(°C)")
plt.savefig("libres3.pdf")

#condiciones iniciales de sistema periodico
iniPeriodico=np.genfromtxt("inicialesPeriodica.dat",delimiter=",")

y2=np.linspace(0,50,np.shape(iniPeriodico)[0])
x2=np.linspace(0,50,np.shape(iniPeriodico)[1])
x2,y2=np.meshgrid(x2,y2)

fig2=plt.figure()
eje2=fig2.add_subplot(1,1,1, projection='3d')
eje2.plot_wireframe(x2,y2,iniPeriodico)

plt.title("Condiciones iniciales en sistema periodico")
eje2.set_xlabel("x(m)")
eje2.set_ylabel("y(m)")
eje2.set_zlabel("T(°C)")
eje2.set_zlim(0,100)
plt.savefig("iniPeriodica.pdf")

##momento 1 con sistema periodico
periodica1=np.genfromtxt("periodica1.dat",delimiter=",")

y9=np.linspace(0,50,np.shape(periodica1)[0])
x9=np.linspace(0,50,np.shape(periodica1)[1])
x9,y9=np.meshgrid(x9,y9)

fig9=plt.figure()
eje9=fig9.add_subplot(1,1,1, projection='3d')
eje9.plot_wireframe(x9,y9,periodica1)

plt.title("Momento 1 con sistema periodico")
eje9.set_zlim(0,100)
eje9.set_xlabel("x(m)")
eje9.set_ylabel("y(m)")
eje9.set_zlabel("T(°C)")
plt.savefig("periodica1.pdf")

##momento 2 con sistema periodico
periodica2=np.genfromtxt("periodica2.dat",delimiter=",")

y10=np.linspace(0,50,np.shape(periodica2)[0])
x10=np.linspace(0,50,np.shape(periodica2)[1])
x10,y10=np.meshgrid(x10,y10)

fig10=plt.figure()
eje10=fig10.add_subplot(1,1,1, projection='3d')
eje10.plot_wireframe(x10,y10,periodica2)

plt.title("Momento 1 con sistema periodico")
eje10.set_xlabel("x(m)")
eje10.set_ylabel("y(m)")
eje10.set_zlim(0,100)
eje10.set_zlabel("T(°C)")
plt.savefig("periodica2.pdf")

##momento final con sistema periodico
periodica3=np.genfromtxt("periodica3.dat",delimiter=",")

y11=np.linspace(0,50,np.shape(periodica3)[0])
x11=np.linspace(0,50,np.shape(periodica3)[1])
x11,y11=np.meshgrid(x11,y11)
fig11=plt.figure()
eje11=fig11.add_subplot(1,1,1, projection='3d')
eje11.plot_wireframe(x11,y11,periodica3)

plt.title("Momento final con sistema periodico")
eje11.set_xlabel("x(m)")
eje11.set_ylabel("y(m)")
eje11.set_zlim(0,100)
eje11.set_zlabel("T(°C)")
plt.savefig("periodica3.pdf")

##graficas de la temperatura del sistema en los diferentes casos
temFijos=np.genfromtxt("temFijos.dat")
temLibres=np.genfromtxt("temLibres.dat")
temPeriodica=np.genfromtxt("temPeriodica.dat")

dt=0.00003
t=np.linspace(0,dt*len(temFijos),len(temFijos))

plt.figure()
plt.plot(t,temFijos,label="Extremos fijos")
plt.plot(t,temLibres,label="Extremos libres")
plt.plot(t,temPeriodica,label="Sistema periodico")
plt.title("Temperatura del sistema en los diferentes casos")
plt.legend()
plt.xlabel("t(seg)")
plt.ylabel("T(°C)")
plt.savefig("temSistema.pdf")
