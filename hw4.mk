resultados.tex: plots.tex
	pdflatex Resultados_hw4.tex
	
plots.tex: Plots_hw4.py ode.dat pde.dat
	python3 Plots_hw4.py
	
	
ode.dat: ODE.cpp
	g++ ODE.cpp -o capaso.out
	./capaso.out
	
pde.dat: PDE.cpp
	g++ PDE.cpp -o capo.out
	./capo.out
	
plots.py:
	pytohn Plots_hw4.py

clean:
	rm *.dat *.pdf *.log *.aux *.out
