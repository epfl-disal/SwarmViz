# SwarmViz

A visualization and analysis tool for Particle Swarm Optimization



## Compilation from source

Make sure the qmake command points to qmake 3.0, provided by Qt5. If not, run the following command.

    export PATH="<Qt5 install dir>/<Qt version>/<compiler>/bin:$PATH"

Then, run
    ./config
    make clean all

## Running the program

To run SwarmViz use either QtCreator or run

    ./bin/swarmviz& 

## Documentation

Run Doxygen 1.8.9.1 on the Doxyfile:

  cd src
  doxygen Doxyfile

## Dependencies 

### Compilation

qmake ~>3.0
Qt5

### Documentation

doxygen ~>1.8.9.1
graphviz

## QCustomPlot 1.1.1

If the library is upgraded, change the function QCPLayerable::setParentLayerable from protected to public
