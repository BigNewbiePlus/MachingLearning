#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class InitAndFinalForIteratorValueAreSameRule : public AbstractASTVisitorRule<InitAndFinalForIteratorValueAreSameRule>
{
public:
    virtual const string name() const override
    {
        return "init and final for iterator value are same";
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

    string getInitValue(Stmt* init){
        if(isa<BinaryOperator>(init)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(init);
            return expr2str(bo->getRHS());
        }else if(isa<ExprWithCleanups>(init)){
            ExprWithCleanups* ewc =dyn_cast_or_null<ExprWithCleanups>(init);
            init = ewc->getSubExpr();
            if(isa<CXXOperatorCallExpr>(init)){
                CXXOperatorCallExpr* coce = dyn_cast_or_null<CXXOperatorCallExpr>(init);
                return expr2str(coce->getArg(1));
            }
        }
        else if(isa<DeclStmt>(init)){
            DeclStmt* ds = dyn_cast_or_null<DeclStmt>(init);
            if(ds->isSingleDecl()){
                Decl* decl = ds->getSingleDecl();
                if(isa<VarDecl>(decl)){
                    VarDecl* varDecl = dyn_cast_or_null<VarDecl>(decl);
                    if(varDecl->hasInit()){
                        return expr2str(varDecl->getInit());
                    }
                }
            }
        }
        return "";
    }
    inline string getCondValue(Expr* cond){
        return getInitValue(cond);
    }
    /* Visit ForStmt */
    bool VisitForStmt(ForStmt* forStmt)
    {
        Stmt* init = forStmt->getInit();
        Expr* cond = forStmt->getCond();
        string initValue = getInitValue(init);
        string condValue = getCondValue(cond);
        
        
        if(initValue.size() && initValue==condValue){
            string message = "Consider inspecting the 'for' operator. Initial and final values of the iterator are the same.
            addViolatio(forStmt, this, message);
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

static RuleSet rules(new InitAndFinalForIteratorValueAreSameRule());
    
