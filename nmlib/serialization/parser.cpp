#include "parser.hpp"

#include <nmlib/model/graph.hpp>
#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/module.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/inputlink.hpp>

//TODO get rapidjson to fix these warnings
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <rapidsjon/document.h>

#include <iostream>
#include <cstdio>

namespace nm {

namespace {

optional<std::pair<std::string, std::string> > parseDotPair(const std::string &sourceString){
    //TODO error checking
    auto dotPos = sourceString.find(".");
    auto sourceModuleString = sourceString.substr(0, dotPos);
    auto outputLinkString = sourceString.substr(dotPos+1);
    return {{sourceModuleString, outputLinkString}};
}

//std::vector<std::string> split(const std::string& input, const std::string& regex) {
//    // passing -1 as the submatch index parameter performs splitting
//    std::sregex_token_iterator
//        first{input.begin(), input.end(), regex, -1},
//        last;
//    return {first, last};
//}
optional<SignalType> parseSignalType(const rapidjson::Value &signalTypeValue)
{
    if(!signalTypeValue.IsString()){
        std::cerr << "Signal type is not a string\n";
        return{};
    }
    int dimensionality{-1};
    if(sscanf(signalTypeValue.GetString(), "%df", &dimensionality) == EOF){
        std::cerr << "Couldn't parse signal type\n";
        return {};
    }
    return {SignalType{dimensionality}};
}

bool parseModule(const rapidjson::Value &moduleValue, const nm::TypeManager &typeManager, Graph &graph)
{
    if(!moduleValue["name"].IsString()){
        return false;
    }
    if(!moduleValue["type"].IsString()){
        return false;
    }
    std::string typeString = moduleValue["type"].GetString();
    std::string nameString = moduleValue["name"].GetString();
    auto type = typeManager.getType(typeString);
    if(type == nullptr){
        std::cerr << "Unknown type: " <<  typeString << std::endl;
        return false;
    }
    auto module = make_unique<Module>(*type, nameString);
    //parse inputs
    auto &inputsValue = moduleValue["inputs"];
    if(!inputsValue.IsNull()){
        if(!inputsValue.IsObject()){
            std::cerr << "Invalid input\n";
            return false;
        }
        for(auto it = inputsValue.MemberBegin(); it != inputsValue.MemberEnd(); ++it){
            if(!it->name.IsString()){
                std::cerr << "Invalid member in inputs\n";
                return false;
            }

            //find out which input to connect
            auto inputName = it->name.GetString();
            auto inputLink = module->getInput(inputName);
            if(inputLink==nullptr){
                std::cerr << "ModuleType \"" << module->getName() << "\" has no input named \"" << inputName << "\"\n";
                return false;
            }

            //if it's a string, connect it to the correct output
            if(it->value.IsString()){
                //find out which outputlink to connect to
                auto sourceString = it->value.GetString();
                auto sourcePair = parseDotPair(sourceString);
                if(!sourcePair){
                    std::cerr << "Couldn't parse input string\n";
                    return false;
                }
                auto sourceModule = graph.getModule(sourcePair->first);
                if(sourceModule==nullptr){
                    std::cerr << "No module named \"" << sourcePair->first << "\" in graph\n"; // \"" << owner.getName() << "\"\n";
                    return false;
                }

                auto sourceOutputLink = sourceModule->getOutput(sourcePair->second);
                if(sourceOutputLink==nullptr){
                    std::cerr << "No output named \"" << sourcePair->second << "\" in module \"" << sourceModule->getName() << "\"\n";
                    return false;
                }
                inputLink->link(*sourceOutputLink);
            } else if(it->value.IsArray()){
                std::vector<float> values;
                if(it->value.Size() != static_cast<unsigned int>(inputLink->getModuleInput().getSignalType().dimensionality)){
                    std::cerr << "Wrong dimensionality for input " << inputName << "\n";
                    return false;
                }
                for(rapidjson::SizeType i = 0; i < it->value.Size(); ++i){
                    auto &arrayEntry = it->value[i];
                    if(!arrayEntry.IsNumber()){
                        std::cerr << "Array member is not a number";
                        return false;
                    }
                    values.push_back(arrayEntry.GetDouble());
                }
                inputLink->setUnlinkedValue(values);

            } else if(it->value.IsNumber() && inputLink->getModuleInput().getSignalType().dimensionality == 1){
                inputLink->setUnlinkedValue(it->value.GetDouble());
            } else {
                std::cerr << "Unexpected type value for input value " << inputName << "\n";
                return false;
            }
        }

    }
    graph.addModule(std::move(module));
    return true;
}

optional<std::unique_ptr<ModuleType> > parseModuleType(const rapidjson::Value &type, const TypeManager& typeManager)
{
    auto &nameValue = type["name"];
    if(!nameValue.IsString()){
        std::cerr << "Module missing required field \"name\"\n";
        return {};
    }
    std::string moduleTypeName = nameValue.GetString();
    std::string description;
    auto &descriptionValue = type["description"];
    if(descriptionValue.IsString()){
        description = descriptionValue.GetString();
    }

    auto moduleType = make_unique<ModuleType>(moduleTypeName, description);

    //parse inputs
    auto &inputsValue = type["inputs"];
    if(!inputsValue.IsNull()){
        if(!inputsValue.IsArray()){
            std::cerr << "inputs is not an array\n";
            return {};
        }
        for(rapidjson::SizeType i = 0; i < inputsValue.Size(); i++){
            auto &inputValue = inputsValue[i];
            std::string name = inputValue["name"].GetString();
            auto maybeSignalType = parseSignalType(inputValue["type"]);
            if(!maybeSignalType){
                std::cerr << "Error parsing signal type";
                return {};
            }
            moduleType->addInput(name, *maybeSignalType);
        }
    }

    //parse submodules
    auto &modulesValue = type["modules"];
    if(!modulesValue.IsNull()){
        if(!modulesValue.IsArray()){
            std::cerr << "modules is not an array\n";
            return {};
        }
        for(rapidjson::SizeType i = 0; i<modulesValue.Size(); i++){
            auto success = parseModule(modulesValue[i], typeManager, *moduleType->getGraph());
            //TODO consider continuing without this module?
            if(!success){
                std::cerr << "Couldn't parse Module\n";
                return {};
            }
        }
    }

    //parse outputs
    auto &outputsValue = type["outputs"];
    if(!outputsValue.IsNull()){
        if(!outputsValue.IsArray()){
            std::cerr << "outputs is not an array\n";
            return {};
        }
        for(rapidjson::SizeType i = 0; i < outputsValue.Size(); i++){
            auto &outputValue = outputsValue[i];
            if(
                    !outputValue["name"].IsString() ||
                    (!outputValue["source"].IsString() && !outputValue["source"].IsArray())
                    ){
                std::cerr << "Missing required field name or source\n";
                return {};
            }
            std::string externalName = outputValue["name"].GetString();
            if(outputValue["source"].IsString()){
                std::string sourceString = outputValue["source"].GetString();
                //dotpos stuff
                auto sourcePair = parseDotPair(sourceString);
                if(!sourcePair){
                    std::cerr << "Couldn't parse source string: " << sourceString << "\n";
                    return {};
                }
                Module* module = moduleType->getGraph()->getModule(sourcePair->first);
                if(module==nullptr){
                    std::cerr << "Couldn't find the output node for: " << sourceString << "\n";
                    return {};
                }
                OutputLink* outputLink = module->getOutput(sourcePair->second);
                if(outputLink==nullptr){
                    std::cerr << "Couldn't find an output named: " << sourcePair->second << "\n";
                    return {};
                }
                if(moduleType->exportInternalOutput(*outputLink, externalName) == nullptr){
                    std::cerr << "Error exporting output: " << sourcePair->second << "\n";
                    return {};
                }
            } else if(outputValue["source"].IsArray()){
                std::cerr << "TODO: implement parsing of constant outputs of module types.\n";
                //TODO parse and use signalValue instead
                SignalType signalType{static_cast<int>(outputValue["source"].Size())};
                moduleType->addOutput(externalName, signalType);
            }
        }
    }

    return {std::move(moduleType)};
}

bool parseModuleTypeArray(const rapidjson::Value &array, TypeManager &typeManager)
{
    if(!array.IsArray()){
        std::cerr << "Tried to parse an array that wasn't an array.\n";
        return false;
    }

    //we want to use indices instead of names, this makes it easier
    std::map<std::string, int> nameToIndexMap;
    for(rapidjson::SizeType i = 0; i < array.Size(); i++){
        //TODO verify types
        nameToIndexMap[array[i]["name"].GetString()] = i;
    }

    //create a list of dependencies
    struct Node {
        int id;
        std::vector<int> edges;
        bool visited;
        bool finished;
        Node():id(-1), edges(), visited(false), finished(false){}
    };

    std::vector<Node> dependencies(array.Size());
    for(rapidjson::SizeType i = 0; i < array.Size(); i++){
        dependencies[i].id = i;
        //TODO verify types
        const rapidjson::Value &moduleArray = array[i]["modules"];
        for(rapidjson::SizeType i = 0; i < moduleArray.Size(); ++i){
            //TODO verify types
            std::string typeName = moduleArray[i]["type"].GetString();
            if(typeName == "inputs" || typeName == "outputs")continue;
            //TODO verify types
            if(typeManager.getBuiltinType(typeName) != nullptr)continue;
            auto it = nameToIndexMap.find(typeName);
            if(it == nameToIndexMap.end()){
                std::cerr << "Unknown module type: " << typeName << "\n";
                return false;
            }
            dependencies[i].edges.push_back(nameToIndexMap[typeName]);
        }
    }

    std::function<bool(Node&, std::function<void(Node&)>)> traverseTopological = [&](Node& node, std::function<void(Node&)> visitor) -> bool {
        if(node.finished)return true; //we've already been here
        if(node.visited)return false; //means there is a cycle
        node.visited = true; //mark this node, so we now if there's a cycle
        for(int edge : node.edges){
            //traverse children
            if(!traverseTopological(dependencies[edge], visitor)){
                std::cerr << "Error traversing topologically loop at " << node.id << "\n";
                return false;
            }
        }
        visitor(node);
        node.finished = true;
        return true;
    };

    for(auto dep : dependencies){
        bool fail = false;
        std::function<void(Node&)> v = [&](Node& node) {
            auto maybeModuleType = parseModuleType(array[node.id], typeManager);
            if(!maybeModuleType){
                std::cerr << "Error parsing module type " << node.id << "\n";
                fail = true;
                return;
            }
            std::unique_ptr<ModuleType> &moduleTypePtr = *maybeModuleType;
            if(!typeManager.addUserType(std::move(moduleTypePtr))){
                std::cerr << "Couldn't add type to typeManager.\n";
                fail = true;
                return;
            }
        };
        traverseTopological(dep, v);
        if(fail){
            std::cerr << "Error parsing module types\n";
            return false;
        }
    }
    return true;
}

} // namespace

Parser::Parser()
{
}

optional<std::unique_ptr<TypeManager> > Parser::parseDocument(std::string json)
{
    rapidjson::Document document;
    document.Parse<0>(json.c_str());

    if(document.HasParseError()){
        std::cerr << "Couldn't parse json document\n";
        return {};
    }

    auto &moduleTypes = document["moduleTypes"];

    if(moduleTypes.IsNull()){
        std::cerr << "moduleTypes not present in root of document\n";
        return {};
    }

    auto typeManager = make_unique<TypeManager>();
    typeManager->initBuiltinTypes();
    if(!parseModuleTypeArray(moduleTypes, *(typeManager.get()))){
        return {};
    }
    return {std::move(typeManager)};
}

} // namespace nm
