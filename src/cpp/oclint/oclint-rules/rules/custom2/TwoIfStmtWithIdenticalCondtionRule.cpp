#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class TwoIfStmtWithIdenticalCondtionRule : public AbstractASTVisitorRule<TwoIfStmtWithIdenticalCondtionRule>
{
public:
    virtual const string name() const override
    {
        return "two if stmt with identical condtion";
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

    bool hasReturnStmt(Stmt* stmt){
        if(isa<ReturnStmt>(stmt))return true;
        if(isa<CompoundStmt>(stmt)){
            CompoundStmt* cs = dyn_cast_or_null<CompoundStmt>(stmt);
            for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end();it++){
                if(isa<ReturnStmt>(*it))return true;
            }
        }
        return false;
    }

    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *cs)
    {
        set<string> return_conds;
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
            if(isa<IfStmt>(*it)){
                IfStmt* is = dyn_cast_or_null<IfStmt>(*it);
                string cond = expr2str(is->getCond());
                if(return_conds.find(cond)!=return_conds.end()){
                    string message = "There are two 'if' statements with identical conditional expressions. The first 'if' statement contains function return. This means that the second 'if' statement is senseless.";
                    addViolation(*it, this, message);
                }
                if(hasReturnStmt(is->getThen())){
                    return_conds.insert(cond);
                }

            }
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

static RuleSet rules(new TwoIfStmtWithIdenticalCondtionRule());
