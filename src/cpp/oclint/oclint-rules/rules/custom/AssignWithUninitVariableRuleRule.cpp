#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
#include "clang/Lex/Lexer.h"

#include<iostream>
#include<fstream>
    
using namespace std;
using namespace clang;
using namespace oclint;

class ParamInfo{
public:
    bool ref; //是否引用类型
    bool init;//是否初始化了
    int index;//下标
};

class AssignWithUninitVariableRuleRule : public AbstractASTVisitorRule<AssignWithUninitVariableRuleRule>
{
public:
    virtual const string name() const override
    {
        return "assign with uninit variable rule";
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
    
    virtual bool enableSuppress() const override
    {
        return true;
    }
    
#endif

    virtual void setUp() override {
        myfile.open ("/home/lupeng/example.txt", ios::app);
        //myfile<<"\n\n\n******************************************"<<endl;
        rule = this;
        literal = "Literal"; //字面值,表示变量值
        maxlevel = 2; //最大探查深度
        sm = &_carrier->getSourceManager();
    }
    virtual void tearDown() override {
        myfile.close();
    }

    //Visit FunctionDecl
    bool VisitFunctionDecl(FunctionDecl *fun_decl)
    {
        int param_num = fun_decl->getNumParams();
        vector<bool> parent_params_info(param_num, true);//默认情况下父参数均已赋值
        map<string, ParamInfo> child_params_info;//调用函数的参数状况，需要回执
        vector<string> wrong_info; //下级和参数相关的出错语句
        checkFunc(fun_decl, parent_params_info, child_params_info, wrong_info, 1);//检测函数
        return true;
    }
private:
    /***********************************************************************************************/
    /******************************************  Util Func *****************************************/
    /***********************************************************************************************/
    string concateStr(vector<string> strs){
        string res="";
        if(strs.size()>0)res="'"+strs[0]+"'";
        for(int i=1;i<strs.size();i++){
            res += ",'"+strs[i]+"'";
        }
        return res;
    }
    string getDeclRefExprName(Expr* expr){
        if(isa<DeclRefExpr>(expr)){ //变量引用
            DeclRefExpr * ref = dyn_cast_or_null<DeclRefExpr>(expr);
            return ref->getNameInfo().getAsString();
        }
        if(isa<ImplicitCastExpr>(expr)){//强制转化表达式
            ImplicitCastExpr *implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            DeclRefExpr *initExpr = dyn_cast_or_null<DeclRefExpr>(implicitCastExpr->getSubExpr());
            return initExpr->getNameInfo().getAsString();
        }
        return literal;
    }
    std::string decl2str(clang::Decl *d) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(
            CharSourceRange::getTokenRange(d->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(d->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
    std::string expr2str(Expr *expr) {
        // (T, U) => "T,,"
        string text = clang::Lexer::getSourceText(CharSourceRange::getTokenRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        if (text.at(text.size()-1) == ',')
            return clang::Lexer::getSourceText(CharSourceRange::getCharRange(expr->getSourceRange()), *sm, LangOptions(), 0);
        return text;
    }
    /***********************************************************************************************/
    /******************************************  Func Check ***************************************/
    /**********************************************************************************************/
    void checkFunc(FunctionDecl *fun_decl, vector<bool>& parent_params_info,
                   map<string, ParamInfo> &child_params_info, vector<string>& wrong_info, int level)
    {
        if(level>maxlevel)return; //设置最大遍历的调用层，超出退出 
        if(!fun_decl->hasBody())return;//不存在定义，退出
        
        //需要维护的三个状态：本参数信息，变量初始化状态，错误子句, 
        //其中参数信息和错误子句由上层传入，由本层获取
        map<string, bool> vars_init; //本层只维护变量初始化状态：记录各变量初始化状态，包括参数
        
        //获取当前参数信息，是否初始化和是否引用
        unsigned int params_num = fun_decl->getNumParams();
        for(unsigned int i=0;i<params_num;i++){
            ParamInfo param_info;
            param_info.ref=false, param_info.index=i, param_info.init = parent_params_info[i];
            ParmVarDecl* p = fun_decl->getParamDecl(i);
            QualType original_type = p->getOriginalType();
            
            if(original_type->isReferenceType()){
                param_info.ref=true; //引用参数标记
            }
            string p_name = p->getNameAsString();
            child_params_info[p_name]=param_info;
            vars_init[p_name]=parent_params_info[i]; //从上级函数获取当前参数状态。
        }
        vars_init[literal]=true; //字面值为真实值
        
        //获取当前函数主题内容
        Stmt* funBody = fun_decl->getBody();
        
        CompoundStmt* compoundStmt = dyn_cast_or_null<CompoundStmt>(funBody);      
        if(!compoundStmt)return;

        for (CompoundStmt::body_iterator body = compoundStmt->body_begin(), bodyEnd = compoundStmt->body_end();
             body != bodyEnd; body++){
            Stmt* bodyStmt = *body;      //获取其中一条语句
            
            if(isa<DeclStmt>(bodyStmt)){
                DeclStmt* declStmt = dyn_cast_or_null<DeclStmt>(bodyStmt); //获取声明语句
                checkDeclStmt(declStmt, child_params_info, vars_init, wrong_info, level); 
            }else if(isa<BinaryOperator>(bodyStmt)){
                BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(bodyStmt);
                checkBinaryOperator(binaryOperator, child_params_info, vars_init, wrong_info, level);   
            }else if(isa<CallExpr>(bodyStmt)){//调用表达式  
                CallExpr* callExpr = dyn_cast_or_null<CallExpr>(bodyStmt);//转化
                checkCallExpr(callExpr, child_params_info, vars_init, wrong_info, level); //搜集调用函数对变量的赋值情况
            }       
        }
        
        //对当前参数信息更新，回馈给上层函数
        for(map<string, ParamInfo>::iterator it=child_params_info.begin(); it!=child_params_info.end();it++){
            it->second.init = vars_init[it->first];
        }
    }
    /***********************************************************************************************/
    /******************************************  Decl Check ***************************************/
    /**********************************************************************************************/
    void declViolation(vector<string>& violation_vars, Decl* decl, vector<string>& wrong_info, int level){
        string res = concateStr(violation_vars);
        string decl_str = "'"+decl2str(decl)+"'";   
        if(level==1){
            res = decl_str+" The local variable "+res + " is uninitialized!";
            addViolation(decl, rule, res);
        }else{
            res = decl_str+" The parameters "+res + " is uninitialized!";
            wrong_info.push_back(res);    
        }
    }
    
    void checkDeclStmt(DeclStmt* declStmt, map<string, ParamInfo>& child_params_info, map<string, bool>& vars_init,
        vector<string>& wrong_info, int level)
    {    
        for(clang::DeclGroupRef::iterator decl = declStmt->decl_begin(); decl != declStmt->decl_end(); decl++)
        {
            Decl* one_decl = *decl;
            if(isa<VarDecl>(one_decl)){//如果是变量表达式
                VarDecl* var_decl = dyn_cast_or_null<VarDecl>(one_decl);
                Expr* init_expr = var_decl->getInit(); //得到该变量的初始化语句
                if(!init_expr) continue; //该变量为初始化,跳过
                
                std::string lname = var_decl->getNameAsString();
                
                vector<string> rnames = checkNonAssignBinaryOperator(init_expr);//获取初始化表达式涉及的所有变量
                
                vector<string> violation_vars = checkViolationVars(child_params_info, vars_init, rnames, level);
                if(violation_vars.size()==0){//未违反
                    vars_init[lname]=true;
                }else{//违反了
                    declViolation(violation_vars, one_decl, wrong_info, level);
                }
            }
        }
    }
    
    bool isaLiteral(Expr* expr){
        if(isa<IntegerLiteral>(expr) || isa<CharacterLiteral>(expr) || isa<FloatingLiteral>(expr) ||
          isa<StringLiteral>(expr)){
            return true;
        }
        return false;
    }
    vector<string> checkNonAssignBinaryOperator(Expr* expr){
        vector<string> result;
        if(isa<BinaryOperator>(expr)){
            BinaryOperator* binaryOperator = dyn_cast_or_null<BinaryOperator>(expr);
            vector<string> lv = checkNonAssignBinaryOperator(binaryOperator->getLHS());
            vector<string> rv = checkNonAssignBinaryOperator(binaryOperator->getRHS());
            result.insert(result.end(), lv.begin(), lv.end());
            result.insert(result.end(), rv.begin(), rv.end());
            return result;
        }
        if(isa<CallExpr>(expr) || isaLiteral(expr)){//调用了函数或是个变量值
            result.push_back(literal);
            return result;
        }
        if(isa<ParenExpr>(expr)){//带括号
            ParenExpr* parenExpr = dyn_cast_or_null<ParenExpr>(expr);
            result = checkNonAssignBinaryOperator(parenExpr->getSubExpr());
            return result;
        }
        if(isa<ImplicitCastExpr>(expr)){//强制转化表达式
            ImplicitCastExpr *implicitCastExpr = dyn_cast_or_null<ImplicitCastExpr>(expr);
            DeclRefExpr *initExpr = dyn_cast_or_null<DeclRefExpr>(implicitCastExpr->getSubExpr());
            std::string rname =  initExpr->getNameInfo().getAsString();
            result.push_back(rname);
        }
        return result;
    }
    
    //检测是否违背未赋值先使用
    vector<string> checkViolationVars(map<string, ParamInfo>& child_params_info, map<string, bool>& vars_init, 
                                      vector<string>& rnames, int level){
        //遍历赋值表达式中的变量
        vector<string> violation_vars;
        for(auto rname: rnames){
            if(vars_init[rname]==false){//违反
                if(level==1){//当前层，查找和参数无关的错误
                    violation_vars.push_back(rname);
                }
                else if(level>1 && child_params_info.find(rname)!=child_params_info.end()) //子函数中查找错误，只显示和参数相关问题
                {
                    violation_vars.push_back(rname);
                }
            }
        }
        return violation_vars;
    }
    /***********************************************************************************************/
    /**************************************  Binary Operator Check *********************************/
    /**********************************************************************************************/
    void exprViolation(vector<string>& violation_vars, Expr* expr, vector<string>& wrong_info, int level){
        string res = concateStr(violation_vars);
        string expr_str = "'"+expr2str(expr)+"'";   
        if(level==1){
            res = expr_str+" The local variable "+res + " is uninitialized!";
            addViolation(expr, rule, res);
        }else{
            res = expr_str+" The parameters "+res + " is uninitialized!";
            wrong_info.push_back(res);    
        }
    }
    void checkBinaryOperator(BinaryOperator* binaryOperator, map<string, ParamInfo>& child_params_info, 
                             map<string, bool>& vars_init, vector<string>& wrong_info, int level){
        Expr* rhs = binaryOperator;
        //解析赋值语句和表达式语句
        vector<string> lnames;
        while(isa<BinaryOperator>(rhs)){
            BinaryOperator* binary = dyn_cast_or_null<BinaryOperator>(rhs);
            if(binary->isAssignmentOp()){
                Expr* lhs = binaryOperator->getLHS(); //获取左端
                rhs = binaryOperator->getRHS(); //获取赋值符号右端
                string lname = getDeclRefExprName(lhs); //获取左端变量名
                lnames.push_back(lname); //记录
            }else{
                break;
            }
        }
        
        if(lnames.size()==0)return; //非赋值二元表达式，退出
        vector<string> rnames = checkNonAssignBinaryOperator(rhs); //获取赋值语句等号右端表达式涉及的变量
        
        vector<string> violation_vars = checkViolationVars(child_params_info, vars_init, rnames, level);
        if(violation_vars.size()==0){//未违反
            for(auto lname:lnames) vars_init[lname]=true; 
        }else{//违反了
            exprViolation(violation_vars, binaryOperator, wrong_info, level);    
        }
    }
            
    /************************************************************************************************/
    /******************************************  Call Expr Check ************************************/
    /************************************************************************************************/
    void callFuncViolation(CallExpr* callExpr, vector<string>& wrong_info)
    {
        string expr_str = "'"+expr2str(callExpr)+"'";
        for(auto str:wrong_info){
            string message = expr_str+" Function call error! "+str;
            addViolation(callExpr, rule, message);    
        }        
    }
    
    void checkCallExpr(CallExpr* callExpr, map<string, ParamInfo>& child_params_info, 
                       map<string, bool>& vars_init, vector<string>& wrong_info, int level){
        FunctionDecl *fun_decl = callExpr->getDirectCallee();
        if(!fun_decl->hasBody())return; //函数没定义，退出
        
        //获取调用函数调用的参数名
        unsigned int arg_num = callExpr->getNumArgs();
        
        vector<bool> parent_params_init(arg_num);//调用时变量是否初始化
        vector<string> parent_params_name(arg_num);//调用函数时传入的变量名
        
        for(unsigned int i=0;i<arg_num;i++){
            Expr* argExpr = callExpr->getArg(i);
            string argName = getDeclRefExprName(argExpr); //获取左端变量名
            parent_params_name[i] = argName;//记录Index-name
            parent_params_init[i] = vars_init[argName];//记录index-init
        }
        
        map<string, ParamInfo> callee_params_info;//参数初始化表，记录该参数是否初始化和引用
        checkFunc(fun_decl, parent_params_init, callee_params_info, wrong_info, level+1);
        
        //函数调用过程中，参数变化信息
        for(map<string, ParamInfo>::iterator it=callee_params_info.begin(); it!=callee_params_info.end();it++){
            if(it->second.ref){//参数为引用
                int index = it->second.index;
                vars_init[parent_params_name[index]] = it->second.init;
            }
        }
        
        //子函数存在的问题
        if(wrong_info.size()>0 && level==1){//存在问题且当前层
            callFuncViolation(callExpr, wrong_info);
            wrong_info.clear();
        }
    }
    

private:
    ofstream myfile;
    RuleBase* rule;
    string literal;
    int maxlevel;
    clang::SourceManager *sm;
};

static RuleSet rules(new AssignWithUninitVariableRuleRule());
