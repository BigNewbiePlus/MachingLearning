#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
#include<fstream>
    
using namespace std;
using namespace clang;
using namespace oclint;

class DifferentEnumComparisonRule : public AbstractASTVisitorRule<DifferentEnumComparisonRule>
{
public:
    virtual const string name() const override
    {
        return "different enum comparison";
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
        sm = &_carrier->getSourceManager();fwrite.open("/home/fdh/info.txt",ios::app);
    }
    virtual void tearDown() override {fwrite.close();}

    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *node)
    {
        BinaryOperatorKind bok = node->getOpcode();
        
        if((bok==BO_EQ) || (bok==BO_NE)){
            Expr* lhs = node->getLHS();
            Expr* rhs = node->getRHS();
            
            string type1 = getEnumType(lhs);
            string type2 = getEnumType(rhs);
            
            if(type1.size() && type2.size() && type1!=type2){
                string message = "The values of different enum types are compared: "+expr2str(node)+".";
                addViolation(node,this,message);
            }
        }
        return true;
    }
     
    /* Visit SwitchStmt */
    bool VisitSwitchStmt(SwitchStmt *node)
    {
        Expr* cond = node->getCond();
        string type1 = getEnumType(cond);
        if(type1.size()==0)return true;
        
        SwitchCase* switchCase = node->getSwitchCaseList();
        
        while(switchCase){

            if(isa<CaseStmt>(switchCase)){
                
                CaseStmt* caseStmt = dyn_cast<CaseStmt>(switchCase);
                Expr* lhs = caseStmt->getLHS();
                string type2 = getEnumType(lhs);
                
                if(type2.size()&&type2!=type1){
                    string message = "The values of different enum types are compared: switch(ENUM_TYPE_A) { case ENUM_TYPE_B: ... }.";
                    addViolation(switchCase,this,message);
                }
            }
            switchCase = switchCase->getNextSwitchCase();
        }
        return true;
    }
private:
    string getEnumType(Expr* expr){
        string type = "";
        while(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        } 
        
        if(isa<DeclRefExpr>(expr)){
            DeclRefExpr* declRefExpr = dyn_cast<DeclRefExpr>(expr);
            ValueDecl* valueDecl = declRefExpr->getDecl();
            if(valueDecl->getType()->isEnumeralType()){
              return valueDecl->getType().getAsString();  
            }
        }
        return type;
    }
    
    std::string expr2str(Expr* expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
private:
    fstream fwrite;
    SourceManager* sm;
};

static RuleSet rules(new DifferentEnumComparisonRule());  