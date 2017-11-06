#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class WrongVariableIncreaseInForLoopRule : public AbstractASTVisitorRule<WrongVariableIncreaseInForLoopRule>
{
public:
    virtual const string name() const override
    {
        return "wrong variable increase in for loop";
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
            Expr *incExpr = forStmt->getInc();
            string name;
            if (isInnerIncMatchingOuterInit(incExpr, initStmt, name))
            {
                
                string message = 
                    "It is likely that a wrong variable is being incremented inside the 'for' operator. Consider reviewing '"+name+"'.";
                addViolation(incExpr, this, message);
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

    ValueDecl *valueDeclFromIncExpr(Expr *incExpr)
    {
        UnaryOperator *unaryOperator = dyn_cast_or_null<UnaryOperator>(incExpr);
        if (unaryOperator)
        {
            Expr *unaryOpSubExpr = unaryOperator->getSubExpr();
            if (unaryOpSubExpr && isa<DeclRefExpr>(unaryOpSubExpr))
            {
                DeclRefExpr *declRefExpr = dyn_cast<DeclRefExpr>(unaryOpSubExpr);
                return declRefExpr->getDecl();
            }
        }
        return nullptr;
    }

    bool isInnerIncMatchingOuterInit(Expr *incExpr, Stmt *initStmt,string& name)
    {
        VarDecl *varDecl = varDeclFromInitStmt(initStmt);
        ValueDecl *valueDecl = valueDeclFromIncExpr(incExpr);
        
        if(varDecl)name = varDecl->getNameAsString();
        return varDecl && valueDecl && varDecl == valueDecl;
    }
};

static RuleSet rules(new WrongVariableIncreaseInForLoopRule());