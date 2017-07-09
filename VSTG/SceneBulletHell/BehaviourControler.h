#pragma once

#include "GameObject.h"
#include <Methods.h>
#include <SFML/System.hpp>
#include <assert.h>

struct BinTree {
	enum ReturnType : int {
		TREE_GOTO_LEFT,
		TREE_GOTO_RIGHT,
		TREE_GOTO_PARENT,
		TREE_STAY
	};
	struct Node {
		int id;
		Node *parent;
		Node *left;
		Node *right;
		ReturnType (*func)(GameObject* const pObj);
	};

	Node *head;
	int count;
};

void ClearNode(BinTree::Node *node) {
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

BinTree *CreateTree(BinTree::ReturnType (*func)(GameObject* const pObj)) {
	BinTree *tree = (BinTree*)calloc(1, sizeof(BinTree));
	tree->head = (BinTree::Node*)calloc(1, sizeof(BinTree::Node));
	tree->head->func = func;
	return tree;
}

void ClearTree(BinTree *bTree) {
	BinTree::Node *node = bTree->head;
	ClearNode(node);
	delete node;
	bTree = nullptr;
}

BinTree::ReturnType ctrlVelocity(GameObject* const pObj) {
	const sf::Vector2f pos = pObj->getPosition();
	sf::Vector2f ctrl = { 0.f,0.f };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		ctrl.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		ctrl.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		ctrl.y += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		ctrl.y -= 1.f;
	ctrl = CommResMeth::normalize(ctrl);
	const sf::Vector2f newPos = pos + ctrl * 1.f;
	pObj->setPosition(newPos);

	return BinTree::ReturnType::TREE_STAY;
}

class BehaviourControler : public virtual GameObject {
public:
	BehaviourControler() :
		GameObject(nullptr, sf::Vector2f(),CommResMeth::Angle(),"")
	{
	}
public:
	void updateBehaviour(const float dt){
		BinTree::ReturnType rc = curNode->func(this);
		switch (rc) {
		case BinTree::ReturnType::TREE_GOTO_LEFT:
			if (curNode->left)
				curNode = curNode->left;
			break;
		case BinTree::ReturnType::TREE_GOTO_RIGHT:
			if (curNode->right)
				curNode = curNode->right;
			break;
		case BinTree::ReturnType::TREE_GOTO_PARENT:
			if (curNode->parent)
				curNode = curNode->parent;
			break;
		case BinTree::ReturnType::TREE_STAY:
		default:
			break;
		}
	}
protected:
	BinTree::Node *curNode;
};

BinTree *t1 = CreateTree(&ctrlVelocity);
