#include "oclint/AbstractASTVisitorRule.h"
#include "oclint/RuleSet.h"
using namespace std;
using namespace clang;
using namespace oclint;

class RangeIntersectionAreWithinConditionExpressionRule : public AbstractASTVisitorRule<RangeIntersectionAreWithinConditionExpressionRule>
{
public:
    virtual const string name() const override
    {
        return "range intersection are within condition expression";
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


    bool getDeclRefExpr(Expr* expr, string& name){
        while(expr){
            if(isa<ImplicitCastExpr>(expr)){
                ImplicitCastExpr* ice = dyn_cast_or_null<ImplicitCastExpr>(expr);
                expr = ice->getSubExpr();
            }else if(isa<DeclRefExpr>(expr)){
                DeclRefExpr* dre = dyn_cast_or_null<DeclRefExpr>(expr);
                name = dre->getNameInfo().getAsString();
                return true;
            }else break;
        }
        return false;
    }
    bool getBinaryCompareCondInfo(Expr* cond, string& name, BinaryOperatorKind& bok, int& value){
        if(isa<BinaryOperator>(cond)){
            BinaryOperator* bo = dyn_cast_or_null<BinaryOperator>(cond);
            BinaryOperatorKind bokTmp = bo->getOpcode();
            if(bokTmp==BO_GT||bokTmp==BO_GE)bok=BO_GT; 
            else if(bokTmp==BO_LT||bokTmp==BO_LE)bok=BO_LT;
            else return false;

            if(isa<IntegerLiteral>(bo->getRHS())){
                IntegerLiteral* il = dyn_cast_or_null<IntegerLiteral>(bo->getRHS());
                value = il->getValue().getSExtValue();
            }else return false;

            return getDeclRefExpr(bo->getLHS(), name);
        }
        return false;
    }
    /* Visit IfStmt */
    bool VisitIfStmt(IfStmt *is)
    {
        Expr* cond1 = is->getCond();
        Stmt* elStmt = is->getElse();
        if(elStmt && isa<IfStmt>(elStmt)){
            IfStmt* is2 = dyn_cast_or_null<IfStmt>(elStmt);
            Expr* cond2 = is2->getCond();

            string varName1, varName2;
            BinaryOperatorKind bok1, bok2;
            int value1, value2;
            if(getBinaryCompareCondInfo(cond1, varName1, bok1, value1) && getBinaryCompareCondInfo(cond2, varName2, bok2, value2) && varName1.size() && varName1==varName2){
                if((bok1==BO_GT && bok2==bok1 && value1<value2) || (bok1==BO_LT && bok1==bok2 && value1>value2)){
                    string message = "Range intersections are possible within conditional expressions. Example: if (A < 5) { ... } else if (A < 2) { ... }.";
                    addViolation(is, this, message);
                }
            }
        }
        return true;
    }
    
};

static RuleSet rules(new RangeIntersectionAreWithinConditionExpressionRule());
