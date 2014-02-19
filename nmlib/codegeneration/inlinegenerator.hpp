#ifndef NM_INLINEGENERATOR_HPP
#define NM_INLINEGENERATOR_HPP

#include <nmlib/codegeneration/idgenerator.hpp>
#include <nmlib/codegeneration/modulegenerator.hpp>

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/primitivemoduletype.hpp>
#include <nmlib/model/signalvalue.hpp>

#include <nmlib/util.hpp>

namespace nm {

struct Expression;
struct Assignment;
struct Variable;
struct Declaration;
struct FunctionCall;

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

    void generateFromLinks(const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
    void generateModule(Module& module, const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream &out);
    std::string getUniqueId();
    virtual std::unique_ptr<ModuleGenerator> getModuleGenerator(Module &module);

protected:
    //syntax tree generation helpers
    virtual void genTypeKeyword(const SignalType &signalType, std::ostream& out) = 0;
    virtual void genDeclaration(const Declaration &variable, std::ostream &out);
    virtual void genAssignment(const Assignment &assignment, std::ostream &out);
    virtual void genVariable(const Variable &variable, std::ostream &out);
    virtual void genValue(const SignalValue &value, std::ostream &out);
    virtual void genFunctionCall(FunctionCall &functionCall, std::ostream &out);


private:
    void generateOutputDeclarations(const std::vector<OutputRemap> &conversions, std::ostream& out);
    void generateInputDeclarations(Module&, std::ostream& out);
    void generateInputAssignments(const std::vector<InputRemap> &conversions, std::ostream& out);
    void generateOutputAssignments(const std::vector<OutputRemap> &conversions, std::ostream& out);

    IdGenerator m_idGenerator;

    friend struct Assignment;
    friend struct Variable;
    friend struct Expression;
    friend struct Value;
    friend struct Declaration;
    friend struct FunctionCall;
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
    Assignment(std::string l, std::string r):
        lhs{make_unique<Variable>(std::move(l))},
        rhs{make_unique<Variable>(std::move(r))}
    {}
     virtual void gen(InlineGenerator &g, std::ostream &out) override {
        g.genAssignment(*this, out);
    }
    std::unique_ptr<Variable> lhs;
    std::unique_ptr<Expression> rhs;
};

struct Declaration : public SyntaxNode {
    Declaration(SignalType t, std::string s):
        type{t},
        id{make_unique<Variable>(std::move(s))}
    {}
    Declaration(SignalType t, std::unique_ptr<Variable> v):
        type(t),
        id(std::move(v))
    {}
    virtual void gen(InlineGenerator &g, std::ostream &out) override {
        g.genDeclaration(*this, out);
    }
    SignalType type;
    std::unique_ptr<Variable> id;
};

struct Value : public Expression {
    Value(std::unique_ptr<SignalValue> v): value(std::move(v)){}
    virtual void gen(InlineGenerator &g, std::ostream &out) override {
        g.genValue(*value, out);
    }
    std::unique_ptr<SignalValue> value;
};

struct FunctionCall : public SyntaxNode {
    template<typename T, typename U, typename V>
    FunctionCall(T&& function, U&& ins, V&& outs):
        functionName{std::forward<T>(function)},
        inputs{std::forward<U>(ins)},
        outputs{std::forward<V>(outs)}
    {}
    virtual void gen(InlineGenerator &g, std::ostream &out) override {
        g.genFunctionCall(*this, out);
    }
    std::string functionName;
    std::vector<Variable> inputs;
    std::vector<Variable> outputs;
};

} // namespace nm

#endif // NM_INLINEGENERATOR_HPP
