#include "Grid.h"
#include <string>

// Explicit instantiation to make sure we always generate the code and thus generate the member functions letting us check their syntax.
template class Core::Grid<std::string>;
