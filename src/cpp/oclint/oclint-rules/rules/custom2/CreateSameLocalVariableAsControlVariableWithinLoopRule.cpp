#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class CreateSameLocalVariableAsControlVariableWithinLoopRule : public AbstractASTVisitorRule<CreateSameLocalVariableAsControlVariableWithinLoopRule>
{
public:
    virtual const string name() const override
    {
        return "create same local variable as control variable within loop";
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

    bool getControlVarName(Expr* expr, string& name){
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
            expr = bo->getLHS();
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }
            if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
                name = dre->getNameInfo().getAsString();
                return true;
            }
        }
        return false;
    }

    string getSingleDeclVarName(DeclStmt* ds){
        if(ds->isSingleDecl()){
            Decl* decl = ds->getSingleDecl();
            if(isa<VarDecl>(decl)){
                VarDecl* vd = dyn_cast_or_null<VarDecl>(decl);
                return vd->getNameAsString();
            }
        }
        return "";
    }
    /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt *ws)
    {
        Expr* cond = ws->getCond();
        string name1;
        if(getControlVarName(cond, name1)){
            Stmt* body = ws->getBody();
            if(isa<CompoundStmt>(body)){
                CompoundStmt* cs = dyn_cast_or_null<CompoundStmt>(body);
                for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
                    if(isa<DeclStmt>(*it)){
                        DeclStmt* ds = dyn_cast_or_null<DeclStmt>(*it);
                        string name2 = getSingleDeclVarName(ds);
                        if(name1==name2){
                            string message = "It is dangerous to create a local variable within a loop with a same name as a variable controlling this loop.";
                            addViolation(ws, this, message);
                            break;
                        }
                    }
                }
            }

        }
        return true;
    }
};

static RuleSet rules(new CreateSameLocalVariableAsControlVariableWithinLoopRule());
