#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class MemFunCallLeadOverOrUnderFlowWithSizeofRule : public AbstractASTVisitorRule<MemFunCallLeadOverOrUnderFlowWithSizeofRule>
{
public:
    virtual const string name() const override
    {
        return "mem fun call lead over or under flow with sizeof";
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
    /* Visit CallExpr */
    bool VisitCallExpr(CallExpr *node)
    {
        FunctionDecl* funcDecl = node->getDirectCallee();
        int argNums = node->getNumArgs();
        string funcName = funcDecl->getNameInfo().getAsString();
        if(argNums==3 && (funcName=="memset" || funcName=="memcpy")){
            Expr* arg1 = node->getArg(0);
            Expr* arg3 = node->getArg(2);
            
            int arg1Type = getArg1Type(arg1); //1:array, 2:pointer
            int arg3Type = getArg3Type(arg3); //11:sizeof(array),12:sizeof(*array),13:Integerliteral, 14:IntegerLiteral*sizeof(Int)
                                   //21:sizeof(point),22:sizeof(*point)
            bool violation=false;
            if(arg1Type==1 && (arg3Type==12 || arg3Type==13)){
                violation=true;
            }else if(arg1Type==2 && arg3Type==21){
                violation=true;
            }
            if(violation){
                string message = "A call of the '"+funcName+"' function will lead to a buffer overflow or underflow.";
                addViolation(node, this, message); 
            }
        }
        return true;
    }
private:
    int getArg1Type(Expr* arg1){ //1:array, 2:pointer
        if(isa<ImplicitCastExpr>(arg1)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(arg1);
            arg1 = implicitCastExpr->getSubExpr();
        }
        if(isa<ImplicitCastExpr>(arg1)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(arg1);
            arg1 = implicitCastExpr->getSubExpr();
        }
        if(isa<DeclRefExpr>(arg1)){
            DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(arg1);
            if(declRefExpr->getType()->isArrayType())return 1;
            if(declRefExpr->getType()->isPointerType())return 2;
        }
        return 0;
    }
    
    int getArg3Type(Expr* arg3){ //11:sizeof(array),12:sizeof(*array),13:Integerliteral, 14:IntegerLiteral*sizeof(Int)
                       //21:sizeof(point),22:sizeof(*point)
        if(isa<UnaryExprOrTypeTraitExpr>(arg3)){//sizeof
            UnaryExprOrTypeTraitExpr* unaryExprOrTypeTraitExpr = dyn_cast_or_null<UnaryExprOrTypeTraitExpr>(arg3);
            if(unaryExprOrTypeTraitExpr->getKind()!=UETT_SizeOf)return 0; //sizeof
            
            arg3 = unaryExprOrTypeTraitExpr->getArgumentExpr();
            if(isa<ParenExpr>(arg3)){
                ParenExpr* parenExpr = dyn_cast_or_null<ParenExpr>(arg3);
                arg3 = parenExpr->getSubExpr();
            }
            bool deref = false;
            if(isa<UnaryOperator>(arg3)){
                UnaryOperator* unaryOperator = dyn_cast_or_null<UnaryOperator>(arg3);
                arg3 = unaryOperator->getSubExpr();
                if(unaryOperator->getOpcode() == UO_Deref){
                   deref = true; 
                }
                
            }
            if(isa<ImplicitCastExpr>(arg3)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(arg3);
                arg3 = implicitCastExpr->getSubExpr();
            }
            int type=0; //1:array,2:pointer,0:未知
            if(isa<DeclRefExpr>(arg3)){
                DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(arg3);
                
                if(declRefExpr->getType()->isPointerType()) type=2;
                else if(declRefExpr->getType()->isArrayType()) type=1;
            }
            
            if(type==1){//array
                if(deref)return 12;
                else return 11;
            }else if(type==2){//pointer
                if(deref)return 22;
                else return 21;
            } 
            
        }else if(isa<BinaryOperator>(arg3)){
            return 14;
        }
        else{
            if(isa<ImplicitCastExpr>(arg3)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(arg3);
                arg3 = implicitCastExpr->getSubExpr();
                if(isa<IntegerLiteral>(arg3))return 13;
            }
            return 0;
        }
    }
};

static RuleSet rules(new MemFunCallLeadOverOrUnderFlowWithSizeofRule());