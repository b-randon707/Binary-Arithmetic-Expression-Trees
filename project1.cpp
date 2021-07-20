#include <iostream>
#include <fstream>
//#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include <stack>
#include "project1.h"

using namespace std;


//check if there is matching open parenthesis in operator stack
bool open_Parenthesis(stack<char> s) {

    stack<char> temps;
    char r;
    int x = 0;

    while (!s.empty()) {
        r = s.top();
        temps.push(r);
        s.pop();

        if (r == '(') {
            while (!temps.empty()) {
                s.push(temps.top());
                temps.pop();
            }
            return true;
        }
    }

    while (!temps.empty()) {
        s.push(temps.top());
        temps.pop();
    }
    return false;
}





//Display tree inOrder
void inOrderTraversal(treeNodePtr p) {
    if (p != NULL) {
        if (p->getFlag() == true) {             //if current pointer is an operand
            inOrderTraversal(p->getLeft());     //get  operand value and continue inOrder traversal
            cout << p->getValue() << " ";
            inOrderTraversal(p->getRight());
        }
        else if (p->getFlag() == false) {       //if current pointer is an operator
            inOrderTraversal(p->getLeft());     //get operator value and continue inOrder traversal
            cout << p->getOperator() << " ";
            inOrderTraversal(p->getRight());
        }
    }
}

//Display tree postOrder
void postOrderTraversal(treeNodePtr p) {
    if (p != NULL) {
        if (p->getFlag() == true) {             //if current pointer is an operand
            postOrderTraversal(p->getLeft());   //get  operand value and continue postOrder traversal
            postOrderTraversal(p->getRight());
            cout << p->getValue() << " ";
        }
        else if (p->getFlag() == false) {       //if current pointer is an operator
            postOrderTraversal(p->getLeft());   //get operator value and continue postOrder traversal
            postOrderTraversal(p->getRight());
            cout << p->getOperator() << " ";
        }
    }
}
//Display tree preOrder
void preOrderTraversal(treeNodePtr p) {
    if (p != NULL) {
        if (p->getFlag() == true) {
            cout << p->getValue() << " ";       //if current pointer is an operand
            preOrderTraversal(p->getLeft());    //get  operand value and continue preOrder traversal
            preOrderTraversal(p->getRight());
        }
        else if (p->getFlag() == false) {       //if current pointer is an operator
            cout << p->getOperator() << " ";    //get operator value and continue preOrder traversal
            preOrderTraversal(p->getLeft());
            preOrderTraversal(p->getRight());
        }
    }
}

//Function that evaluates the math for our expression tree
double eval(treeNodePtr p) {
    if (p->getFlag() == true)
        return p->getValue();

    double leftVal = eval(p->getLeft());
    double RightVal = eval(p->getRight());

    if (p->getFlag() == false) {
        if (p->getOperator() == '+')
            return leftVal + RightVal;
        else if (p->getOperator() == '-')
            return leftVal - RightVal;
        else if (p->getOperator() == '*')
            return leftVal * RightVal;
        else if (p->getOperator() == '/')
            return leftVal / RightVal;
    }

}



int main() {

    ifstream inFile;
    char str[100];          //holds one arithmetic expression at a time
    int i, j;           //variables for our loops
    string numStr;          //save operands while still in string
    double operand;         //save operands when changed into double
    char p;            //for getting operators from operator stack
    stack<char> opStack;            //Stack for operators
    stack<treeNodePtr> treeStack;           //Stack for pointers
    treeNodePtr tmpNode, left_ch, right_ch;         //Declaring new pointers
    bool tag;           //Tag is to check if operand/value or not
    bool error = false;         //boolean to check for errors in expressions
    inFile.open("Arithmetic_Expressions.txt");              //open file of arithmetic expressions

    i = 0;
    while (!inFile.eof())
    {
        i++;
        inFile.getline(str, 100);

            cout << "See the input expression: " << str << endl;
            //empty all the stacks
            while (!opStack.empty())
                opStack.pop();
            while (!treeStack.empty())
                treeStack.pop();
            tag = true;




            //go through each item in str and save them in the operator stack (opStack) or operand stack (treeStack)
            for (j = 0; j < strlen(str); j++) {

                //case 1: if operand, extract value, create tree node, & push node onto treeStack
                if (isdigit(str[j]) || str[j] == '.') {
                    numStr = "";
                    //Add all digits into numStr
                    while (isdigit(str[j]) || str[j] == '.') {
                        numStr += str[j];
                        j++;
                    }
                    j--;
                    //convert string to double
                    operand = stod(numStr);
                    //create a tree node and save/push it onto treeStack
                    tmpNode = new treeNode(true, operand, '#', NULL, NULL);
                    treeStack.push(tmpNode);
                }


                //case 2: if ( push to top of opStack
                else if (str[j] == '(') {
                    opStack.push(str[j]);
                }


                //case 3: if + or -
                else if (str[j] == '+' || str[j] == '-') {
                    if (opStack.empty() || opStack.top() == '(') {
                        opStack.push(str[j]);
                    }
                    else if (opStack.top() == '+' || opStack.top() == '-' || opStack.top() == '*' || opStack.top() == '/') {
                        //make current operator at the top of opStack into a new node with top 2 nodes in treeStack as children
                        p = opStack.top();
                        opStack.pop();
                        right_ch = treeStack.top();
                        treeStack.pop();
                        left_ch = treeStack.top();
                        treeStack.pop();
                        tmpNode = new treeNode(false, NULL, p, left_ch, right_ch);
                        treeStack.push(tmpNode);    //Save new node into treeStack                    
                        opStack.push(str[j]);   //save the new operator in opStack
                    }
                }


                //case 4: if * or /
                else if (str[j] == '*' || str[j] == '/') {
                    if (opStack.empty() || opStack.top() == '(' || opStack.top() == '+' || opStack.top() == '-') {
                        opStack.push(str[j]);
                    }
                    else if (opStack.top() == '*' || opStack.top() == '/') {
                        //make current operator at the top of opStack into a new node with top 2 nodes in treeStack as children
                        p = opStack.top();
                        opStack.pop();
                        right_ch = treeStack.top();
                        treeStack.pop();
                        left_ch = treeStack.top();
                        treeStack.pop();
                        tmpNode = new treeNode(false, NULL, p, left_ch, right_ch);
                        treeStack.push(tmpNode);    //Save new node into treeStack
                        opStack.push(str[j]);   //save the new operator in opStack
                    }
                }


                //case 5: if ) take out all operators until reaching (
                else if (str[j] == ')') {
                    //if there exists an open parenthesis in opStack, untill reaching it, remove all operators in-between and make them into nodes in treeStack
                    while ((opStack.top() != '(') && (open_Parenthesis(opStack) == true)) {
                        //Make each operator into a node with top 2 nodes in treeStack as children
                        p = opStack.top();
                        opStack.pop();
                        right_ch = treeStack.top();
                        treeStack.pop();
                        left_ch = treeStack.top();
                        treeStack.pop();
                        tmpNode = new treeNode(false, NULL, p, left_ch, right_ch);
                        treeStack.push(tmpNode);                               //Save new node into treeStack
                    }

                    //remove the matching open parenthesis, otherwise detect an error
                    if (opStack.top() == '(')
                        opStack.pop();
                    else
                    {
                        cout << "Error! Missing an opening parenthesis!" << endl;
                        error = true;
                    }

                }
            }


            //take out all legal and remaining operators from opStack
            while (opStack.size() > 0 && treeStack.size() > 1 && error == false) {
                //for every legal operator, remove from opStack, make into treeNode with children (top 2 nodes from treeStack), and add new node to treeStack
                p = opStack.top();
                opStack.pop();
                right_ch = treeStack.top();
                treeStack.pop();
                left_ch = treeStack.top();
                treeStack.pop();
                tmpNode = new treeNode(false, NULL, p, left_ch, right_ch);
                treeStack.push(tmpNode);
            }



            //Display solutions and errors
            if (treeStack.size() > 1 || opStack.size() > 0 || error == true)
                cout << "Sorry, there was an error in your " << i << " arithmetic expression" << endl;
            else
            {
                cout << "Your " << i << " arithmetic expression has no sintax errors" << endl;
                cout << "Displayed are the 3 traversals of your tree: " << endl;
                cout << "InOrder Traversal:  ";
                inOrderTraversal(treeStack.top());
                cout << endl << "PostOrder Traversal:  ";
                postOrderTraversal(treeStack.top());
                cout << endl << "PreOrder Traversal:  ";
                preOrderTraversal(treeStack.top());
                cout << endl << "The value of the " << i << " expression evaluates to: ";
                double evaluation = eval(treeStack.top());
                cout << evaluation << endl;
            }

            if (opStack.size() > 0)
                cout << "There are leftover operators in opStack " << endl;
            else
                cout << "There are no operators left in opStack" << endl;

            if (treeStack.size() > 1)
                cout << "There are more than 1 things in treeStack " << endl;
            else
                cout << "There is just 1 thing in treeStack" << endl;

            cout << "This is the end of the " << i << " expression. \n" << endl << endl;
    }

    return 0;
}

