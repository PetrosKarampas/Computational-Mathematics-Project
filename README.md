## Drone movement study through differential equations

We used [gnuplot](http://www.gnuplot.info) for plotting.

You can find the gnuplot docs [here](http://www.gnuplot.info/docs_5.4/Gnuplot_5_4.pdf).

<br>

## Project structure
Folders `Problem-1b`, `Problem-1d`, `Problem-2d` include the scripts for the solution of the problems.

The `plots` folder includes  `.txt` files with the output values of the solutions. The scripts use these files to generate plots.

The `utils` folder includes an API used by the scripts that creates plots using the gnuplot command line tool.

The `bin` folder includes the unix executables after the compilation.

<br>

## Installation

### Install gnuplot
Install  `gnuplot` in ubuntu linux,
~~~~
sudo apt-get update -y && sudo apt-get install -y gnuplot
~~~~

Install  `gnuplot` in solus linux,
~~~~
sudo eopkg install gnuplot
~~~~

*`WARNING:`* If the scripts produce runtime errors try to uninstall and reinstall gnuplot by adding `-qt` to the above commands

`Ubuntu`
~~~~
sudo apt-get update -y && sudo apt-get install -y gnuplot -qt
~~~~

`Solus`
~~~~
sudo eopkg install gnuplot -qt
~~~~

### Install make
Install  `make` in `ubuntu linux`,
~~~~
sudo apt-get update -y && sudo apt-get install build-essential -y
~~~~

Install  `make` in `solus linux`,
~~~~
sudo eopkg it -c system.devel 
~~~~

<br>

## Build

You need to have  `make` installed.

Run in `root` folder,
~~~~
make
~~~~

<br>

## Run the scripts
Run in `bin` folder,
~~~~
./problem1b 1
~~~~
to run the solution of 1b using the first input

~~~~
./problem1b 2
~~~~
to run the solution of 1b using the second input

~~~~
./problem1d
~~~~
to run the solution of 1d

~~~~
./problem2d
~~~~
to run the solution of 2d
