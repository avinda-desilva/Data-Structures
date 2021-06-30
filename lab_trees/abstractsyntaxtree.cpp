#include "abstractsyntaxtree.h"

/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
    return eval(root);
}

double AbstractSyntaxTree::eval(Node* subRoot) const {

    double rightTreeValue = 0;
    double leftTreeValue = 0;
    double total = 0.0;

    if (subRoot == NULL) {
      return 0.0;
    }
    if (subRoot->right == NULL && subRoot->left == NULL) {
      return std::stoi(subRoot->elem);
    }

    leftTreeValue = eval(subRoot->left);
    rightTreeValue = eval(subRoot->right);


    if (subRoot->elem == "*") {
      total = leftTreeValue * rightTreeValue;
    }
    if (subRoot->elem == "/") {
      total =  leftTreeValue / rightTreeValue;
    }
    if (subRoot->elem == "+") {
      total =  leftTreeValue + rightTreeValue;
    }
    if (subRoot->elem == "-") {
      total =  leftTreeValue - rightTreeValue;
    }

    return total;

}
