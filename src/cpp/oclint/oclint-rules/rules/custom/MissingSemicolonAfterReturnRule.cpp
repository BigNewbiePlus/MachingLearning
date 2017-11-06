#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class MissingSemicolonAfterReturnRule : public AbstractASTVisitorRule<MissingSemicolonAfterReturnRule>
{
public:
    virtual const string name() const override
    {
        return "missing semicolon after return";
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
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    
     /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *node)
    {
        Stmt* then = node->getThen();
        if(isa<ReturnStmt>(then)){//if语句后直接跟return语句
            ReturnStmt* returnStmt = dyn_cast_or_null<ReturnStmt>(then);
            Expr* returnValue = returnStmt->getRetValue();
            if(returnValue){//不为空
                SourceLocation location1 = returnStmt->getLocStart();
                SourceLocation location2 = returnValue->getLocStart();
                unsigned int line1 = sm->getExpansionLineNumber(location1);
                unsigned int line2 = sm->getExpansionLineNumber(location2);
                if(line1!=line2){
                    addViolation(returnStmt, this, 
                                 "It is highly probable that the semicolon ';' is missing after 'return' keyword.");
                }
                
            }
        }
        return true;
    }
private:
    SourceManager* sm;
     
};

static RuleSet rules(new MissingSemicolonAfterReturnRule());

