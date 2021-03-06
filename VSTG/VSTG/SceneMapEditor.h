#pragma once

#include <set>
#include <chrono>
#include <thread>

#include "Scene.hpp"
#include "Essential.hpp"
#include "GameObject.hpp"
#include "ObjMenu.h"
#include "ObjEnemy.hpp"

struct YCmp {
	bool operator()(const std::shared_ptr<GameObject> lhs, const std::shared_ptr<GameObject> rhs) const {
		if (lhs->getPosition().y * 10000 + lhs->getPosition().x > rhs->getPosition().y * 10000 + rhs->getPosition().x) {
			return true;
		}
		return false;
	}
};

class SceneMapEditor : public Scene {
private:
	class Data {
	private:
		float sponsTime;
		sf::Vector2f initPos;
		char objectID[128];
		size_t hasdID;
		int numPaths;
		sf::Vector2i followPaths[16];
	};
public:
	SceneMapEditor();
	Essential::GameState Run();
	void DrawScene();
	bool MergeFromFile(const std::string filepath);
	bool MergeFromFile();
	bool WriteToFile(const std::string filepath);
	bool WriteToFile();
private:
	bool isExit;
	bool isDrag;
	bool isMouseLeft;
	bool isFocused;
	bool isMenuTriger;
	float timeAtBottom;
	float timeScale;
//	float spriteScale;
	static constexpr float scrollSpeed = 30.0f;
	static constexpr float eraseSize= 20.0f;
//	static constexpr float brushSize = 5.0f;
	std::vector<Data> vdata;
	std::set<std::shared_ptr<ObjCharacter>, YCmp> sortedpObject;
	std::list<std::shared_ptr<ObjCharacter>> lObjectDel;
	std::shared_ptr<sf::Texture> pTexBuffer;
	std::shared_ptr<ObjCharacter> objectBrush;
	sf::CircleShape objectEraser;
	std::shared_ptr<ObjCharacter> dragObject;
	ObjMenu escMenu;
	sf::RectangleShape paintboard;
	int typeIdx;
private: // Menu Context
	Button butPrev;
	Button butNext;
	Button butMerge;
	Button butWrite;
	Button butClear;
	Button butExit;
	static constexpr float previewXPos = 580.0f;
	static constexpr float previewYPos = 80.0f;
	std::shared_ptr<GameObject> spritePreview;
	sf::Text textPreview;
	sf::Text textPos;
	sf::Text textTime;
private:
	void Update();
	void DrawLine(sf::RenderTarget & gfx, const float y);
	inline float time2dim(const float & dim) const;
	inline float dim2time(const float & time) const;
	inline sf::Vector2f offsetToCanvas(const sf::Vector2f & vec) const;
	inline sf::Vector2f offsetOutCanvas(const sf::Vector2f & vec) const;
	inline bool inPaintboard(const sf::Vector2f& pos) const;
	inline void objScrollLeft();
	inline void objeScrollRight();
};