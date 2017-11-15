#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class FunctionReceivesAnOddArgumentRule : public AbstractASTVisitorRule<FunctionReceivesAnOddArgumentRule>
{
public:
    virtual const string name() const override
    {
        return "function receives an odd argument";
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

    /* Visit CallExpr */
    bool VisitCallExpr(CallExpr *callExpr)
    {
        string funName = callExpr->getDirectCallee()->getNameInfo().getAsString();
        if(funName=="memset" && callExpr->getNumArgs()==3){//memset函数，第三个参数表示设置内存大小，如果是0存在问题
            Expr* arg3 = callExpr->getArg(2); //获取第3个参数
            if(isa<IntegerLiteral>(arg3)){
                IntegerLiteral* integerLiteral = dyn_cast_or_null<IntegerLiteral>(arg3);
                if(integerLiteral->getValue().getSExtValue()==0){
                    string message = "The 'memset' function processes '0' elements. Inspect the third argument.";
                    addViolation(callExpr, this, message);
                }
            }
        }
        return true;
    }
};

static RuleSet rules(new FunctionReceivesAnOddArgumentRule());
    
