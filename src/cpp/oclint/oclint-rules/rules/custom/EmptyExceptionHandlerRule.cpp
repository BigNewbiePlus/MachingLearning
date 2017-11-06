#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class EmptyExceptionHandlerRule : public AbstractASTVisitorRule<EmptyExceptionHandlerRule>
{
public:
    virtual const string name() const override
    {
        return "empty exception handler";
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

    /* Visit CXXTryStmt */
    bool VisitCXXTryStmt(CXXTryStmt *cxxTryStmt)
    {
        unsigned num = cxxTryStmt->getNumHandlers();
        for(unsigned i=0;i<num;i++){
            CXXCatchStmt * catchStmt = cxxTryStmt->getHandler(i);
            Stmt* stmt = catchStmt->getHandlerBlock();
            if(isa<CompoundStmt>(stmt)){
               CompoundStmt* compoundStmt = dyn_cast<CompoundStmt>(stmt);
                if(compoundStmt->size()==0){
                    string message = "An empty exception handler. Silent suppression of exceptions can hide the presence of bugs in source code during testing.";
                    addViolation(catchStmt, this, message);
                }
            }
        }
        return true;
    }
     
};

static RuleSet rules(new EmptyExceptionHandlerRule());