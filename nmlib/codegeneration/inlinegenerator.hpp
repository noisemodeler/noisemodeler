#ifndef NM_INLINEGENERATOR_HPP
#define NM_INLINEGENERATOR_HPP

#include <nmlib/codegeneration/idgenerator.hpp>
#include <nmlib/codegeneration/modulegenerator.hpp>

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/primitivemoduletype.hpp>
#include <nmlib/model/signalvalue.hpp>

namespace nm {

class Expression;
class Assignment;
class Variable;

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
    explicit InlineGenerator();
    virtual void generateFromLinks(const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
    virtual void generateModule(Module& module, const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
    std::string getUniqueId();
    virtual std::unique_ptr<ModuleGenerator> getModuleGenerator(Module &module);
private:
    virtual void generateOutputDeclarations(const std::vector<OutputRemap> &conversions, std::ostream& out);
    virtual void generateInputDeclarations(Module&, std::ostream& out);
    virtual void generateInputAssignments(const std::vector<InputRemap> &conversions, std::ostream& out);
    virtual void generateOutputAssignments(const std::vector<OutputRemap> &conversions, std::ostream& out);

    //syntax tree generation helpers
    virtual void genTypeKeyword(const SignalType &signalType, std::ostream& out);
    virtual void genAssignment(const Assignment &assignment, std::ostream &out);
    virtual void genVariable(const Variable &variable, std::ostream &out);
    virtual void genValue(const SignalValue &value, std::ostream &out);

    IdGenerator m_idGenerator;

    friend struct Assignment;
    friend struct Variable;
    friend struct Expression;
    friend struct Value;
};

struct SyntaxNode {
    virtual void gen(InlineGenerator &gen,std::ostream& out) = 0;
    virtual ~SyntaxNode(){}
};

struct Expression : public SyntaxNode {
};

struct Variable : public Expression {
    Variable(std::string id):m_id(id){}
    virtual void gen(InlineGenerator &g, std::ostream &out) override {
        g.genVariable(*this, out);
    }
    std::string m_id;
};

struct Assignment : public Expression {
    Assignment(std::unique_ptr<Variable> id, std::unique_ptr<Expression> value):
        lhs(std::move(id)),
        rhs(std::move(value))
    {}
    virtual void gen(InlineGenerator &g, std::ostream &out) override {
        g.genAssignment(*this, out);
    }
    std::unique_ptr<Variable> lhs;
    std::unique_ptr<Expression> rhs;
};

struct Value : public Expression {
    Value(std::unique_ptr<SignalValue> v): value(std::move(v)){}
    virtual void gen(InlineGenerator &g, std::ostream &out) override {
        g.genValue(*value, out);
    }
    std::unique_ptr<SignalValue> value;
};
} // namespace nm

#endif // NM_INLINEGENERATOR_HPP
