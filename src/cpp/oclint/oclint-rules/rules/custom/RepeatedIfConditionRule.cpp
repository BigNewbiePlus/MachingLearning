#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class RepeatedIfConditionRule : public AbstractASTVisitorRule<RepeatedIfConditionRule>
{
public:
    virtual const string name() const override
    {
        return "repeated if condition";
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
        IfStmt* origIfStmt = ifStmt;
        vector<string> conditions;
        while(ifStmt){
            Expr* condExpr = ifStmt->getCond();
            string condition = expr2str(condExpr);
            conditions.push_back(condition);
            Stmt* elseStmt = ifStmt->getElse();
            if(elseStmt && isa<IfStmt>(elseStmt)){
               ifStmt = dyn_cast_or_null<IfStmt>(elseStmt);
            }else
                break;
            
        }
        
        for(int i=0;i<conditions.size()-1;i++){
            for(int j=i+1;j<conditions.size();j++){
                if(conditions[i]==conditions[j]){
                    string message = "The use of 'if (A) {...} else if (A) {...}' pattern was detected. There is a probability of logical error presence.";
                    addViolation(origIfStmt, this, message);
                    return true;
                }
            }
        }
        
        return true;
    }
private:
    std::string expr2str(Expr *expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
private:
    SourceManager* sm;
};

static RuleSet rules(new RepeatedIfConditionRule());