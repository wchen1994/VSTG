#pragma once

#include "GameObject.h"
#include <Methods.h>
#include <assert.h>
#include <fstream>
#include <map>

#define		TREE_EXIT			0
#define		TREE_GOTO_LEFT		1
#define		TREE_GOTO_RIGHT		2
#define		TREE_GOTO_PARENT	3
#define		TREE_GOTO_HEAD		4
#define		TREE_STAY			5

class BinTree {
public:
	struct Node {
		int id;
		Node *parent;
		Node *left;
		Node *right;
		int (*func)(GameObject* const pObj, const float dt);
	};

	Node *head;
	int count;

	static Node *CreateNode(int(*func)(GameObject* const pObj, const float dt)); 

	static void ClearNode(Node *node);

	static BinTree *CreateTree(std::ifstream & file_in); 

	static BinTree *CreateTree(int(*func)(GameObject* const pObj, const float dt));

	static void ClearTree(BinTree *bTree);

};

class BehaviourController : public virtual GameObject {
public:
	BehaviourController(BinTree* tree);

	void updateBehaviour(const float dt);

	static const BinTree *getTree(const std::string treeName);

private:
	BinTree *tree;
	BinTree::Node *curNode;
	static std::map<std::string, BinTree*> m_mapTree;
};
