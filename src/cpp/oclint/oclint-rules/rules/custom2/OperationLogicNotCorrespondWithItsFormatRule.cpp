#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
using namespace std;
using namespace clang;
using namespace oclint;

class OperationLogicNotCorrespondWithItsFormatRule : public AbstractASTVisitorRule<OperationLogicNotCorrespondWithItsFormatRule>
{
public:
    virtual const string name() const override
    {
        return "operation logic not correspond with its format";
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

    bool isSameFormat(Stmt* stmt1, Stmt* stmt2){
        SourceLocation sl1 = stmt1->getLocStart();
        SourceLocation sl2 = stmt2->getLocStart();
        unsigned row1 = sm->getSpellingLineNumber(sl1);
        unsigned col1 = sm->getSpellingColumnNumber(sl1);
        unsigned row2 = sm->getSpellingLineNumber(sl2);
        unsigned col2 = sm->getSpellingColumnNumber(sl2);
        if(row1==row2 || (row1+1==row2 && col1==col2))return true;
        return false;
    }
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *cs)
    {
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end();it++){
            if(isa<IfStmt>(*it)){
                IfStmt* ifStmt = dyn_cast_or_null<IfStmt>(*it);
                Stmt* then = ifStmt->getThen();
                if(!ifStmt->getElse() && !isa<CompoundStmt>(then) && (it+1!=cs->body_end())){//if语句没else分支且then无括号
                    Stmt* nextStmt = *(it+1);
                    if(isSameFormat(then, nextStmt)){
                        string message= "The code's operational logic does not correspond with its formatting. The statement is indented to the right, but it is always executed. It is possible that curly brackets are missing.";
                        addViolation(ifStmt, this, message);
                    }
                }
            }
        }
        return true;
    }
private:
    SourceManager* sm;
};

static RuleSet rules(new OperationLogicNotCorrespondWithItsFormatRule());
