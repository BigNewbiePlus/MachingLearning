#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
#include<fstream>
using namespace std;
using namespace clang;
using namespace oclint;

class TwoFunctionBodyEquivalentRule : public AbstractASTVisitorRule<TwoFunctionBodyEquivalentRule>
{
public:
    virtual const string name() const override
    {
        return "two function body equivalent";
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
        fwrite.open("/home/fdh/info.txt",ios::app);
    }
    virtual void tearDown() override {
        checkFuncDecls();
        checkCXXMethodDecls();
        
        fwrite.close();
        
    }

    /* Visit FunctionDecl */
    bool VisitFunctionDecl(FunctionDecl *node)
    {
        if(node->hasBody())
            functionDecls.push_back(node);
        return true;
    }
     

    /* Visit CXXMethodDecl */
    bool VisitCXXMethodDecl(CXXMethodDecl *node)
    {
        if(node->hasBody())
            cxxMethodDecls.push_back(node);
        return true;
    }
    
private:

    std::string stmt2str(Stmt *stmt) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
    
    inline int getLineNum(FunctionDecl* funcDecl){
        SourceLocation start = funcDecl->getLocStart();
        SourceLocation end = funcDecl->getLocEnd();
        
        unsigned startLine = sm->getSpellingLineNumber(start,0);
        unsigned endLine = sm->getSpellingLineNumber(end,0);
        return endLine-startLine;
    }
 
    inline int getLineNum(CXXMethodDecl* funcDecl){
        SourceLocation start = funcDecl->getLocStart();
        SourceLocation end = funcDecl->getLocEnd();
        
        unsigned startLine = sm->getSpellingLineNumber(start,0);
        unsigned endLine = sm->getSpellingLineNumber(end,0);
        return endLine-startLine;
    }
    
    bool hasSameLines(FunctionDecl* funcDecl1, FunctionDecl* funcDecl2)
    {
        int lineNum1 = getLineNum(funcDecl1);
        int lineNum2 = getLineNum(funcDecl2);
        return lineNum1 == lineNum2; 
    } 
    bool hasSameLines(CXXMethodDecl* funcDecl1, CXXMethodDecl* funcDecl2)
    {
        int lineNum1 = getLineNum(funcDecl1);
        int lineNum2 = getLineNum(funcDecl2);
        return lineNum1 == lineNum2; 
    }     
    bool hasSameBody(FunctionDecl* funcDecl1, FunctionDecl* funcDecl2){
        Stmt* body1 = funcDecl1->getBody();
        Stmt* body2 = funcDecl2->getBody();
        
        string body1Str = stmt2str(body1);
        string body2Str = stmt2str(body2);
        return body1Str == body2Str;
    }

    bool hasSameBody(CXXMethodDecl* funcDecl1, CXXMethodDecl* funcDecl2){
        Stmt* body1 = funcDecl1->getBody();
        Stmt* body2 = funcDecl2->getBody();
        
        string body1Str = stmt2str(body1);
        string body2Str = stmt2str(body2);
        return body1Str == body2Str;
    }
    void checkFuncDecls()
    {
        for(int i=0;i<functionDecls.size()-1;i++){
            for(int j=i+1;j<functionDecls.size();j++){
                
                if(hasSameLines(functionDecls[i], functionDecls[j])){
                    if(hasSameBody(functionDecls[i], functionDecls[j])){
                        string func1Name = functionDecls[i]->getNameInfo().getAsString();
                        string func2Name = functionDecls[j]->getNameInfo().getAsString();
                        string message = "It is odd that the body of '"+func1Name+"' function is fully equivalent to the body of '"+
                            func2Name+"' function.";
                        addViolation(functionDecls[i],this, message);
                    }
                }
                
            }
               
        }
    }


    void checkCXXMethodDecls(){
      
        for(int i=0;i<cxxMethodDecls.size()-1;i++){
            for(int j=i+1;j<cxxMethodDecls.size();j++){
                
                if(hasSameLines(cxxMethodDecls[i], cxxMethodDecls[j])){
                    if(hasSameBody(cxxMethodDecls[i], cxxMethodDecls[j])){
                        string func1Name = cxxMethodDecls[i]->getNameInfo().getAsString();
                        string func2Name = cxxMethodDecls[j]->getNameInfo().getAsString();
                        string message = "It is odd that the body of '"+func1Name+"' function is fully equivalent to the body of '"+
                            func2Name+"' function.";
                        addViolation(cxxMethodDecls[i],this, message);
                    }
                }
                
            }
               
        } 
    }
private:
    vector<FunctionDecl*> functionDecls;
    vector<CXXMethodDecl*> cxxMethodDecls;
    
    SourceManager* sm;
    ofstream fwrite;
     
};

static RuleSet rules(new TwoFunctionBodyEquivalentRule());  