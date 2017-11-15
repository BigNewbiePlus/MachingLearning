#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class FooFunctionCalledTwiceForDeallocationRule : public AbstractASTVisitorRule<FooFunctionCalledTwiceForDeallocationRule>
{
public:
    virtual const string name() const override
    {
        return "foo function called twice for deallocation";
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
        sm =&_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

    /* Visit CompoundStmt */
    bool VisitCompoundStmt(CompoundStmt *compoundStmt)
    {
        map<string, int> objNames;
        for(CompoundStmt::body_iterator it=compoundStmt->body_begin(); it!=compoundStmt->body_end(); it++){
            if(isa<CXXMemberCallExpr>(*it)){
                CXXMemberCallExpr* callExpr = dyn_cast_or_null<CXXMemberCallExpr>(*it);
                string funcName = callExpr->getMethodDecl()->getNameInfo().getAsString();
                if(funcName=="clear"){
                    string objName = expr2str(callExpr->getImplicitObjectArgument());
                    objNames[objName]++;
                    if(objNames[objName]==2){
                        string message = "The 'clear' function is called twice for deallocation of the same resource.";
                        addViolation(*it, this, message);
                        return true;
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

static RuleSet rules(new FooFunctionCalledTwiceForDeallocationRule()); 
