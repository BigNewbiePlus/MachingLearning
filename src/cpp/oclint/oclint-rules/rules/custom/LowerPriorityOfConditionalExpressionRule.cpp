#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include<fstream>
using namespace std;
using namespace clang;
using namespace oclint;

class LowerPriorityOfConditionalExpressionRule : public AbstractASTVisitorRule<LowerPriorityOfConditionalExpressionRule>
{
public:
    virtual const string name() const override
    {
        return "lower priority of conditional expression";
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
        
    }
    virtual void tearDown() override {
        
    }

   /* Visit ConditionalOperator */
    bool VisitConditionalOperator(ConditionalOperator *node)
    {
        Expr* condExpr = node->getCond();
        if(isa<ImplicitCastExpr>(condExpr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(condExpr);
            condExpr = implicitCastExpr->getSubExpr();
        }
        if(isa<BinaryOperator>(condExpr)){//条件表达式条件是二元是，可能存在优先级问题
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(condExpr);
            string opcStr = binaryOperator->getOpcodeStr();
            string message = "Perhaps the '?:' operator works in a different way than it was expected.The '?:' operator has a lower priority than the '"+opcStr+"' operator.";
            
            addViolation(node, this, message);
        }
        return true;
    }
private:

};

static RuleSet rules(new LowerPriorityOfConditionalExpressionRule());
