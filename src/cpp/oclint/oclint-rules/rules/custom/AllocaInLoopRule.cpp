#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class AllocaInLoopRule : public AbstractASTVisitorRule<AllocaInLoopRule>
{
public:
    virtual const string name() const override
    {
        return "alloca in loop";
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
        return "Aolloca In Loop Rule"; // TODO: fill in the description of the rule.
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
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {}

     /* Visit WhileStmt */
    bool VisitWhileStmt(WhileStmt *node)
    {
        Stmt* body = node->getBody();
        VisitLoopBody(body);
        return true;
    }
     

    /* Visit DoStmt */
    bool VisitDoStmt(DoStmt *node)
    {
        Stmt* body = node->getBody();
        VisitLoopBody(body);
        return true;
    }
     

    /* Visit ForStmt */
    bool VisitForStmt(ForStmt *node)
    {
        Stmt* body = node->getBody();
        VisitLoopBody(body);
        return true;
    }
    
    void VisitLoopBody(Stmt* body){
        if(isa<CompoundStmt>(body)){//如果是复合语句
            CompoundStmt* compoundStmt = dyn_cast_or_null<CompoundStmt>(body);
            for(clang::CompoundStmt::body_iterator it = compoundStmt->body_begin(); it!=compoundStmt->body_end();it++){
                Stmt* cur_body = *it;
                VisitDeclOrExpr(cur_body);
            }
        }else
            VisitDeclOrExpr(body);
    }
    
    void VisitDeclOrExpr(Stmt* stmt){
        string str = stmt2str(stmt);
        if(str.find("alloca")!=std::string::npos){//存在开辟空间
            addViolation(stmt, this, "The 'alloca' function is used inside the loop. This can quickly overflow stack.");
        }
    }
    
    std::string stmt2str(clang::Stmt *stmt) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
private:
    SourceManager* sm;

};

static RuleSet rules(new AllocaInLoopRule());
