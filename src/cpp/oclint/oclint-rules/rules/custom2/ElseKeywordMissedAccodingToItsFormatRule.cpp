#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ElseKeywordMissedAccodingToItsFormatRule : public AbstractASTVisitorRule<ElseKeywordMissedAccodingToItsFormatRule>
{
public:
    virtual const string name() const override
    {
        return "else keyword missed accoding to its format";
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

    virtual void setUp() override {
        sm=&_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *cs) 
    {
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end();it++){
            if(isa<IfStmt>(*it) && it+1!=cs->body_end() && isa<IfStmt>(*(it+1))){
                IfStmt* stmt1 = dyn_cast_or_null<IfStmt>(*it);
                IfStmt* stmt2 = dyn_cast_or_null<IfStmt>(*(it+1));
                SourceLocation sle1 = stmt1->getLocEnd();
                SourceLocation sls2 = stmt2->getLocStart();
                unsigned e1_row = sm->getSpellingLineNumber(sle1);
                unsigned e1_col = sm->getSpellingColumnNumber(sle1);
                unsigned s2_row = sm->getSpellingLineNumber(sls2);
                unsigned s2_col = sm->getSpellingColumnNumber(sls2);
                if(e1_row==s2_row){
                    string message = "Consider inspecting the application's logic. It's possible that 'else' keyword is missing.";
                    addViolation(stmt2, this, message);
                }

            }
        }
        return true;
    }
private:
    SourceManager* sm;

};

static RuleSet rules(new ElseKeywordMissedAccodingToItsFormatRule());
