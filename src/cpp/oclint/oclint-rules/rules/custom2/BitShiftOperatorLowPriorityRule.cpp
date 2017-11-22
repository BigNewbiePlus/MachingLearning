#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class BitShiftOperatorLowPriorityRule : public AbstractASTVisitorRule<BitShiftOperatorLowPriorityRule>
{
public:
    virtual const string name() const override
    {
        return "bit shift operator low priority";
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

    bool isSimpleOperator(Expr* expr, string& simpOp){
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
            BinaryOperatorKind bok = bo->getOpcode();
            if(bok==BO_Add || bok==BO_Sub || bok==BO_Mul || bok==BO_Div){
                simpOp = bo->getOpcodeStr().str();
                return true;
            }
        }
        return false;
    }
    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *bo)
    {
        BinaryOperatorKind bok = bo->getOpcode();
        if(bok==BO_Shl || bok==BO_Shr){
            string shifOp = bo->getOpcodeStr().str();
            string simpOp;
            if(isSimpleOperator(bo->getLHS(), simpOp) || isSimpleOperator(bo->getRHS(), simpOp)){
                string message = "The priority of the '"+simpOp+"' operation is higher than that of the '"+shifOp+"' operation. It's possible that parentheses should be used in the expression.";
                addViolation(bo, this, message);
            }
        }
        return true;
    }
};

static RuleSet rules(new BitShiftOperatorLowPriorityRule());
