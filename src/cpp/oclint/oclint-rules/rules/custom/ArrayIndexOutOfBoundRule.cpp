#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ArrayIndexOutOfBoundRule : public AbstractASTVisitorRule<ArrayIndexOutOfBoundRule>
{
public:
    virtual const string name() const override
    {
        return "array index out of bound";
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
    /* Visit ArraySubscriptExpr */
    bool VisitArraySubscriptExpr(ArraySubscriptExpr *node)
    {
        Expr* base = node->getBase();
        Expr* idx = node->getIdx();
        
        int bound = getArrayBound(base);
        int index = getIndex(idx);
        if(bound!=-1 && index!=-1 && index>=bound){
            string message = "Array overrun is possible. The '"+to_string(index)+"' index is pointing beyond array bound.";
            addViolation(node,this,message);
        }
        return true;
    }
    
private:
    int getArrayBound(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<DeclRefExpr>(expr)){
           DeclRefExpr* declRefExpr = dyn_cast<DeclRefExpr>(expr);
            ValueDecl* valueDecl = declRefExpr->getDecl();
            if(valueDecl->getType()->isArrayType()){  
                string type = valueDecl->getType().getAsString();
                return getNum(type);  
            }
        }
        return -1;
    }
    
    int getNum(string type){
        string res;
        for(int i=0;i<type.size();i++){
            if(type[i]=='['){
                while(i<type.size() && type[++i]!=']')res.push_back(type[i]);
            }
        }
        if(res.size()){
            int result=0;
            for(int i=0;i<res.size();i++)result = result*10+res[i]-'0';
            return result;
        }
        return -1;
        
    }
    
    int getIndex(Expr* expr){
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<IntegerLiteral>(expr)){
            IntegerLiteral* integerLiteral = dyn_cast<IntegerLiteral>(expr);
            return integerLiteral->getValue().getSExtValue();
        }
        return -1;
    }
};

static RuleSet rules(new ArrayIndexOutOfBoundRule());