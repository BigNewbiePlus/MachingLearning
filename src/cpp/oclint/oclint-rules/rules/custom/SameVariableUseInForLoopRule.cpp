#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class SameVariableUseInForLoopRule : public AbstractASTVisitorRule<SameVariableUseInForLoopRule>
{
public:
    virtual const string name() const override
    {
        return "same variable use in for loop";
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
        ForStmt *forStmt = dyn_cast<ForStmt>(bodyStmt);
        CompoundStmt *compoundStmt = dyn_cast_or_null<CompoundStmt>(bodyStmt);
        if (!forStmt && compoundStmt && compoundStmt->size() == 1)
        {
            forStmt = dyn_cast_or_null<ForStmt>(compoundStmt->body_back());
        }
        if (forStmt)
        {
            Stmt *initStmt1 = parentStmt->getInit();
            Stmt *initStmt2 = forStmt->getInit();
            string name;
            if (isInnerIncMatchingOuterInit(initStmt2, initStmt1, name))
            {
                string message = 
                    "The variable '"+name+"' is being used for this loop and for the outer loop.";
                addViolation(initStmt2, this, message);
            }
        }

        return true;
    }

private:
    ValueDecl *varDeclFromInitStmt(Stmt *initStmt)
    {
        DeclStmt *declStmt = dyn_cast_or_null<DeclStmt>(initStmt);
        if (declStmt && declStmt->isSingleDecl())
        {
            return dyn_cast_or_null<VarDecl>(declStmt->getSingleDecl());
        }
        if(isa<BinaryOperator>(initStmt)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(initStmt);
            if(binaryOperator->getOpcode()==BO_Assign){
                Expr* lhs = binaryOperator->getLHS();
                if(isa<DeclRefExpr>(lhs)){
                    DeclRefExpr* declRefExpr = dyn_cast<DeclRefExpr>(lhs);
                    return declRefExpr->getDecl();
                }
            }  
        }
        return nullptr;
    }

    bool isInnerIncMatchingOuterInit(Stmt *initStmt2, Stmt *initStmt1,string& name)
    {
        ValueDecl *varDecl2 = varDeclFromInitStmt(initStmt2);
        ValueDecl *varDecl1 = varDeclFromInitStmt(initStmt1);
        
        if(varDecl2)name = varDecl2->getNameAsString();
        return varDecl2 && varDecl1 && varDecl2 == varDecl1;
    }
};

static RuleSet rules(new SameVariableUseInForLoopRule());   