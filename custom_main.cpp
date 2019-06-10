/*
Stochastically ranked evolutionary strategy sampler for zebrafish segmentation
Copyright (C) 2013 Ahmet Ay, Jack Holland, Adriana Sperlea, Sebastian Sangervasi

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
main.cpp contains the main, usage, and licensing functions.
Avoid putting functions in main.cpp that could be put in a more specific file.
*/

// Include MPI if compiled with it
#if defined(MPI)
	#undef MPI // MPI uses this macro as well, so temporarily undefine it
	#include <mpi.h> // Needed for MPI_Comm_rank, MPI_COMM_WORLD
	#define MPI // The MPI macro should be checked only for definition, not value
#endif

#if 0
#include "main.hpp" // Function declarations
#endif

#include "io/arg_parse.hpp"
#include "io/csvr.hpp"
#include "utility/common_utils.hpp"
#include "utility/style.hpp"
#include "model_impl.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

using style::Color;

int printing_precision = 6;

std::vector<double> her2014_scorer (const std::vector<Parameter_Set>& population) {
  //Create mutants

  //Create simulations
  /*Simulation_Set set(population,
                 parse_gradients("", 0), parse_perturbations(""),
                 arg_parse::get<int>("c", "cell-total", 200),
                 arg_parse::get<int>("w", "tissue_width", 50),
                 arg_parse::get<RATETYPE>("s", "step-size", 0.01),
                 arg_parse::get<int>("r", "rand-seed", std::time(nullptr))
                );*/


//Real analysis_interval = arg_parse::get<RATETYPE>("u", "anlys-intvl", 0.01);
//Real total_time = arg_parse::get<int>("t", "time-total", 600);

  //Create analyses

  //Run simulation
  std::cout << "Running simulations!\n";

  //Calculate scores
  std::vector<double> scores;
  for (unsigned int i = 0; i < population.size(); ++i) {
    scores.push_back((double)rand() / (double)RAND_MAX);
  }
  return scores;
}

/* main is called when the program is run and performs all program functionality
	parameters:
		argc: the number of command-line arguments
		argv: the array of command-line arguments
	returns: 0 on success, a positive integer on failure
	notes:
		Main should only delegate functionality; let the functions it calls handle specific tasks. This keeps the function looking clean and helps maintain the program structure.
	todo:
*/
int main (int argc, char** argv) {
	// Initialize MPI if compiled with it
	#if defined(MPI)
		MPI_Init(&argc, &argv);
	#endif
  arg_parse::init(argc, argv);

  if (arg_parse::get<bool>("h", "help", false) || arg_parse::get<bool>("H", "usage", false) || argc == 1) {
    std::cout << style::apply(Color::yellow) <<
      "[-h | --help | --usage]         " << style::apply(Color::green) <<
      "Print information about program's various command line arguments.\n"
      << style::reset();
    std::cout << style::apply(Color::yellow) <<
      "[-b | --param-bounds]   <string>" << style::apply(Color::green) <<
      "Path to file for lower and upper bounds\n"
      << style::reset();
    std::cout << style::apply(Color::yellow) <<
      "[-p | --population]        <int>" << style::apply(Color::green) <<
      "Size of a population\n" << style::reset();
    std::cout << style::apply(Color::yellow) <<
      "[-m | --miu | --parents] <int>" << style::apply(Color::green) <<
      "Size of the parent set between generations\n" << style::reset();
    std::cout << style::apply(Color::yellow) <<
      "[-n | --num-generations]   <int>" << style::apply(Color::green) <<
      "Number of generations\n" << style::reset();
    return 0;
  }
  int popc = arg_parse::get<int>("p", "population", 400);

  int miu = arg_parse::get<int>("m", "parents", NUM_PARAMS);

  std::string boundsfile;

  if (!arg_parse::get<std::string>("b", "param-bounds", &boundsfile, true)) {
    return -1;
  }
  std::cout << boundsfile << '\n';

  csvr csv_in(boundsfile);

  Parameter_Set lBounds, uBounds;

  if (!lBounds.import_from(csv_in) || !uBounds.import_from(csv_in)) {
    std::cout << style::apply(Color::red) << "ERROR, parameter bounds file does not contain precisely two sets\n" << style::reset();
  }

	return 0;
}
