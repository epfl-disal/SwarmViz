# SwarmViz

A visualization and analysis tool for Particle Swarm Optimization



## COMPILATION FROM SOURCE
Make sure the qmake command points to qmake 3.0, provided by Qt5. If not, run the following command.
    export PATH="<Qt5 install dir>/<Qt version>/<compiler>/bin:$PATH"

Then, run
    ./config
    make clean all

## RUN
To run SwarmViz use either QtCreator or run
    ./bin/swarmviz& 

## DOCUMENTATION
Run Doxygen 1.8.9.1 on the Doxyfile:
  cd src
  doxygen Doxyfile

## DEPENDENCIES (draft)
### Compilation
qmake ~>3.0
Qt5
### Documentation
doxygen ~>1.8.9.1
graphviz

## QCUSTOMPLOT 1.1.1
If the library is upgraded, change the function QCPLayerable::setParentLayerable from protected to public
