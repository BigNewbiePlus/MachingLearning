#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class AssignAndComparisionExpressionErrorRule : public AbstractASTVisitorRule<AssignAndComparisionExpressionErrorRule>
{
public:
    virtual const string name() const override
    {
        return "assign and comparision expression error";
    }

    virtual int priority() const override
    {
        return 3;
    }

    virtual const string category() const override
    {
        return "custom2";
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

    virtual void setUp() override {}
    virtual void tearDown() override {}

    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *binaryOperator)
    {
        if(binaryOperator->getOpcode()==BO_Assign){
            Expr* rhs = binaryOperator->getRHS();
            if(isa<ImplicitCastExpr>(rhs)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(rhs);
                Expr* subExpr = implicitCastExpr->getSubExpr();
                if(isa<BinaryOperator>(subExpr)){
                    BinaryOperator* rbo = dyn_cast_or_null<BinaryOperator>(subExpr);
                    BinaryOperatorKind bok = rbo->getOpcode();
                    if(bok==BO_GT || bok==BO_LT || bok==BO_GE || bok==BO_LE || bok==BO_EQ || bok==BO_NE){
                        string message = "Consider reviewing the expression of the 'A = B == C' kind. The expression is calculated as following: 'A = (B == C)'.";
                        addViolation(binaryOperator, this, message);
                    }
                }
            }
        }
        return true;
    }

};

static RuleSet rules(new AssignAndComparisionExpressionErrorRule());
