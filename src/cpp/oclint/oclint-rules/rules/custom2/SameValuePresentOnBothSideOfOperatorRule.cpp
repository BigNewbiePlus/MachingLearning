#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class SameValuePresentOnBothSideOfOperatorRule : public AbstractASTVisitorRule<SameValuePresentOnBothSideOfOperatorRule>
{
public:
    virtual const string name() const override
    {
        return "same value present on both side of operator";
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

    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        Expr* expr = ifStmt->getCond();
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(expr);
            BianryOperatorKind bok = binaryOperator->getOpcode();
            if(bok==BO_LT || bok==BO_GT || bok==BO_LE || bok==BO_GE || bok==EQ || bok==NE){
                vector<string> lhss, rhss;
                getOperandName(binaryOperator->getLHS(), lhss);
                getOperandName(binaryOperator->getRHS(), rhss);
                if(lhss.size()+rhss.size()>2){
                    for(auto lhs: lhss)
                        for(auto rhs: rhss){
                            if(lhs==rhs){
                                string message = "The '"+lhs+"' value is present on both sides of the '"++"' operator.";
                                addViolation(ifStmt, this, message);
                                return true;
                            }
                        }
                }
            }
        }
        return true;
    }

};

static RuleSet rules(new SameValuePresentOnBothSideOfOperatorRule());
