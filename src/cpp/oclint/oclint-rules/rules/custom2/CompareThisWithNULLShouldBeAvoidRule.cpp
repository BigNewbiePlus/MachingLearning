#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
    
using namespace std;
using namespace clang;
using namespace oclint;

class CompareThisWithNULLShouldBeAvoidRule : public AbstractASTVisitorRule<CompareThisWithNULLShouldBeAvoidRule>
{
public:
    virtual const string name() const override
    {
        return "compare this with n u l l should be avoid";
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

    inline Expr* rmICE(Expr* expr){
        while(expr){
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }else break;
        }
        return expr;
    }
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *is)
    {
        Expr* expr = is->getCond();
        if(isa<UnaryOperator>(expr)){
            UnaryOperator* uo = dyn_cast_or_null<UnaryOperator>(expr);
            if(uo->getOpcode()==UO_LNot){
                expr = uo->getSubExpr();
                expr = rmICE(expr);
                if(isa<CXXThisExpr>(expr)){
                    string message = "'"+expr2str(is->getCond())+"' comparison should be avoided - this comparison is always false on newer compilers.";
                    addViolation(is->getCond(), this, message);
                }
            }
        }else if(isa<BinaryOperator>(expr)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
            Expr* lhs = bo->getLHS();
            if(isa<CXXThisExpr>(lhs)){
                Expr* rhs = rmICE(bo->getRHS());
                if(isa<IntegerLiteral>(rhs) || isa<GNUNullExpr>(rhs)){
                    string message = "'"+expr2str(bo)+"' comparison should be avoided - this comparison is always false on newer compilers.";
                    addViolation(bo, this, message);
                }
            }
        }
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

static RuleSet rules(new CompareThisWithNULLShouldBeAvoidRule());
