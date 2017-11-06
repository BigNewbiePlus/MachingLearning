#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class StrlenConstantValueInMallocRule : public AbstractASTVisitorRule<StrlenConstantValueInMallocRule>
{
public:
    virtual const string name() const override
    {
        return "strlen constant value in malloc";
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

    /* Visit CallExpr */
    bool VisitCallExpr(CallExpr *callExpr)
    {
        unsigned argNum = callExpr->getNumArgs();
        FunctionDecl* funcDecl = callExpr->getDirectCallee();
        string callFuncName = funcDecl->getNameInfo().getAsString();
        
        Expr* argExpr = NULL;
        if(callFuncName=="malloc" && argNum==1)
            argExpr = callExpr->getArg(0);
        else if(callFuncName=="realloc" && argNum==2)
            argExpr = callExpr->getArg(1);
        
        if(argExpr && isa<CallExpr>(argExpr)){//调用函数的第1(2)个参数是strlen            
            callExpr = dyn_cast_or_null<CallExpr>(argExpr);
            funcDecl = callExpr->getDirectCallee();
            string funcName = funcDecl->getNameInfo().getAsString();
            argNum = callExpr->getNumArgs();
            
            if(funcName=="strlen" && argNum==1){
                if(strlenArgViolation(callExpr->getArg(0))){
                    string strlenStr = expr2str(argExpr);
                    string message = "The '"+callFuncName+"' function allocates strange amount of memory calculated by '"+strlenStr+"'.";
                    addViolation(argExpr, this, message);
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
    
    bool strlenArgViolation(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(expr);
            Expr* lhs = binaryOperator->getLHS();
            Expr* rhs = binaryOperator->getRHS();
            if(isIntegerLiteral(lhs)||isIntegerLiteral(rhs))return true;
        }
        return false;    
    }
    bool isIntegerLiteral(Expr* expr){
       if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<IntegerLiteral>(expr))return true;
        return false;
    }
private:
    SourceManager* sm;
};

static RuleSet rules(new StrlenConstantValueInMallocRule());   