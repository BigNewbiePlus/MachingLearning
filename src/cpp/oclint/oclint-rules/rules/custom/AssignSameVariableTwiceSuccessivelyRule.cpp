#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class AssignSameVariableTwiceSuccessivelyRule : public AbstractASTVisitorRule<AssignSameVariableTwiceSuccessivelyRule>
{
public:
    virtual const string name() const override
    {
        return "assign same variable twice successively";
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

    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *node)
    {
        clang::CompoundStmt::body_iterator body_it = node->body_begin();
        if(body_it==node->body_end())return true;
        Stmt* stmt1 = *body_it;
        Stmt* stmt2;
        for(body_it++; body_it!=node->body_end();body_it++){
            stmt2 = *body_it;
            checkSuccessiveStmt(stmt1, stmt2);
            stmt1=stmt2;   
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
    void checkSuccessiveStmt(Stmt* stmt1, Stmt* stmt2){
        if(isa<BinaryOperator>(stmt1) && isa<BinaryOperator>(stmt2)){
            BinaryOperator* binaryOperator1 = dyn_cast_or_null<BinaryOperator>(stmt1);
            BinaryOperator* binaryOperator2 = dyn_cast_or_null<BinaryOperator>(stmt2);
            
            if(binaryOperator1->getOpcode()==BO_Assign && binaryOperator2->getOpcode()==BO_Assign){
                Expr* lhs1 = binaryOperator1->getLHS();
                Expr* lhs2 = binaryOperator2->getLHS();
                string lhsStr1 = expr2str(lhs1);
                string lhsStr2 = expr2str(lhs2);
                if(lhsStr1==lhsStr2){
                    string message = "The '"+lhsStr1+"' object is assigned values twice successively. Perhaps this is a mistake.";
                    addViolation(lhs1, this, message);
                }  
            }
        }
    }
private:
    SourceManager* sm;
    
};

static RuleSet rules(new AssignSameVariableTwiceSuccessivelyRule());  