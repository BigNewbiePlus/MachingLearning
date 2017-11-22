#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class IteratorInitAndFinalValueDifferInForLoopRule : public AbstractASTVisitorRule<IteratorInitAndFinalValueDifferInForLoopRule>
{
public:
    virtual const string name() const override
    {
        return "iterator init and final value differ in for loop";
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


    string getNameFromExpr(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = ice->getSubExpr();
        }
        if(isa<DeclRefExpr>(expr)){
            DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
            if(dre->getType().getAsString().find("::iterator")!=string::npos){
                return dre->getNameInfo().getAsString();
            }
        }
        return "";
    }

    string getRefExprIteratorName(Expr* expr){
        while(expr){
            if(isa<ExprWithCleanups>(expr)){
                ExprWithCleanups* ewc = dyn_cast_or_null<ExprWithCleanups>(expr);
                expr = ewc->getSubExpr(); 
            }else if(isa<CXXConstructExpr>(expr)){
                CXXConstructExpr* cxxce = dyn_cast_or_null<CXXConstructExpr>(expr);
                if(cxxce->getNumArgs()==1){
                    expr = cxxce->getArg(0);
                }else
                    break;
            }else if(isa<MaterializeTemporaryExpr>(expr)){
                MaterializeTemporaryExpr* mte = dyn_cast_or_null<MaterializeTemporaryExpr>(expr);
                expr = mte->GetTemporaryExpr();
            }else if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }else if(isa<MemberExpr>(expr)){
                MemberExpr* me = dyn_cast_or_null<MemberExpr>(expr);
                expr = me->getBase();
            }else if(isa<CXXMemberCallExpr>(expr)){
                CXXMemberCallExpr* cce = dyn_cast_or_null<CXXMemberCallExpr>(expr);
                expr = cce->getCallee();
            }else if(isa<DeclRefExpr>(expr)){    
                DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
                return dre->getNameInfo().getAsString();
            }else
                break;
        }
        return "";
    }

    void getBinaNameAndVal(Stmt* stmt, string& name, string& value){
        if(isa<ExprWithCleanups>(stmt)){
            ExprWithCleanups* ewc = dyn_cast_or_null<ExprWithCleanups>(stmt);
            Expr* expr = ewc->getSubExpr();
            if(isa<CXXOperatorCallExpr>(expr)){
                CXXOperatorCallExpr* cxxoce = dyn_cast_or_null<CXXOperatorCallExpr>(expr);
                if(cxxoce->getNumArgs()==2){
                    name = getNameFromExpr(cxxoce->getArg(0));
                    value = getRefExprIteratorName(cxxoce->getArg(1));
                }
            }
        }
    }

    void getDeclNameAndVal(Stmt* stmt, string& name, string& value){
        if(isa<DeclStmt>(stmt)){
            DeclStmt* ds  = dyn_cast_or_null<DeclStmt>(stmt);
            if(ds->isSingleDecl()){
                Decl* decl = ds->getSingleDecl();
                if(isa<VarDecl>(decl)){
                    VarDecl* vd = dyn_cast_or_null<VarDecl>(decl);
                    string type = vd->getType().getAsString();
                    if(type.find("::iterator")!=string::npos){//容器
                        name = vd->getNameAsString();
                        value = getRefExprIteratorName(vd->getInit());
                    }
                }
            }
        }else if(isa<ExprWithCleanups>(stmt)){
            getBinaNameAndVal(stmt, name, value);
        }
    }

    /* Visit ForStmt */
    bool VisitForStmt(ForStmt *fs)
    {
        Stmt* initStmt = fs->getInit();
        Expr* cond = fs->getCond();
        string initName, initVal, condName, condVal;
        getDeclNameAndVal(initStmt, initName, initVal);
        getBinaNameAndVal(cond, condName, condVal);

        if(initName.size() && initVal.size() && initName==condName && initVal!=condVal){
            string message = "Consider inspecting the loop expression. Different containers are utilized for setting up initial and final values of the iterator.";
            addViolation(fs, this, message);
        }
        return true;
    }
};

static RuleSet rules(new IteratorInitAndFinalValueDifferInForLoopRule());
