
#include <iostream>
#include <memory>
#include <vector>
#include <lars/generator.h>

using namespace std;
using namespace lars;

// Define Node data type and output methods

struct Node{
  using Shared = shared_ptr<Node>;
  vector<Shared> children;
  string name;
  Node(string _name):name(_name){}
};

ostream &operator<<(ostream &stream,Node::Shared &node){
  stream << node->name;
  if(node->children.size() != 0){
    stream << '[';
    for(auto c:node->children) stream << c << (c != node->children.back() ? "," : "");
    stream << ']';
  }
  return stream;
}

// Use Yields to define traversal functions

namespace{ // Traversal helper functions
  void postorder_yield(Node::Shared node,Yield<Node::Shared>& yield){
    for(auto &c:node->children) postorder_yield(c, yield);
    yield(node);
  }

  void preorder_yield(Node::Shared node,Yield<Node::Shared>& yield){
    yield(node);
    for(auto &c:node->children) postorder_yield(c, yield);
  }
}

Generator<Node::Shared> postorder_traversal(Node::Shared node){
  return Generator<Node::Shared>([=](Yield<Node::Shared> &yield){ postorder_yield(node, yield); });
}

Generator<Node::Shared> preorder_traversal(Node::Shared node){
  return Generator<Node::Shared>([=](Yield<Node::Shared> &yield){ preorder_yield(node, yield); });
}

// Create a tree and traverse on it

int main(){
  Node::Shared a = make_shared<Node>("a");
  Node::Shared b = make_shared<Node>("b");
  Node::Shared c = make_shared<Node>("c");
  Node::Shared d = make_shared<Node>("d");
  Node::Shared e = make_shared<Node>("e");
  Node::Shared f = make_shared<Node>("f");
  
  a->children.push_back(b);
  a->children.push_back(c);
  b->children.push_back(d);
  c->children.push_back(e);
  c->children.push_back(f);
  
  cout << "tree: " << a << std::endl;
  
  cout << "postorder traversal: ";
  for(auto n:postorder_traversal(a)) cout << n->name << ' ';
  cout << '\n' << "preorder traversal: ";
  for(auto n:preorder_traversal(a)) cout << n->name << ' ';
  cout << endl;
}

