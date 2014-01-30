#include "parser.hpp"

#include <rapidsjon/document.h>

#include <iostream>
#include <cstdio>

namespace nm {

namespace {

//std::vector<std::string> split(const std::string& input, const std::string& regex) {
//    // passing -1 as the submatch index parameter performs splitting
//    std::sregex_token_iterator
//        first{input.begin(), input.end(), regex, -1},
//        last;
//    return {first, last};
//}
//    int dimensionality{-1};
//    if(sscanf(signalTypeString.c_str(), "%df", &dimensionality) == EOF){
//        std::cerr << "Couldn't parse signal type";
//        return {};
//    }

optional<std::unique_ptr<ModuleType> > parseModule(const rapidjson::Value &moduleValue)
{
}

optional<std::unique_ptr<ModuleType> > parseModuleType(const rapidjson::Value &type)
{
    auto &nameValue = type["name"];
    if(!nameValue.IsString()){
        std::cerr << "Module missing required field \"name\"\n";
        return {};
    }
    std::string name = nameValue.GetString();
    std::string description;
    auto &descriptionValue = type["description"];
    if(descriptionValue.IsString()){
        description = descriptionValue.GetString();
    }

    auto moduleType = std::unique_ptr<CompositeModuleType>{new CompositeModuleType(name, description)};

    //parse Inputs
    std::vector<ModuleInput> inputs;
    auto &inputsValue = type["inputs"];
    if(!inputsValue.IsNull()){
        if(!inputsValue.IsArray()){
            return {};
        }
        for(rapidjson::SizeType i = 0; i < inputsValue.Size(); i++){
                string name = inputValue["name"].GetString();
                string source = inputValue["source"].GetString();
                auto maybeInput = parseModuleInput(inputsValue[i], *moduleType);
            if(!maybeInput){
                return {};
            }
            inputs.push_back(*maybeInput);
        }
    }
    for(auto input : inputs){
        moduleType->addInput(input);
    }

    //parse submodules

    return {std::move(moduleType)};
}

bool parseModuleTypeArray(const rapidjson::Value &array, TypeManager &typeManager)
{
    if(!array.IsArray()){
        std::cerr << "Tried to parse an array that wasn't an array";
        return {};
    }
    std::map <std::string, std::unique_ptr<ModuleType>> moduleTypes{};
    for(rapidjson::SizeType i = 0; i < array.Size(); i++){
        auto maybeModuleType = parseModuleType(array[i]);
        if(!maybeModuleType){
            return false;
        }
        auto &moduleTypePtr = *maybeModuleType;
        if(!typeManager.addType(std::move(moduleTypePtr))){
            std::cerr << "Couldn't add type to typeManager.\n";
            return false;
        }
    }
    return true;
}

} // namespace

Parser::Parser()
{
}

optional<std::unique_ptr<TypeManager> > Parser::parseDocument(std::string input)
{
    rapidjson::Document document;
    document.Parse<0>(input.c_str());

    if(document.HasParseError()){
        std::cerr << "Couldn't parse json document\n";
        return {};
    }

    auto &moduleTypes = document["moduleTypes"];

    if(moduleTypes.IsNull()){
        std::cerr << "moduleTypes not present in root of document\n";
        return {};
    }

    std::unique_ptr<TypeManager> typeManager{new TypeManager()};
    if(!parseModuleTypeArray(moduleTypes, *(typeManager.get()))){
        return {};
    }
    return {std::move(typeManager)};
}

} // namespace nm
