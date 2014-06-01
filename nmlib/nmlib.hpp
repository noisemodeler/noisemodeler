#ifndef NM_NMLIB_ALL
#define NM_NMLIB_ALL

#include <nmlib/model.hpp>
#include <nmlib/serialization.hpp>
#include <nmlib/codegeneration.hpp>

/**
 * @mainpage Noise Modeler Library Documentation
 *
 * ## Introduction
 *
 * Welcome to the reference for the noise modeler library, nmlib.
 *
 * The Noise Modeler Library is a library for specifying content generating
 * procedural functions based on noise in a platform independent manner.
 *
 * The prime example of such content is terrain heightmap generation.
 * With the help of this library, it is possible represent terrains
 * that are several times the size of the earth using only a few kilobytes.
 * This representation may be expanded during run-time in a game at high speed
 * by utilizing the GLSL code generation feature.
 *
 * ## Documentation overview
 *
 * The library is divided into four modules, and so is the documentation:
 *
 * * @ref model is the core part of the library, everything depends on this.
 * * @ref serialization is concerned with serialization and parsing of models.
 * * @ref codegeneration is responsible for generating code, such as GLSL to evaluate functions.
 * * @ref util contains utility functions for the library.
 *
 */

#endif // NM_NMLIB_ALL
