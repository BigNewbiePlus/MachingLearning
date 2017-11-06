#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class WrongVariableComparedInForLoopRule : public AbstractASTVisitorRule<WrongVariableComparedInForLoopRule>
{
public:
    virtual const string name() const override
    {
        return "wrong variable compared in for loop";
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
    
    bool VisitForStmt(ForStmt *parentStmt)
    {
        Stmt *bodyStmt = parentStmt->getBody();
        ForStmt *forStmt = dyn_cast_or_null<ForStmt>(bodyStmt);
        CompoundStmt *compoundStmt = dyn_cast_or_null<CompoundStmt>(bodyStmt);
        if (!forStmt && compoundStmt && compoundStmt->size() == 1)
        {
            forStmt = dyn_cast_or_null<ForStmt>(compoundStmt->body_back());
        }
        if (forStmt)
        {
            Stmt *initStmt = parentStmt->getInit();
            Expr *condExpr = forStmt->getCond();
            string name;
            if (isInnerIncMatchingOuterInit(condExpr, initStmt, name))
            {
                
                string message = 
                    "It is likely that a wrong variable is being compared inside the 'for' operator. Consider reviewing '"+name+"'.";
                addViolation(condExpr, this, message);
            }
        }

        return true;
    }

private:
    VarDecl *varDeclFromInitStmt(Stmt *initStmt)
    {
        DeclStmt *declStmt = dyn_cast_or_null<DeclStmt>(initStmt);
        if (declStmt && declStmt->isSingleDecl())
        {
            return dyn_cast_or_null<VarDecl>(declStmt->getSingleDecl());
        }
        return nullptr;
    }

    ValueDecl *valueDeclFromCondExpr(Expr *expr)
    {
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* binaryOperator = dyn_cast<BinaryOperator>(expr);
            if(binaryOperator->getOpcode()==BO_LT){
                expr = binaryOperator->getLHS();
                if(isa<ImplicitCastExpr>(expr)){
                    auto implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
                    expr = implicitCastExpr->getSubExpr();
                }
                if(isa<DeclRefExpr>(expr)){
                    DeclRefExpr *declRefExpr = dyn_cast<DeclRefExpr>(expr);
                    return declRefExpr->getDecl(); 
                }
            }
        }
        return nullptr;
    }

    bool isInnerIncMatchingOuterInit(Expr *condExpr, Stmt *initStmt,string& name)
    {
        VarDecl *varDecl = varDeclFromInitStmt(initStmt);
        ValueDecl *valueDecl = valueDeclFromCondExpr(condExpr);
        
        if(varDecl)name = varDecl->getNameAsString();
        return varDecl && valueDecl && varDecl == valueDecl;
    }
};

static RuleSet rules(new WrongVariableComparedInForLoopRule());