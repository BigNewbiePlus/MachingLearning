#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class RecurringCheckRule : public AbstractASTVisitorRule<RecurringCheckRule>
{
public:
    virtual const string name() const override
    {
        return "recurring check";
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
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    //check whether the stmt contain the same condtion of expr
    bool recurCheck(string condStr, Stmt* then){
        if(isa<CompoundStmt>(then)){
            CompoundStmt* compoundStmt = dyn_cast_or_null<CompoundStmt>(then);
            for(CompoundStmt::body_iterator it=compoundStmt->body_begin(); it!=compoundStmt->body_end(); it++){
                Stmt* stmt = *it;
                if(isa<IfStmt>(stmt)){
                    IfStmt* nestIfStmt = dyn_cast_or_null<IfStmt>(stmt);
                    if(condStr == expr2str(nestIfStmt->getCond())){
                        return true;
                    }
                }
            }
        }else if(isa<IfStmt>(then)){
            IfStmt* nestIfStmt = dyn_cast_or_null<IfStmt>(then);
            if(condStr == expr2str(nestIfStmt->getCond())){
                return true;
            }
        }
        return false;
    }
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        Expr* expr= ifStmt->getCond();
        Stmt* then = ifStmt->getThen();
        string condStr = expr2str(expr);

        if(recurCheck(condStr, then)){
            string message = "Recurring check. The IF Condition '"+condStr+"' check twice.";
            addViolation(ifStmt, this, message);
        }
        return true;
    }

    string expr2str(Expr* expr){
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text; 
    }
private:
    SourceManager* sm;

};

static RuleSet rules(new RecurringCheckRule());
