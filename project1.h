#include <iostream>
//#include <iomanip>
//#include <cassert>

using namespace std;

//forward declaration
class treeNode;

//pointer declaration with nickname
typedef treeNode* treeNodePtr;

class treeNode
{
public:

//constructor
treeNode(bool is_operand, double key, char op, treeNodePtr lp, treeNodePtr rp)
{
    flag = is_operand;
    value = key;
    optr = op;
    left = lp;
    right = rp;
};

bool getFlag()
{
    return flag;
}

double getValue()
{
    return value;
}

char getOperator()
{
    return optr;
}

treeNodePtr getLeft()
{
    return left;
}

treeNodePtr getRight()
{
    return right;
}

private:
bool flag;
double value;
char optr;
treeNodePtr left;
treeNodePtr right;

};
