#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
    
using namespace std;
using namespace clang;
using namespace oclint;

class PartOfConditionIsConstantValueRule : public AbstractASTVisitorRule<PartOfConditionIsConstantValueRule>
{
public:
    virtual const string name() const override
    {
        return "part of condition is constant value";
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
    bool VisitIfStmt(IfStmt *node)
    {
        checkConstant(node->getCond());
        return true;
    }
     
    /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt *node)
    {
        checkConstant(node->getCond());
        return true;
    }
     

    /* Visit DoStmt */
    bool VisitDoStmt(DoStmt *node)
    {
        checkConstant(node->getCond());
        return true;
    }
    
private:

    void checkConstant(Expr* expr)
    {
        while(true){
            if(isa<UnaryOperator>(expr)){
                UnaryOperator* unaryOperator = dyn_cast<UnaryOperator>(expr);
                expr = unaryOperator->getSubExpr();
            }else if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
                expr = implicitCastExpr->getSubExpr();
                
                
            }else if(isa<ParenExpr>(expr)){
                ParenExpr* parenExpr = dyn_cast<ParenExpr>(expr);
                expr = parenExpr->getSubExpr();
                
            }else if(isa<BinaryOperator>(expr)){
                BinaryOperator* binaryOperator = dyn_cast<BinaryOperator>(expr);
                BinaryOperatorKind bok = binaryOperator->getOpcode();
                if(bok==BO_LOr || bok==BO_LAnd){
                    checkConstant(binaryOperator->getLHS());
                    checkConstant(binaryOperator->getRHS());
                }
                break;
            }else if(isa<IntegerLiteral>(expr)){
                string message = "A part of conditional expression is always true: "+expr2str(expr)+"."; 
                addViolation(expr,this,message);  
                break;
            }else
                break;
        }      
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

static RuleSet rules(new PartOfConditionIsConstantValueRule()); 