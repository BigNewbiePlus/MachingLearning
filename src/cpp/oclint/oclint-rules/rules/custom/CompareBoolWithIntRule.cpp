#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
    
using namespace std;
using namespace clang;
using namespace oclint;

class CompareBoolWithIntRule : public AbstractASTVisitorRule<CompareBoolWithIntRule>
{
public:
    virtual const string name() const override
    {
        return "compare bool with int";
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
        BinaryOperatorKind bok = node->getOpcode();
        if(bok==BO_LT || bok==BO_GT || bok==BO_LE || bok==BO_GE||bok==BO_EQ || bok==BO_NE){
            Expr* lhs = node->getLHS();
            Expr* rhs = node->getRHS();
            
            int type1,type2;//1:bool,2:int,-1:其他
            int value1, value2;//取值
            getType(lhs, type1, value1);
            getType(rhs, type2, value2);
            if((type1==1 && type2==2) || (type1==2 && type2==1)){
                string intStr;
                
                if(type1==1)intStr = to_string(value2);
                else intStr = to_string(value1);
              
                string message = "It's odd to compare a bool type value with a value of "+intStr+": "+expr2str(node)+"."; 
                addViolation(node, this, message);
            }
            
        }
        return true;
    }
private:
    void getType(Expr* expr, int& type, int& value){
        type=-1;
        
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(expr->getType()->isBooleanType()){
            type=1;
        }else if(expr->getType()->isIntegerType()){
            
            int coff = 1;
            if(isa<UnaryOperator>(expr)){
                UnaryOperator* unaryOperator = dyn_cast<UnaryOperator>(expr);
                expr = unaryOperator->getSubExpr();
                if(unaryOperator->getOpcode()==UO_Minus)coff=-1;
            }
            if(isa<IntegerLiteral>(expr)){
                type=2;
                IntegerLiteral* integerLiteral = dyn_cast<IntegerLiteral>(expr);
                value = integerLiteral->getValue().getSExtValue();
                value*=coff;
                
            }        
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

static RuleSet rules(new CompareBoolWithIntRule());    