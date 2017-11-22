#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class NoSenseTestPointerAgainstNullAsMemAlloUseNewRule : public AbstractASTVisitorRule<NoSenseTestPointerAgainstNullAsMemAlloUseNewRule>
{
public:
    virtual const string name() const override
    {
        return "no sense test pointer against null as mem allo use new";
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

    virtual void setUp() override {}
    virtual void tearDown() override {}

    VarDecl* getVarDecl(DeclStmt* ds){
        if(ds->isSingleDecl()){
            Decl* decl = ds->getSingleDecl();
            if(isa<VarDecl>(decl)){
                VarDecl* vd = dyn_cast_or_null<VarDecl>(decl);
                return vd;
            }
        }
        return nullptr;
    }

    string getCondVarName(Expr* expr){
        
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(expr);
            expr = bo->getLHS();
        }
        while(expr){
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice  = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }else if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
                return dre->getNameInfo().getAsString();
            }else
                break;
        }
        return "";
    }
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *cs)
    {
        set<string> newPtrNames;
        for(CompoundStmt::body_iterator it=cs->body_begin(); it!=cs->body_end(); it++){
            if(isa<DeclStmt>(*it)){
                DeclStmt* ds = dyn_cast_or_null<DeclStmt>(*it);
                VarDecl* vd = getVarDecl(ds);
                if(vd->hasInit() && isa<CXXNewExpr>(vd->getInit())){
                    newPtrNames.insert(vd->getNameAsString());
                }
            }else if(isa<BinaryOperator>(*it)){
                BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(*it);
                if(isa<DeclRefExpr>(bo->getLHS()) && isa<CXXNewExpr>(bo->getRHS())){
                    DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(bo->getLHS());
                    newPtrNames.insert(dre->getNameInfo().getAsString());
                }
            }else if(isa<IfStmt>(*it)){
                IfStmt* is = dyn_cast_or_null<IfStmt>(*it);
                Expr* expr = is->getCond();
                string name = getCondVarName(expr);
                if(newPtrNames.find(name)!=newPtrNames.end()){
                    string message = "There is no sense in testing the '"+name+"' pointer against null, as the memory was allocated using the 'new' operator. The exception will be generated in the case of memory allocation error.";
                    addViolation(*it, this, message);
                }
            }
        }
        return true;
    }
};

static RuleSet rules(new NoSenseTestPointerAgainstNullAsMemAlloUseNewRule());
