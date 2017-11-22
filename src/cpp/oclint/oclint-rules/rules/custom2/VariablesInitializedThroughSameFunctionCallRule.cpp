#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class VariablesInitializedThroughSameFunctionCallRule : public AbstractASTVisitorRule<VariablesInitializedThroughSameFunctionCallRule>
{
public:
    virtual const string name() const override
    {
        return "variables initialized through same function call";
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

    string getFunCallName(Expr* expr){
        if(expr && (isa<CallExpr>(expr) || isa<CXXMemberCallExpr>(expr))){
            return expr2str(expr);
        }
        return "";
    }
    void checkInitExpr(Expr* expr1, Expr* expr2, Stmt* stmt){
        
        string func1 = getFunCallName(expr1);
        string func2 = getFunCallName(expr2);
        if(func1.size() && func1==func2){
            string message = "Variables are initialized through the call to the same function. It's probably an error or un-optimized code.";
            addViolation(stmt, this, message);
        }
    }

    Expr* getDeclInit(DeclStmt* ds){
        if(ds->isSingleDecl()){
            Decl* decl = ds->getSingleDecl();
            if(isa<VarDecl>(decl)){
                VarDecl* vd = dyn_cast_or_null<VarDecl>(decl);
                return vd->getInit();
            }
        }
        return nullptr;
    }
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *cs)
    {
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end();it++){
            if(isa<BinaryOperator>(*it) && it+1!=cs->body_end() && isa<BinaryOperator>(*(it+1))){
                BinaryOperator* bo1 = dyn_cast_or_null<BinaryOperator>(*it);
                BinaryOperator* bo2 = dyn_cast_or_null<BinaryOperator>(*(it+1));
                if(bo1->getOpcode()==BO_Assign && bo2->getOpcode()==BO_Assign){
                    checkInitExpr(bo1->getRHS(), bo2->getRHS(), *it);
                }
            }else if(isa<DeclStmt>(*it) && it+1!=cs->body_end() && isa<DeclStmt>(*(it+1))){
                DeclStmt* ds1 = dyn_cast_or_null<DeclStmt>(*it);
                DeclStmt* ds2 = dyn_cast_or_null<DeclStmt>(*(it+1));
                checkInitExpr(getDeclInit(ds1),getDeclInit(ds2), *it);
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

static RuleSet rules(new VariablesInitializedThroughSameFunctionCallRule());
