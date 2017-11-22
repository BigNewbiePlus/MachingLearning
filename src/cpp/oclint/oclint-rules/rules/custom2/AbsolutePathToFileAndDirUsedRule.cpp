#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"

using namespace std;
using namespace clang;
using namespace oclint;

class AbsolutePathToFileAndDirUsedRule : public AbstractASTVisitorRule<AbsolutePathToFileAndDirUsedRule>
{
public:
    virtual const string name() const override
    {
        return "absolute path to file and dir used";
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
        if(funName=="fopen"){
            Expr* expr = callExpr->getArg(0);
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }
            if(isa<StringLiteral>(expr)){
                StringLiteral* sl = dyn_cast_or_null<StringLiteral>(expr);
                string path = sl.getString().str();
                if(path.find(":")!=string::npos){
                    string message = "Consider inspecting the 'fopen' function call. Defining an absolute path to the file or directory is considered a poor style.";
                    addViolation(callExpr, this, message);
                }
            }
        }
        return true;
    }
};

static RuleSet rules(new AbsolutePathToFileAndDirUsedRule());
