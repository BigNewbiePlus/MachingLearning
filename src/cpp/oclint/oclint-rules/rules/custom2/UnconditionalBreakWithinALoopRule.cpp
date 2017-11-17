#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class UnconditionalBreakWithinALoopRule : public AbstractASTVisitorRule<UnconditionalBreakWithinALoopRule>
{
public:
    virtual const string name() const override
    {
        return "unconditional break within a loop";
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

    bool visitBody(Stmt* stmt){
        if(isa<CompoundStmt>(stmt)){
            CompoundStmt* cs = dyn_cast_or_null<CompoundStmt>(stmt);
            for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
                string value;
                if(isa<BreakStmt>(*it))value="break";
                else if(isa<ReturnStmt>(*it))value="return";
                else if(isa<ContinueStmt>(*it))value="continue";
                if(value.size()>0){
                    string message = "An unconditional '"+value+"' within a loop.";
                    addViolation(*it, this, message);
                }
            }
        }
    }

    /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt *ws)
    {
        visitBody(ws->getBody());
        return true;
    }

    /* Visit DoStmt */
    bool VisitDoStmt(DoStmt *ds)
    {
        visitBody(ds->getBody());
        return true;
    }

    /* Visit ForStmt */
    bool VisitForStmt(ForStmt *fs)
    {
        visitBody(fs->getBody());
        return true;
    }

};

static RuleSet rules(new UnconditionalBreakWithinALoopRule());
