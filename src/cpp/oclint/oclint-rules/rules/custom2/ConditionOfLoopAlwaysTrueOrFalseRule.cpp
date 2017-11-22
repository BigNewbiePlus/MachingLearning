#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ConditionOfLoopAlwaysTrueOrFalseRule : public AbstractASTVisitorRule<ConditionOfLoopAlwaysTrueOrFalseRule>
{
public:
    virtual const string name() const override
    {
        return "condition of loop always true or false";
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


    inline string getDeclRefExprName(Expr* expr){
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
    string getCondVar(Expr* cond){
        if(isa<BinaryOperator>(cond)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(cond);
            BinaryOperatorKind bok = bo->getOpcode();
            if(bok==BO_LT || bok==BO_GT || bok==BO_LE || bok==BO_GE || bok==BO_EQ || bok==BO_NE){
                return getDeclRefExprName(bo->getLHS());
            }
        }
        return "";
    }

    inline bool hasVarInStmt(Stmt* stmt, string& var){
        if(isa<UnaryOperator>(stmt)){
            UnaryOperator* uo = dyn_cast_or_null<UnaryOperator>(stmt);
            UnaryOperatorKind uok =uo->getOpcode();
            if(uok==UO_PostInc || uok==UO_PostDec || uok==UO_PreInc || uok==UO_PostDec){
                return getDeclRefExprName(uo->getSubExpr())==var;
            }
        }else if(isa<CompoundAssignOperator>(stmt)){
            CompoundAssignOperator* cao = dyn_cast_or_null<CompoundAssignOperator>(stmt);
            return getDeclRefExprName(cao->getLHS())==var;
        }else if(isa<BinaryOperator>(stmt)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(stmt);
            if(bo->getOpcode()==BO_Assign){
                return getDeclRefExprName(bo->getLHS())==var;
            }
        }
        return false;
    }

    bool hasNoVarInBody(Stmt* stmt, string var){
        if(isa<CompoundStmt>(stmt)){
            CompoundStmt* cs = dyn_cast_or_null<CompoundStmt>(stmt);
            for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
                if(hasVarInStmt(*it, var))return false;
            }
        }else
            return hasVarInStmt(stmt, var)==false;
    }
    /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt * ws)
    {
        Expr* cond = ws->getCond();
        Stmt* body = ws->getBody();
        string var = getCondVar(cond);
        if(var.size() && hasNoVarInBody(body, var)){
            string message = "The condition of loop is always true.";
            addViolation(ws, this, message);
        }
        return true;
    }
};

static RuleSet rules(new ConditionOfLoopAlwaysTrueOrFalseRule());
