#include <nmlib/model.hpp>
#include <nmlib/serialization.hpp>
#include <nmlib/codegeneration/glsl/glslgenerator.hpp>
#include <nmlib/util.hpp>

#include <fstream>
#include <sstream>

//TODO remove
#include <iostream>
#include <optional>

std::optional<std::string> readFile(std::string path)
{
    std::ifstream t(path);
    if(!t || !t.good()){
        return {};
    }
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

int main(int argc, char *argv[]){
    //handle arguments
    if(argc!=2){
        std::cout << "Example usage:\n\tnm terrain.nm.json\n";
        std::cout << "\nThis will generate a GLSL shader for the terrain function in the file \"terrain.nm.json\"\n";
        return EXIT_SUCCESS;
    }
    std::string filepath = argv[1];
    std::cout << "Generating code for terrain file: " << filepath << "\n";

    //read file
    auto maybeFile = readFile(filepath);
    if(!maybeFile){
        std::cerr << "Error: Couldn't open file: " << filepath << "\n";
        return EXIT_FAILURE;
    }

    //parse document
    std::string json = *maybeFile;
    nm::Parser parser;
    auto maybeTypeManager = parser.parseDocument(json);
    if(!maybeTypeManager){
        std::cerr << "Error: Couldn't parse document: " << filepath << "\n";
        return EXIT_FAILURE;
    }

    //get the first module type
    nm::TypeManager& typeManager =  **maybeTypeManager;
    unsigned int first = 0;
    auto moduleType = typeManager.getUserType(first);
    if(moduleType==nullptr){
        std::cerr << "Error: Empty document\n";
        return EXIT_FAILURE;
    }

    //get links
    //TODO support other configurations with multiple inputs and outputs
    auto inputLink = moduleType->getGraph()->getModule("inputs")->getInput(first);
    auto outputLink = moduleType->getGraph()->getModule("outputs")->getOutput(first);

    //generate GLSL
    std::string glslCode = nm::glsl::GlslGenerator::compileToGlslFunction(*inputLink, *outputLink, moduleType->getName());

    std::cout << glslCode << "\n";

    return EXIT_SUCCESS;
}
