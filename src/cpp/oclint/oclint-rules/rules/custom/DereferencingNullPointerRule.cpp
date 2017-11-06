#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"
#include<fstream>
using namespace std;
using namespace clang;
using namespace oclint;

struct PointerState{
    bool isPointer; //标记是否是指针
    string name;//指针名
    bool isNull;//是否为空
    bool deref;//是否引用指针内容
};

class DereferencingNullPointerRule : public AbstractASTVisitorRule<DereferencingNullPointerRule>
{
public:
    virtual const string name() const override
    {
        return "dereferencing null pointer";
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
        astContext = _carrier->getASTContext();
        
    }
    virtual void tearDown() override {
        
    }

    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *node)
    {
        Expr* cond = node->getCond();
        if(isa<BinaryOperator>(cond)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(cond);
            Expr* lhs = binaryOperator->getLHS();
            Expr* rhs = binaryOperator->getRHS();
            clang::BinaryOperatorKind bok = binaryOperator->getOpcode();
            
            if(bok!=BO_LAnd && bok!=BO_LOr)return true;
            
            PointerState ps1 = getLPointerState(lhs);
            PointerState ps2 = getRPointerState(rhs);
            bool violation=false;
            if(ps1.isPointer && ps2.isPointer && ps1.name==ps2.name){
                if(bok==BO_LAnd && ps1.isNull && ps2.deref)violation=true;
                else if(bok==BO_LOr && !ps1.isNull && ps2.deref)violation=true;
            }
            if(violation){
                string message = "Dereferencing of the null pointer '"+ps1.name+"' might take place. Check the logical condition.";
                addViolation(cond,this, message);
            }           
        }
        return true;
    }
    
    /* Visit DeclRefExpr */
    bool VisitDeclRefExpr(DeclRefExpr *node)
    {
        ValueDecl* valueDecl = node->getDecl();
        if(valueDecl->getType()->isPointerType()){//指针
            string name = valueDecl->getNameAsString();
            if(isRefNullInIfCondition(*node, name)){
                
                string nodeStr = expr2str(node);
                string message = "Dereferencing of the null pointer '"+nodeStr+"' might take place. Check the logical condition.";
                addViolation(node, this, message);
            }
        }
        return true;
    }
    
private:
    /*********************************************getLPointerState***********************************************************/
    void getType(const Expr* expr, int& type, string& name){
        type=-1;
        while(true){
            if(isa<ImplicitCastExpr>(expr)){
                auto implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = implicitCastExpr->getSubExpr();
            }else if(isa<IntegerLiteral>(expr)){
                auto integerLiteral = dyn_cast_or_null<IntegerLiteral>(expr);
                if(integerLiteral->getValue()==0)type=0;
                break;
            }else if(isa<DeclRefExpr>(expr)){
                auto declRefExpr = dyn_cast_or_null<DeclRefExpr>(expr);
                auto valueDecl = declRefExpr->getDecl();
                
                if(valueDecl->getType()->isPointerType() || valueDecl->getType()->isArrayType()){
                    type=1;
                    name = valueDecl->getNameAsString();
                }
                break;
            }else
                break;
        }
    }
    PointerState getLPointerState(const Expr* expr){
        PointerState ps;
        ps.isPointer=false;
        
        bool unary = false;
        
        if(isa<BinaryOperator>(expr)){
            auto binaryOperator = dyn_cast_or_null<BinaryOperator>(expr);
            auto bok = binaryOperator->getOpcode();
            if(bok!=BO_EQ && bok!=BO_NE)return ps;
            
            auto lhs = binaryOperator->getLHS();
            auto rhs = binaryOperator->getRHS();
            
            int ltype, rtype;
            string lname, rname;
            getType(lhs, ltype, lname);//type:0空，1:指针,-1:其他
            getType(rhs, rtype, rname);//name:若为指针，返回指针名
            
            ps.isPointer=true;
            if(bok==BO_EQ)ps.isNull=true;    
            else ps.isNull=false;
            
            if(ltype==1 && rtype==0) ps.name=lname;
            else if(ltype==0 && rtype==1)ps.name=rname;
            else ps.isPointer=false;
            return ps;
            
        }else if(isa<UnaryOperator>(expr)){
            auto unaryOperator = dyn_cast_or_null<UnaryOperator>(expr);
            expr = unaryOperator->getSubExpr();
            if(unaryOperator->getOpcode()==UO_LNot)unary=true; 
        }
        
        int type;
        string name;
        getType(expr, type, name);//type:0空，1:指针,-1:其他
        if(type==1){//指针
            ps.isPointer=true;
            ps.name=name;
            ps.isNull=false;
            if(unary)ps.isNull=true;
        }
        return ps;
    }
    
    /*********************************************getRPointerState***********************************************************/
    PointerState getRPointerState(Expr* expr){
        PointerState ps;
        ps.isPointer = false;
        bool deref = false;
        
        while(true){
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = implicitCastExpr->getSubExpr();
            }else if(isa<UnaryOperator>(expr)){
                UnaryOperator* unaryOperator = dyn_cast_or_null<UnaryOperator>(expr);
                if(unaryOperator->getOpcode()==UO_Deref)deref=true;
                expr = unaryOperator->getSubExpr();
            }else if(isa<ArraySubscriptExpr>(expr)){
                ArraySubscriptExpr* arraySubscriptExpr = dyn_cast_or_null<ArraySubscriptExpr>(expr);
                expr = arraySubscriptExpr->getBase();
                deref = true;
            }else if(isa<CXXMemberCallExpr>(expr)){
                CXXMemberCallExpr* cxxMemberCallExpr = dyn_cast_or_null<CXXMemberCallExpr>(expr);
                expr = cxxMemberCallExpr->getImplicitObjectArgument();
                deref = true;
            }else if(isa<MemberExpr>(expr)){
                MemberExpr* memberExpr = dyn_cast_or_null<MemberExpr>(expr);
                expr = memberExpr->getBase();
                deref = true;
            }else if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* declRefExpr = dyn_cast_or_null<DeclRefExpr>(expr);
                ValueDecl* valueDecl = declRefExpr->getDecl();
                if(valueDecl->getType()->isPointerType() || valueDecl->getType()->isArrayType()){
                    ps.isPointer = true;
                    ps.name = valueDecl->getNameAsString();
                    ps.deref = deref;
                }
                break;
            }else
                break;
        }
        return ps;
    }
    
    /********************************************* isRefNullInIfCondition ***********************************************************/
    bool isRefNullInIfCondition(const clang::Stmt& stmt, string name){
        
        bool deref = false;
        const Stmt *parent = NULL;
        const Stmt *child = &stmt;
        while(true){//找到第一个父ifStmt
            auto it = astContext->getParents(*child).begin();
            if(it == astContext->getParents(*child).end())
                return false;
        
            parent = it->get<clang::Stmt>();
            if(parent){
                if(isa<UnaryOperator>(parent)){
                    
                    
                    auto unaryOperator = dyn_cast<UnaryOperator>(parent);
                    if(unaryOperator->getOpcode()==UO_Deref){
                        deref = true;
                    }
                }else if(isa<IfStmt>(parent)){
                    break;
                }
            }else
                break;
            child = parent;
        }
        
        if(deref && parent && isa<IfStmt>(parent)){
            
            auto ifStmt = dyn_cast<IfStmt>(parent);
            
            if(ifStmt->getThen()==child){//child是否是if语句的then部分

                PointerState ps= getLPointerState(ifStmt->getCond());
                if(ps.isPointer && ps.isNull && ps.name == name){
                    return true;
                }
            }else{//从else跳出

                while(isa<IfStmt>(parent)){
                    
                    auto ifStmt = dyn_cast<IfStmt>(parent);
                    PointerState ps1= getLPointerState(ifStmt->getCond());
                    if(ps1.isPointer && !ps1.isNull && ps1.name == name){
                        return true;
                    }
                    auto it = astContext->getParents(*parent).begin();
                    if(it == astContext->getParents(*parent).end())
                        break;
                    parent = it->get<clang::Stmt>();
                }
                
            }
                
        }
        return false;
           
    }
    std::string expr2str(Expr *expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
    std::string stmt2str(const Stmt *stmt) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(stmt->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
private:
    SourceManager* sm;
    ASTContext* astContext;
    
};

static RuleSet rules(new DereferencingNullPointerRule()); 