#ifndef NM_INLINEGENERATOR_HPP
#define NM_INLINEGENERATOR_HPP

#include <nmlib/codegeneration/idgenerator.hpp>
#include <nmlib/codegeneration/modulegenerator.hpp>

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/primitivemoduletype.hpp>

namespace nm {

class SignalValue;

class InlineGenerator {
public:
    struct InputRemap {
        std::string externalName;
        InputLink* inputLink;
    };
    struct OutputRemap {
        std::string externalName;
        OutputLink* outputLink;
    };

//    class Expression {
//    public:
//        virtual gen(InlineGenerator &gen,std::ostream& out) = 0;
//        virtual ~Expression();
//    };
//    class Variable : public Expression {
//    public:
//        Variable(std::string id):m_id(id){}
//        virtual gen(InlineGenerator &gen, std::ostream &out){
//            gen.genVariable(*this);
//        }
//        std::string m_id;
//    };
//    class Assignment : public Expression {
//    public:
//        Assignment(std::unique_ptr<Variable> id, std::unique_ptr<Expression> value):
//            lhs(id),
//            rhs(value)
//        {}
//        virtual gen(InlineGenerator &gen, std::ostream &out){
//            gen.genAssignment(*this);
//        }

//        std::unique_ptr<Variable> lhs;
//        std::unique_ptr<Expression> rhs;
//    };

    explicit InlineGenerator();
    virtual void generateFromLinks(const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
    virtual void generateModule(Module& module, const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
    std::string getUniqueId();
    virtual std::unique_ptr<ModuleGenerator> getModuleGenerator(Module &module);
//    virtual std::unique_ptr<DefaultsGenerator> getZeroDefaultsGenerator(const Module& module) = 0;
    virtual void assignVariable(std::string name, const SignalValue &value, std::ostream &out);
    virtual std::string generateValue(const SignalValue &value);
private:
    virtual void generateOutputDeclarations(const std::vector<OutputRemap> &conversions, std::ostream& out);
    virtual void generateInputDeclarations(Module&, std::ostream& out);
    virtual void generateInputAssignments(const std::vector<InputRemap> &conversions, std::ostream& out);
    virtual void generateOutputAssignments(const std::vector<OutputRemap> &conversions, std::ostream& out);

    //very low level helper functions
    virtual void generateTypeKeyword(const SignalType &signalType, std::ostream& out);

    IdGenerator m_idGenerator;
};

} // namespace nm

#endif // NM_INLINEGENERATOR_HPP
