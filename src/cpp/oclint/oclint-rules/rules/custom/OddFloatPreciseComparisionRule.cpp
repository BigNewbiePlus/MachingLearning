#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class OddFloatPreciseComparisionRule : public AbstractASTVisitorRule<OddFloatPreciseComparisionRule>
{
public:
    virtual const string name() const override
    {
        return "odd float precise comparision";
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
    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *binaryOperator)
    {
        
        BinaryOperatorKind bok = binaryOperator->getOpcode();
        if(bok==BO_EQ || bok==BO_NE){
            
            Expr* lhs = binaryOperator->getLHS();
            Expr* rhs = binaryOperator->getRHS();
            
            bool isfloat1 = lhs->getType()->isFloatingType();
            bool isfloat2 = rhs->getType()->isFloatingType();
            
            if(isfloat1 && isfloat2)
            {
                string message = "An odd precise comparison: "+expr2str(binaryOperator)
                +". It's probably better to use a comparison with defined precision: fabs(A - B) '<' Epsilon.";
                addViolation(binaryOperator, this, message);
            }    
        }
        return true;
    }
    
private:
    std::string expr2str(Expr *expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
    
private:
    SourceManager* sm;
};

static RuleSet rules(new OddFloatPreciseComparisionRule());