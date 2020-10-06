https://pdg.lbl.gov/2020/hadronic-xsections/

https://github.com/hanswenzel/G4HadStudies

https://g4devel.fnal.gov:8181/DoSSiER/SelectExperiment.xhtml

To compile the Fortran code:

gfortran -std=legacy -c exmpl4.for util.for setup.for graphit.for

gfortran -std=legacy exmpl4.o util.o setup.o graphit.o
