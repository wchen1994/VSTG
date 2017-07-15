#include "BehaviourController.h"

std::map<std::string, BinTree*> BehaviourController::m_mapTree;

BinTree::Node * BinTree::CreateNode(int(*func)(GameObject * const pObj, const float dt))
{
	Node *node = (Node*)calloc(1, sizeof(Node));
	node->func = func;
	return node;
}

void BinTree::ClearNode(Node * node)
{
	if (node->left) {
		if (!node->left->left && !node->left->right) {
			delete node->left;
		}
		else {
			ClearNode(node->left);
		}
	}
	else if (node->right){
		if (!node->left->left && !node->left->right) {
			delete node->left;
		}
		else {
			ClearNode(node->left);
		}
	}
}

BinTree * BinTree::CreateTree(std::ifstream & file_in)
{
	std::string line;
	while (file_in >> line) {
		// read the line and push function name into the queue 
		// Identifier NULL for nullptr (*func)()
	}
	return nullptr;
}

BinTree * BinTree::CreateTree(int(*func)(GameObject * const pObj, const float dt))
{
	BinTree *tree = (BinTree*)calloc(1, sizeof(BinTree));
	tree->head = CreateNode(func);
	return tree;
}

void BinTree::ClearTree(BinTree * bTree)
{
	Node *node = bTree->head;
	ClearNode(node);
	delete node;
	bTree = nullptr;
}

BehaviourController::BehaviourController(BinTree * tree) :
	GameObject(nullptr, sf::Vector2f(),CommResMeth::Angle(),""),
	tree(tree)
{
	if (tree)
		curNode = tree->head;
	else
		curNode = nullptr;
}

void BehaviourController::updateBehaviour(const float dt)
{
	int rc;
	if ( (curNode != nullptr) && (rc = curNode->func(this, dt)) ) { 
		switch (rc) {
		case TREE_GOTO_LEFT:
			curNode = curNode->left;
			break;
		case TREE_GOTO_RIGHT:
			curNode = curNode->right;
			break;
		case TREE_GOTO_PARENT:
			curNode = curNode->parent;
			break;
		case TREE_GOTO_HEAD:
			curNode = tree->head;
			break;
		case TREE_STAY:
		default:
			break;
		}
	}
}

const BinTree * BehaviourController::getTree(const std::string treeName)
{
	auto it = m_mapTree.find(treeName);
	if (it == m_mapTree.end()) {
		return nullptr;
	}
	else {
		return it->second;
	}
}
