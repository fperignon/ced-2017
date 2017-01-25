#ifndef TOOLS_INTERFACE_HPP
#define TOOLS_INTERFACE_HPP
#include "tools_config.hpp"
#include "tools.hpp"

// Boost, fftw and mkl interfaces
// are optional. CMake is supposed
// to control this, depending on
// the availability of those libraries
// on the system, thanks to the
// generated file tools_config.hpp.

// Boost
#ifdef HAS_BOOST
#include "linearAlgebraTools.hpp"
#endif

// fftw
#ifdef HAS_FFTW
#include "fftw_tools.hpp"
#endif

// mkl
#ifdef HAS_MKL
#include "mkl_interface.hpp"
#endif

#endif
