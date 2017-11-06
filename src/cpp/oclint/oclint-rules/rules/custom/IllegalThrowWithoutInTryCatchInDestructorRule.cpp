#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class IllegalThrowWithoutInTryCatchInDestructorRule : public AbstractASTVisitorRule<IllegalThrowWithoutInTryCatchInDestructorRule>
{
public:
    virtual const string name() const override
    {
        return "illegal throw without in try catch in destructor";
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

    virtual void setUp() override {
        astContext = _carrier->getASTContext();
    }
    virtual void tearDown() override {}
    /* Visit CXXThrowExpr */
    bool VisitCXXThrowExpr(CXXThrowExpr *node)
    {
        if(isThrowWithoutInTryCatchInDestructor(*node)){
            addViolation(node, this, "The 'throw' operator inside the destructor should be placed within the try..catch block. Raising exception inside the destructor is illegal.");
        }
        return true;
    }
private:
    bool isThrowWithoutInTryCatchInDestructor(const clang::Stmt& stmt){
        auto it = astContext->getParents(stmt).begin();
        if(it == astContext->getParents(stmt).end())
            return false;
        const clang::Decl *aDecl = it->get<clang::Decl>();
        if(aDecl && isa<CXXDestructorDecl>(aDecl))
            return true;
        const clang::Stmt *aStmt = it->get<clang::Stmt>();
  
        if(aStmt){
            if(isa<CXXTryStmt>(aStmt))return false;
            return isThrowWithoutInTryCatchInDestructor(*aStmt);
        }    
        return false;
    }
    
private:
    ASTContext* astContext;
};

static RuleSet rules(new IllegalThrowWithoutInTryCatchInDestructorRule());