#ifndef Create_TREE
#define Create_TREE

#include <iostream>
#include <cassert>
using namespace std;



class AbstractNode {      
	public:
        AbstractNode * parent = 0;
		virtual double eval() = 0;
		AbstractNode() {};
		virtual ~AbstractNode() {};
		virtual string WhichNode() = 0;
};

class AbstractLeafNode : public AbstractNode{

};
class PlaceholderNode : public AbstractLeafNode {
    public:
        virtual double eval() {assert(0); return 0.0;};
		string WhichNode() {
			return "PlaceHolder";
		}
};
class LeafNode : public AbstractLeafNode {
	private:
		double value;
	public:
		LeafNode(double d) : value(d) {};
		~LeafNode() {};
		double eval() {return value;};
		string WhichNode(){
			return "LeafNode";
		}
};
class UnaryAbstractNode : public AbstractNode {
    public:
       AbstractNode * child;
};
class ParentheisNode : public UnaryAbstractNode {
    public:
        ParentheisNode(AbstractNode * c) {
            child = c;
            child->parent = this;
        };
        ~ParentheisNode() { delete child;};
        virtual double eval() {return (child->eval());};
		string WhichNode(){
			return "Param";
		}

};
class UnaryMinusNode : public UnaryAbstractNode {
	public:
		UnaryMinusNode(AbstractNode * c) {
            child = c;
            child->parent = this;
        };
		~UnaryMinusNode() {delete child;};
		double eval() {return ((-1.0)*child->eval());};
		string WhichNode(){
			return "Minus";
		}
};
class BinaryNode : public AbstractNode {
	private:
		AbstractNode * left;
		AbstractNode * right;
		char op;
	public:
        int precedence;
		BinaryNode(AbstractNode * l,AbstractNode * r,char o) : left(l), right(r), op(o) {
            left->parent = this;
            right->parent = this;
            precedence = getPrecendence();
        };
		string WhichNode(){
			return "Binary";
		}
		~BinaryNode() {delete left; delete right;};
		virtual double eval() {
			switch(op) {
				case '+':
					return left->eval()+right->eval();
				case '-':
					return left->eval()-right->eval();
				case '*':
					return left->eval()*right->eval();
				case '/':
					return left->eval()/right->eval();
				default:
					return 0;
			};
        };
		char getOperator(){
			return op;
		}
		AbstractNode * getLeft(){
			return left;
		};
		AbstractNode * getRight(){
			return right;
		};
        void printLeft(){
            cout<<left->eval();
        };
        void printRight(){
            cout<<right->eval();
        };
		void printOperator(){
			cout<<op<<endl;
		}
		void ChangeRight(AbstractNode * m) {
			right = m;
		}
		void ChangeOperator(char c){
			op = c;
		}
		void ChangeLeft(AbstractNode * m) {
			left = m;
		}
        int getPrecendence(){
            switch(op){
                case '(': return 0;
		        case ')': return 0;
		        case '^': return 3;
		        case '*': return 2;
		        case '/': return 2;
                case '%': return 2;
                case '+': return 1;
                case '-': return 1;
                case '#': return 9;
                default: return 0;
            }
        }

};

#endif