#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class InvalidPointToLocalArrayRule : public AbstractASTVisitorRule<InvalidPointToLocalArrayRule>
{
public:
    virtual const string name() const override
    {
        return "invalid point to local array";
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

    virtual void setUp() override {}
    virtual void tearDown() override {}
    
    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *node)
    {
        map<string, bool> localVarNames;
        for(clang::CompoundStmt::body_iterator body_it = node->body_begin(); body_it!=node->body_end();body_it++){
            Stmt* body = *body_it;
            if(isa<DeclStmt>(body)){
                DeclStmt* declStmt = dyn_cast_or_null<DeclStmt>(body);
                getLocalDeclVarsName(declStmt, localVarNames);
            }else if(isa<BinaryOperator>(body)){
                BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(body);
                Expr* lhs = binaryOperator->getLHS();
                Expr* rhs = binaryOperator->getRHS();
                if(binaryOperator->getOpcodeStr()=="=" && 
                   isPointerType(lhs) && isArrayType(rhs)){//赋值运算且左侧为指针变量
                    
                    string lname = getLHSName(lhs, localVarNames);
                    string rname = getRHSName(rhs, localVarNames);
                    if(localVarNames.find(lname)==localVarNames.end() 
                       && localVarNames.find(rname)!=localVarNames.end()){
                        string message = "Pointer to local array '"+rname+"' is stored outside the scope of this array. Such a pointer will become invalid.";
                        addViolation(body,this, message);
                    }
                }
            }        
        }
        return true;
    }
    
private:
    void getLocalDeclVarsName(DeclStmt* declStmt, map<string,bool>& varNames){
        for(clang::DeclStmt::decl_iterator decl_it = declStmt->decl_begin(); decl_it!=declStmt->decl_end();decl_it++){
            Decl* decl = *decl_it;
            if(isa<VarDecl>(decl)){
                VarDecl* varDecl = dyn_cast_or_null<VarDecl>(decl);
                string varName = varDecl->getNameAsString();
                varNames[varName]=true;
            }
        }
        
    }
    bool isPointerType(Expr* expr){
        return expr->getType()->isPointerType();
    }
    
    bool isArrayType(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        return expr->getType()->isArrayType();
    }
    
    string getLHSName(Expr* lhs, map<string, bool>& localVarNames){
        string lname;
        if(isa<DeclRefExpr>(lhs)){
            DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(lhs);
            lname = declRefExpr->getNameInfo().getAsString();
        }
        return lname;
    }
    string getRHSName(Expr* rhs, map<string, bool>& localVarNames){
        string rname;
        if(isa<UnaryOperator>(rhs)){            
            UnaryOperator* unaryOperator = dyn_cast_or_null<UnaryOperator>(rhs);                
            rhs = unaryOperator->getSubExpr();            
        }
        if(isa<ImplicitCastExpr>(rhs)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(rhs);
            rhs = implicitCastExpr->getSubExpr();
        }
        if(isa<DeclRefExpr>(rhs)){
            DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(rhs);
            rname = declRefExpr->getNameInfo().getAsString();
        }
        return rname;
    }

};

static RuleSet rules(new InvalidPointToLocalArrayRule());