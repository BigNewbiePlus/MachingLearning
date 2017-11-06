#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ConstantValueWithZeroPrefixRule : public AbstractASTVisitorRule<ConstantValueWithZeroPrefixRule>
{
public:
    virtual const string name() const override
    {
        return "constant value with zero prefix";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "custom";
    }

#ifdef DOCGEN
    virtual const std::string since() const override
    {
        return "0.12";
    }

    virtual const std::string description() const override
    {
        return ""; // TODO: fill in the description of the rule.
    }

    virtual const std::string example() const override
    {
        return R"rst(
.. code-block:: cpp

    void example()
    {
        // TODO: modify the example for this rule.
    }
        )rst";
    }

    /* fill in the file name only when it does not match the rule identifier
    virtual const std::string fileName() const override
    {
        return "";
    }
    */

    /* add each threshold's key, description, and its default value to the map.
    virtual const std::map<std::string, std::string> thresholds() const override
    {
        std::map<std::string, std::string> thresholdMapping;
        return thresholdMapping;
    }
    */

    /* add additional document for the rule, like references, notes, etc.
    virtual const std::string additionalDocument() const override
    {
        return "";
    }
    */

    /* uncomment this method when the rule is enabled to be suppressed.
    virtual bool enableSuppress() const override
    {
        return true;
    }
    */
#endif

    virtual void setUp() override {
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    /* Visit IntegerLiteral */
    bool VisitIntegerLiteral(IntegerLiteral *node)
    {
        string intStr = int2str(node);
        if(startWithZero(intStr)){
            addViolation(node, this,"Be advised that the utilized constant value is represented by an octal form.");
        }
        return true;
    }
    
private:
    bool startWithZero(string str){
        
        if(str.size()>2 && str[0]=='0' && str[1]!='x' && str[1]!='X'){
            return true;
        }
        return false;
    }
    std::string int2str(IntegerLiteral *node) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(node->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(node->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    } 
private:
    SourceManager* sm;
     
};

static RuleSet rules(new ConstantValueWithZeroPrefixRule()); 