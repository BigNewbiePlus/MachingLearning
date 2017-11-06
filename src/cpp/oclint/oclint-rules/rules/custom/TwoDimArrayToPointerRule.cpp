#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include<fstream>
using namespace std;
using namespace clang;
using namespace oclint;

class TwoDimArrayToPointerRule : public AbstractASTVisitorRule<TwoDimArrayToPointerRule>
{
public:
    virtual const string name() const override
    {
        return "two dim array to pointer";
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
    }
    virtual void tearDown() override {}

    /* Visit CStyleCastExpr */
    bool VisitCStyleCastExpr(CStyleCastExpr *node)
    {
        string str = node->getTypeAsWritten().getAsString();
        if(!isTwoPointer(str))return true;
        Expr* expr = node->getSubExpr();
        
        if(isa<ImplicitCastExpr>(expr)){
            ImplicitCastExpr* implicitCastExpr = dyn_cast<ImplicitCastExpr>(expr);
            expr = implicitCastExpr->getSubExpr();
        }
        if(isa<DeclRefExpr>(expr)){
            DeclRefExpr* declRefExpr = dyn_cast<DeclRefExpr>(expr);
            string declType = declRefExpr->getType().getAsString();
            
            if(isTwoArray(declType)){
                addViolation(node,this,"Consider reviewing type casting. TYPE X[][] in not equivalent to TYPE **X.");
            }
            
        }
        return true;
    }
private:
    bool isTwoPointer(string str){
        return (str.size()>1) && (str[str.size()-1]=='*') && (str[str.size()-2]=='*');
    }
    
    bool isTwoArray(string str){
        int num=0;
        for(int i=0;i<str.size();i++){
            if(str[i]=='[')num++;
            else if(str[i]==']')num++;
        }
        return num==4;
    }
     
};

static RuleSet rules(new TwoDimArrayToPointerRule()); 