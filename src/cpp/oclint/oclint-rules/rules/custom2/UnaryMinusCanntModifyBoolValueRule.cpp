#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class UnaryMinusCanntModifyBoolValueRule : public AbstractASTVisitorRule<UnaryMinusCanntModifyBoolValueRule>
{
public:
    virtual const string name() const override
    {
        return "unary minus cannt modify bool value";
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

    bool isUnaryMinusBool(Expr* expr){
        bool hasMinus = false;
        while(expr){  
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }else if(isa<UnaryOperator>(expr)){
                UnaryOperator* uo = dyn_cast_or_null<UnaryOperator>(expr);
                if(uo->getOpcode()==UO_Minus){
                    expr = uo->getSubExpr();
                    hasMinus=true;
                }else return false;
            }else if(isa<DeclRefExpr>(expr)){
                return expr->getType()->isBooleanType() && hasMinus;
            }else
                break;
        }
        return false;
    }
    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *bo)
    {
        if(bo->getOpcode()==BO_Assign){
            if(bo->getLHS()->getType()->isBooleanType()){
                if(isUnaryMinusBool(bo->getRHS())){
                    string message = "Unary minus operator does not modify a bool type variable. Consider using the '!' operator.";
                    addViolation(bo, this, message);
                }
            }
        }
        return true;
    }
};

static RuleSet rules(new UnaryMinusCanntModifyBoolValueRule());
