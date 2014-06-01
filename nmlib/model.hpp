/**
 * @file model.hpp
 * @brief The model module
 * @ingroup model
 *
 * @defgroup model model
 * @brief Graph representation of a procedural generator
 *
 * The model contains classes for representing module types and graphs of modules.
 *
 * The top-level entity, is the TypeManager, which may contain several ModuleType%s.
 * A ModuleType represents a mathematical function or algorithm. It is either a
 * primitive type defined by the library, or a composite type described as a 
 * Graph of Module%s.
 *
 * When a ModuleType is described by a Graph of Module%s, it is called a 
 * composite type.
 *
 * A Graph is a directed acyclic graph of function calls (Module%s). It is
 * a similar concept to what is commonly known as an expression tree.
 * 
 * Each node in the Graph, is called a Module. A module represents a function
 * call, and has a corresponding ModuleType, and information about the inputs
 * and outputs of the function call. A Module has several InputLink%s that
 * may be connected to OutputLink%s of other Module%s.
 *
 * Here is an example of how the expression `abs(0.25+fbm(x,y))` may be created
 * using the model:
 *
 * ~~~{.cpp}
 *     //A type manager holds information about module types
 *     TypeManager typeManager;
 *
 *     //Initialize common module types, such as add, abs, and fbm2d
 *     typeManager.initBuiltinTypes();
 *
 *     //create a module type representing our terrain function
 *     ModuleType *terrainType = typeManager.createModuleType("terrain")
 *     
 *     //Add inputs and outputs to the module type
 *     //create a 2D input, "pos"
 *     terrainType->addInput("pos", SignalType{2})
 *     //create a 1D output, "height"
 *     terrainType->addOutput("position", SignalType{2})
 *     
 *     //get a handle for the graph of the module type
 *     Graph *graph = terrainType.getGraph();
 *     Module *inputs = graph->getModule("inputs");
 *     Module *outputs = graph->getModule("outputs");
 *     
 *     //create modules for the fbm (2d), add (1d), abs (1d)
 *     Module* fbmModule = graph->createModule(*typeManager.getBuiltinType("fbm2"));
 *     Module* addModule = graph->createModule(*typeManager.getBuiltinType("add1"));
 *     Module* absModule = graph->createModule(*typeManager.getBuiltinType("abs"));
 *
 *     //connect fbm to position
 *     fbmModule->getInput("pos")->link(*inputs->getOutput("pos"));
 *
 *     //connect add input to fbm output
 *     addModule->getInput("lhs")->link(*fbmModule->getOutput("result"));
 *     //set the right hand side to 0.25
 *     addModule->getInput("rhs")->setUnlinkedValue(SignalValue({0.25}));
 *
 *     //set abs source to add output
 *     absModule->getInput("source")->link(*addModule->getOutput("result"));
 *
 *     //connect abs output to module type output
 *     outputs->getInput("height")->link(*absModule->getOutput("result"));
 *
 *     //we now have a complete model for a heightmap generating
 *     //module type: terrainType
 *     //use the terrainType to evaluate some terrain, or serialize it to disk
 * ~~~
 * 
 */

#ifndef MODEL_HPP
#define MODEL_HPP

#include <nmlib/model/module.hpp>
#include <nmlib/model/moduletype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/signaltype.hpp>
#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/graph.hpp>

#endif // MODEL_HPP
