#include <iostream>
#include "CreateTree.h"
#include "token.h"
#include "stackType.h"
// #include "queueType.h"
using namespace std;

int main() {
    Token t;
    stackType<AbstractNode*> treeNode;
    stackType<BinaryNode*> operatorNode;
    AbstractNode *tmp, *left,*right, *tmp2;
    AbstractNode * current = new PlaceholderNode();
    BinaryNode * op, *op1;
    ParentheisNode *param, *param1;
    cout << "enter a valid arithmetic expression on one line: ";
    cin >> t;
    while (t.Valid()){
        cout << t<<endl;
        if(t.IsOperand()){
            tmp = current->parent;
            current = new LeafNode(t.Operand());
            current->parent = tmp;
            treeNode.push(current);
            if(tmp != 0 && tmp->WhichNode() == "Binary"){
                right = treeNode.top();
                treeNode.pop();
                op1 = operatorNode.top();
                operatorNode.pop();
                op1->ChangeRight(right);
                current = op1->getRight();
                treeNode.push(op1);
                operatorNode.push(op1);
            }
        }
        if(t.IsOperator()){
            bool pushed = false;
            while(!pushed){
                if(operatorNode.isEmptyStack() == true){
                    tmp = current->parent;
                    left = current;
                    right = new PlaceholderNode();
                    op = new BinaryNode(left,right,t.Operator());
                    op->parent = tmp;
                    current = right;
                    operatorNode.push(op);
                    pushed = true;
                }
                else if (current->parent != 0 && current->parent->WhichNode() == "Param"){
                    tmp = current->parent;
                    left = treeNode.top();
                    treeNode.pop();
                    right = new PlaceholderNode();
                    op = new BinaryNode(left,right,t.Operator());
                    op1 = operatorNode.top();
                    op->parent = tmp;
                    tmp->parent = op1;
                    op1->ChangeRight(tmp);
                    operatorNode.push(op);
                    right->parent = op;
                    current = right;
                    pushed = true;
                }
                else if (t.Precedence() < operatorNode.top()->precedence){
                    tmp = current->parent;
                    left = current;
                    op1 = operatorNode.top();
                    operatorNode.pop();
                    right = new PlaceholderNode();
                    op = new BinaryNode(left,right,t.Operator());
                    op->ChangeLeft(op1);
                    current = right;
                    operatorNode.push(op);
                    pushed = true;
                }
                else{
                    op1 = operatorNode.top();
                    operatorNode.pop();
                    tmp = current->parent;
                    left = current;
                    if (op1->getOperator() == '-'){
                        left = new UnaryMinusNode(left);
                        left->parent = tmp;
                        op1->ChangeOperator('+');
                    }
                    right = new PlaceholderNode();
                    op = new BinaryNode(left,right,t.Operator());
                    op->parent = tmp;
                    op1->ChangeRight(op);
                    current = right;
                    operatorNode.push(op);
                    pushed = true;
                   
                }
            }
                
        }
        if(t.IsLeftParen()){
            tmp =current->parent;
            param = new ParentheisNode(current);
            param->parent = tmp;
        }
        if(t.IsRightParen()){
            tmp = current;
            while (tmp->parent->WhichNode() != "Param"){
                tmp = tmp->parent;
            }
                tmp2 = current->parent->parent;
                op = operatorNode.top();
                operatorNode.pop();
                op1 = operatorNode.top();
                operatorNode.pop();
                op1->ChangeRight(tmp);
                tmp->parent = op1;
        }
        cin >> t;
    }

    while (current->parent != 0){
        current = current->parent;
        //cout << current->eval()<<endl;
    }
    cout <<endl<<current->eval();
   
   return 0;
};