#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
using namespace std;
using namespace clang;
using namespace oclint;

class DividingSizeofAPointerByAnotherValueRule : public AbstractASTVisitorRule<DividingSizeofAPointerByAnotherValueRule>
{
public:
    virtual const string name() const override
    {
        return "dividing sizeof a pointer by another value";
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
        if(node->getOpcode() != BO_Div) return true;//除法
        
        Expr* lhs = node->getLHS();
        if(!isa<UnaryExprOrTypeTraitExpr>(lhs))return true; //sizeof
        
        UnaryExprOrTypeTraitExpr* unaryExprOrTypeTraitExpr = dyn_cast_or_null<UnaryExprOrTypeTraitExpr>(lhs);
        if(unaryExprOrTypeTraitExpr->getKind()!=UETT_SizeOf)return true;//sizeof
                    
        Expr* expr = unaryExprOrTypeTraitExpr->getArgumentExpr();
                
        if(isa<ParenExpr>(expr)){//可能存在括号
            ParenExpr* parenExpr = dyn_cast_or_null<ParenExpr>(expr);
            expr= parenExpr->getSubExpr();     
        }
                    
        if(isa<DeclRefExpr>(expr)){            
            DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(expr);
            if(declRefExpr->getType()->isPointerType()){//指针
                string lhsStr = expr2str(lhs);
                string message = "Dividing sizeof a pointer '"+lhsStr+
                    "' by another value. There is a probability of logical error presence.";
                addViolation(lhs, this, message);
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

static RuleSet rules(new DividingSizeofAPointerByAnotherValueRule());