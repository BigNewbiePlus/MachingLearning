#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class NonSensicalPointerComparisonRule : public AbstractASTVisitorRule<NonSensicalPointerComparisonRule>
{
public:
    virtual const string name() const override
    {
        return "non sensical pointer comparison";
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

    virtual void setUp() override {}
    virtual void tearDown() override {}
    
    /* Visit BinaryOperator*/
    bool VisitBinaryOperator(BinaryOperator *node)
    {
        string opcStr = node->getOpcodeStr();
        Expr* lhs = node->getLHS();
        Expr* rhs = node->getRHS();
        if(opcStr==">" || opcStr=="<" || opcStr==">=" || opcStr=="<="){
            if(isPointer(lhs)||isPointer(rhs)){
                addViolation(node, this, "NonSensicalPointerComparison!");
            }
        }
        return true;
    }
private:
    bool isPointer(Expr* expr){
        return expr->getType()->isPointerType();
    }
    
};

static RuleSet rules(new NonSensicalPointerComparisonRule());