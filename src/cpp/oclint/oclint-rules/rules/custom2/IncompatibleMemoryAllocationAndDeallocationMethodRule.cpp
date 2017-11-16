#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class IncompatibleMemoryAllocationAndDeallocationMethodRule : public AbstractASTVisitorRule<IncompatibleMemoryAllocationAndDeallocationMethodRule>
{
public:
    virtual const string name() const override
    {
        return "incompatible memory allocation and deallocation method";
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
        sm=&_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    int varDeclType(VarDecl* varDecl){
        if(varDecl->hasInit()){
            Expr* init = varDecl->getInit();
            if(isa<CXXNewExpr>(init)){
                CXXNewExpr* cne = dyn_cast_or_null<CXXNewExpr>(init);
                if(cne->isArray())return 2;
                else return 1;
            }
        }
        return 0;
    }

    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt* cs)
    {
        map<string, int> newType;
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end();it++){
            if(isa<DeclStmt>(*it)){
                DeclStmt* ds = dyn_cast_or_null<DeclStmt>(*it);
                if(ds->isSingleDecl()){
                    Decl* decl = ds->getSingleDecl();
                    if(isa<VarDecl>(decl)){
                        VarDecl* varDecl = dyn_cast_or_null<VarDecl>(decl);
                        if(varDecl->hasInit() && isa<CXXNewExpr>(varDecl->getInit())){
                            CXXNewExpr* cne = dyn_cast_or_null<CXXNewExpr>(varDecl->getInit());
                            newType[varDecl->getNameAsString()]=cne->isArray()?2:1;
                        }
                    }
                }
            }else if(isa<BinaryOperator>(*it)){
                BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(*it);
                if(bo->getOpcode()==BO_Assign && isa<CXXNewExpr>(bo->getRHS())){
                    CXXNewExpr* cne = dyn_cast_or_null<CXXNewExpr>(bo->getRHS());
                    newType[expr2str(bo->getLHS())]=cne->isArray()?2:1;
                }
            }else if(isa<CXXDeleteExpr>(*it)){
                CXXDeleteExpr* cde = dyn_cast_or_null<CXXDeleteExpr>(*it);
                if(!cde->isArrayForm()){
                    //申请内存使用new[], 删除时应使用 delete []a;
                    string name = expr2str(cde->getArgument());
                    if(newType[name]==2){
                        string message = "The memory was allocated using 'new T[]' operator but was released using the 'delete' operator. Consider inspecting this code. It's probably better to use 'delete []"+name+";'.";
                        addViolation(*it, this, message);

                    }
                }
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

static RuleSet rules(new IncompatibleMemoryAllocationAndDeallocationMethodRule());
