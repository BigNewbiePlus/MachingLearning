#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ComparePointerWithZeroValueRule : public AbstractASTVisitorRule<ComparePointerWithZeroValueRule>
{
public:
    virtual const string name() const override
    {
        return "compare pointer with zero value";
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

    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *node)
    {
        if(node->getOpcode()==BO_EQ || node->getOpcode()==BO_NE){
            Expr* lhs = node->getLHS();
            Expr* rhs = node->getRHS();
            
            string pType;
            if(isZeroValue(rhs) && isPointer(lhs, pType)){
                string exprStr = expr2str(node);
                string message = "It is odd that pointer to '"+
                    pType+"' type is compared with the '\\0' value. Probably meant: *"+exprStr+".";
                addViolation(node, this, message);
            }
        }
        return true;
    }
private:
    bool isZeroValue(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            auto implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<CharacterLiteral>(expr)){
            CharacterLiteral* charLiteral = dyn_cast<CharacterLiteral>(expr);
            if(charLiteral->getValue()==0)return true;
        }
        return false;
    }
    
    bool isPointer(Expr* expr, string& pType){
        if(expr->getType()->isPointerType()){
            pType = expr->getType().getAsString();
            return true;
        }
        return false;
    }
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

static RuleSet rules(new ComparePointerWithZeroValueRule());  