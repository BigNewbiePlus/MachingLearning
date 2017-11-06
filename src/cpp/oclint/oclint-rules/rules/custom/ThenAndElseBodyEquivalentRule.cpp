#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

using namespace std;
using namespace clang;
using namespace oclint;

class ThenAndElseBodyEquivalentRule : public AbstractASTVisitorRule<ThenAndElseBodyEquivalentRule>
{
public:
    virtual const string name() const override
    {
        return "then and else body equivalent";
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
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {}
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *ifStmt)
    {
        vector<string> bodys = getThenElseBodys(ifStmt);
        
        for(int i=0;i<bodys.size()-1;i++)
            for(int j=i+1;j<bodys.size();j++){
       
            if(bodys[i]==bodys[j]){
                addViolation(ifStmt, this, "The 'then' statement is equivalent to the 'else' statement.");
                return true;
            }
        }
        
        return true;
    }
private:
    vector<string> getThenElseBodys(IfStmt* ifStmt){
      
        vector<string> bodys;
        if(!ifStmt->getElse())return bodys;
        
        Stmt* thenStmt;
        Stmt* elseStmt;
        while(true){
            thenStmt = ifStmt->getThen();
            bodys.push_back(stmt2str(thenStmt));
            
            elseStmt = ifStmt->getElse();
            if(!elseStmt)break;
            
            if(isa<IfStmt>(elseStmt)){
                ifStmt = dyn_cast<IfStmt>(elseStmt);    
            }else{
                bodys.push_back(stmt2str(elseStmt));
                break;    
            }
           
        }
        return bodys;
    }
    
    std::string stmt2str(Stmt *stmt) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    } 
private:
    SourceManager* sm;
};

static RuleSet rules(new ThenAndElseBodyEquivalentRule());