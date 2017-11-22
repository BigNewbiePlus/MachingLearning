#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class StringsWereConcatenatedButNotUtilizedRule : public AbstractASTVisitorRule<StringsWereConcatenatedButNotUtilizedRule>
{
public:
    virtual const string name() const override
    {
        return "strings were concatenated but not utilized";
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

    bool isStringDeclRefExpr(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = ice->getSubExpr();
        }
        if(isa<DeclRefExpr>(expr)){
            DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
            return dre->getType().getAsString()=="string";
        }
    }
    /* Visit ExprWithCleanups */
    bool VisitExprWithCleanups(ExprWithCleanups *ewc)
    {
        Expr* expr = ewc->getSubExpr();
        if(isa<CXXBindTemporaryExpr>(expr)){
            CXXBindTemporaryExpr* cbte = dyn_cast_or_null<CXXBindTemporaryExpr>(expr);
            expr = cbte->getSubExpr();
            if(isa<CXXOperatorCallExpr>(expr)){
                CXXOperatorCallExpr* cce = dyn_cast_or_null<CXXOperatorCallExpr>(expr);
                if(!cce->isAssignmentOp() && cce->getNumArgs()>0 && cce->getDirectCallee()->getNameInfo().getAsString()=="+" ){
                    if(isStringDeclRefExpr(cce->getArg(0))){
                        string message= "The strings were concatenated but are not utilized. Consider inspecting the expression.";
                        addViolation(ewc, this, message);
                    }
                }
            }
        }
        return true;
    }
};

static RuleSet rules(new StringsWereConcatenatedButNotUtilizedRule());
