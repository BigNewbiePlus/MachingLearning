#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class VariableInitializedThroughItselfRule : public AbstractASTVisitorRule<VariableInitializedThroughItselfRule>
{
public:
    virtual const string name() const override
    {
        return "variable initialized through itself";
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

    //获取模式: T foo = foo = x;
    bool getAssignPattern(Expr* expr, string& name){
        while(expr){
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }else if(isa<BinaryOperator>(expr)){
                BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
                expr = bo->getLHS();
            }else if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
                name = dre->getNameInfo().getAsString();
                return true;
            }else if(isa<CXXConstructExpr>(expr)){
                CXXConstructExpr* cxxce = dyn_cast_or_null<CXXConstructExpr>(expr);
                if(cxxce->getNumArgs()==1){
                    expr = cxxce->getArg(0);
                }else return false;
            }else if(isa<CXXOperatorCallExpr>(expr)){
                CXXOperatorCallExpr* cxxoce = dyn_cast_or_null<CXXOperatorCallExpr>(expr);
                if(cxxoce->isAssignmentOp()){
                    expr = cxxoce->getArg(0);
                }else return false;
            }else
                break;
        }
        return false;
    }
    /* Visit VarDecl */
    bool VisitVarDecl(VarDecl *vd)
    {
        if(vd->hasInit()){
            Expr* expr = vd->getInit();
            //获取模式T foo = foo = x;
            string name2;
            if(getAssignPattern(expr, name2)){
                string name1 = vd->getNameAsString();
                if(name1==name2){
                    string message = "Consider inspecting the 'T foo = foo = x;' expression. It is odd that variable is initialized through itself.";
                    addViolation(vd, this, message);
                }
            }
        }
        return true;
    }
};

static RuleSet rules(new VariableInitializedThroughItselfRule());
