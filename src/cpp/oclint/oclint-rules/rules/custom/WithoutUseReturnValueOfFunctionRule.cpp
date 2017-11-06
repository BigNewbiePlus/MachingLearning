#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include <fstream>
using namespace std;
using namespace clang;
using namespace oclint;

class WithoutUseReturnValueOfFunctionRule : public AbstractASTVisitorRule<WithoutUseReturnValueOfFunctionRule>
{
public:
    virtual const string name() const override
    {
        return "without use return value of function";
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

    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *compoundStmt)
    {
        for(clang::CompoundStmt::body_iterator body_it = compoundStmt->body_begin(); body_it!=compoundStmt->body_end();body_it++){
            Stmt* stmt = *body_it;
            checkStmt(stmt);
            
        }
        return true;
    }
private:
    void checkStmt(Stmt* stmt){
        
        FunctionDecl* funcDecl = NULL;
        if(isa<CXXMemberCallExpr>(stmt)){
                CXXMemberCallExpr* cxxMemberCallExpr = dyn_cast_or_null<CXXMemberCallExpr>(stmt);
                funcDecl = cxxMemberCallExpr->getDirectCallee();   
            
        }else if(isa<CallExpr>(stmt)){
            CallExpr* callExpr = dyn_cast_or_null<CallExpr>(stmt);
            funcDecl = callExpr->getDirectCallee();
        }
        if(!funcDecl)return;
        
        if(!funcDecl->getReturnType()->isVoidType()){//返回值不为空
            string funcName = funcDecl->getNameInfo ().getAsString();
            string message = "The return value of function '"+funcName+"' is required to be utilized.";
            addViolation(stmt,this,message);
        }
        
    }

};

static RuleSet rules(new WithoutUseReturnValueOfFunctionRule());  