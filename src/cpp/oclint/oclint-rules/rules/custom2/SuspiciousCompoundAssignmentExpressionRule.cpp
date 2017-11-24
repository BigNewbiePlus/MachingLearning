#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class SuspiciousCompoundAssignmentExpressionRule : public AbstractASTVisitorRule<SuspiciousCompoundAssignmentExpressionRule>
{
public:
    virtual const string name() const override
    {
        return "suspicious compound assignment expression";
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

    string getDeclRefExprName(Expr* expr){
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
            expr = bo->getLHS();
        }
        if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
        }
        
        if(isa<DeclRefExpr>(expr)){
            DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
            return dre->getNameInfo().getAsString();
        }
        return "";
    }
    /* Visit CompoundAssignOperator */
    bool VisitCompoundAssignOperator(CompoundAssignOperator *cso)
    {
        Expr* lhs = cso->getLHS();
        Expr* rhs = cso->getRHS();
        string name1 = getDeclRefExprName(lhs);
        string name2 = getDeclRefExprName(rhs);
        if(name1==name2){
            string message = "A compound assignment expression 'X += X + N' is suspicious. Consider inspecting it for a possible error.";
            addViolation(cso, this, message);
        }
        return true;
    }
};

static RuleSet rules(new SuspiciousCompoundAssignmentExpressionRule());
