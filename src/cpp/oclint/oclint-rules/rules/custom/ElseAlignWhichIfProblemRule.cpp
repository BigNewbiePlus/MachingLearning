#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
  
using namespace std;
using namespace clang;
using namespace oclint;

class ElseAlignWhichIfProblemRule : public AbstractASTVisitorRule<ElseAlignWhichIfProblemRule>
{
public:
    virtual const string name() const override
    {
        return "else align which if problem";
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
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        Stmt* then = ifStmt->getThen();
        if(isa<IfStmt>(then)){
            IfStmt* ifStmt2 = dyn_cast<IfStmt>(then);
            if(!ifStmt2->getElse())return true;
            
            int colu1 = sm->getPresumedColumnNumber(ifStmt->getLocStart(),0);
            int colu3 = sm->getPresumedColumnNumber(ifStmt2->getElseLoc(),0);
            
            if(colu1==colu3){
                addViolation(ifStmt, this, "It is possible that this 'else' branch must apply to the previous 'if' statement.");
                return true;
            }
        }
        return true;
    }
    
private:
    SourceManager* sm;
     
};

static RuleSet rules(new ElseAlignWhichIfProblemRule());