#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class FormatStringIntoItselfInSprintfRule : public AbstractASTVisitorRule<FormatStringIntoItselfInSprintfRule>
{
public:
    virtual const string name() const override
    {
        return "format string into itself in sprintf";
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

    /* Visit CallExpr */
    bool VisitCallExpr(CallExpr *callExpr)
    {
        string name = callExpr->getDirectCallee()->getNameInfo().getAsString();
        if(name!="sprintf")return true;
        
        int num = callExpr->getNumArgs();
        if(num>2){
            string varName;
            if(refSamePointerVar(callExpr->getArg(0),callExpr->getArg(2), varName)){
                string message = "It is dangerous to print the string '"+varName+"' into itself.";
                addViolation(callExpr,this,message);
            }
        }
        
        return true;
    }
    
private:
    ValueDecl* getValueDecl(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<DeclRefExpr>(expr)){
            DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(expr);
            return declRefExpr->getDecl();
        }
        return nullptr;
    }
    bool refSamePointerVar(Expr* arg1,Expr* arg3, string& name)
    {
        ValueDecl* valueDecl1 = getValueDecl(arg1);
        ValueDecl* valueDecl3 = getValueDecl(arg3);
        if(valueDecl1)name= valueDecl1->getNameAsString();
        return valueDecl1 && valueDecl3 && valueDecl1==valueDecl3;
    }
     
};

static RuleSet rules(new FormatStringIntoItselfInSprintfRule());  