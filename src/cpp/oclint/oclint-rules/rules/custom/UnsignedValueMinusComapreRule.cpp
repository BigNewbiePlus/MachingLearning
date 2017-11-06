#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
    
using namespace std;
using namespace clang;
using namespace oclint;

class UnsignedValueMinusComapreRule : public AbstractASTVisitorRule<UnsignedValueMinusComapreRule>
{
public:
    virtual const string name() const override
    {
        return "unsigned value minus comapre";
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
    bool VisitBinaryOperator(BinaryOperator *binaryOperator)
    {
        if(binaryOperator->getOpcode()!=BO_GT)return true;
        Expr* lhs = binaryOperator->getLHS();    
        Expr* rhs = binaryOperator->getRHS();
        if(!isa<BinaryOperator>(lhs))return true;
        
        BinaryOperator* binaryOperator2 = dyn_cast<BinaryOperator>(lhs);
        Expr* llhs = binaryOperator2->getLHS();
        Expr* lrhs = binaryOperator2->getRHS();
        
        if(binaryOperator2->getOpcode()!=BO_Sub)return true;
        
        if(isZeroValue(rhs) && isUnsigned(llhs) && isUnsigned(lrhs)){
            string message = "The expression '"+expr2str(binaryOperator)+"' will work as '"+expr2str(llhs)+" != "+expr2str(lrhs)+"'.";
            addViolation(binaryOperator, this, message);
        }
        return true;
    }
private:
   bool  isZeroValue(Expr* expr){
       if(isa<ImplicitCastExpr>(expr)){
           ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
           expr = implicitCastExpr->getSubExpr();
       }
       
       if(isa<IntegerLiteral>(expr)){
           IntegerLiteral* integerLiteral = dyn_cast<IntegerLiteral>(expr);
           if(integerLiteral->getValue().getSExtValue()==0)return true;
       }
       return false;
   }
    
    bool isUnsigned(Expr* expr){
        return expr->getType()->isUnsignedIntegerType();
    }
    
    std::string expr2str(Expr *expr) {
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

static RuleSet rules(new UnsignedValueMinusComapreRule());