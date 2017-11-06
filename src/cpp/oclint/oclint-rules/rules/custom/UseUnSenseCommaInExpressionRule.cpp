#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
  
using namespace std;
using namespace clang;
using namespace oclint;

class UseUnSenseCommaInExpressionRule : public AbstractASTVisitorRule<UseUnSenseCommaInExpressionRule>
{
public:
    virtual const string name() const override
    {
        return "use un sense comma in expression";
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

    /* Visit BinaryOperator */
    bool VisitBinaryOperator(BinaryOperator *node)
    {
        if(node->getOpcode()==BO_Comma){
            checkUnsenseExpr(node->getLHS());
            checkUnsenseExpr(node->getRHS());
        }
        return true;
    }
    
private:
    void checkUnsenseExpr(Expr* expr){
        string message = "Such expressions using the ',' operator are dangerous. Make sure the expression is correct.";
        
        if(isa<CompoundAssignOperator>(expr)){
                   
        }else if(isa<BinaryOperator>(expr)){          
            BinaryOperator* binaryOperator = dyn_cast<BinaryOperator>(expr);
            BinaryOperatorKind bok = binaryOperator->getOpcode();
            
            if(bok==BO_Comma){
                checkUnsenseExpr(binaryOperator->getLHS());
                checkUnsenseExpr(binaryOperator->getRHS()); 
            }else if(bok!=BO_Assign){
                addViolation(expr, this, message);
                
            }
        }else if(isa<UnaryOperator>(expr)){    
            UnaryOperator* unaryOperator = dyn_cast_or_null<UnaryOperator>(expr);
            UnaryOperatorKind uok = unaryOperator->getOpcode();
            
            if((uok!=UO_PostInc) && (uok!=UO_PostDec) && (uok!=UO_PreInc) && (uok!=UO_PreDec)){
                addViolation(expr, this, message);
                
            }
            
        }else{
            addViolation(expr, this, message);
            
        }   
    }
};

static RuleSet rules(new UseUnSenseCommaInExpressionRule()); 