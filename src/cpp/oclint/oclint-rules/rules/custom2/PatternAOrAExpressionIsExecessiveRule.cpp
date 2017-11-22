#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class PatternAOrAExpressionIsExecessiveRule : public AbstractASTVisitorRule<PatternAOrAExpressionIsExecessiveRule>
{
public:
    virtual const string name() const override
    {
        return "pattern a or a expression is execessive";
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

    bool isLAndPattern(ParenExpr* pe, string& name1, string& name2){
        Expr* expr = pe->getSubExpr();
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
            if(bo->getOpcode()==BO_LAnd){
                name1 = expr2str(bo->getLHS());
                name2 = expr2str(bo->getRHS());
                return true;
            }
        }
        return false;
    }
    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *bo)
    {
        if(bo->getOpcode()==BO_LOr){
            Expr* lhs = bo->getLHS();
            Expr* rhs = bo->getRHS();
            string name1, name2, name3;
            if(isa<ParenExpr>(lhs)){
                swap(lhs, rhs);
            }
            
            if(isa<ParenExpr>(rhs)){
                ParenExpr* pe = dyn_cast_or_null<ParenExpr>(rhs);
                if(isLAndPattern(pe, name2, name3)){
                    name1 = expr2str(lhs);
                    if(name1.size() && (name1==name2||name1==name3)){
                        string message = "A pattern was detected: A || (A && ...). The expression is excessive or contains a logical error.";
                        addViolation(bo, this, message);
                    }
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

static RuleSet rules(new PatternAOrAExpressionIsExecessiveRule());
