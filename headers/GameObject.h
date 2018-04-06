#pragma once
// std libs
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class GameObject
{
public:
	void add(GameComponent* new_component);
	GameComponent* remove(string component_name);
	GameComponent* get(string component_name);

private:
	static int count;
	glm::mat4 model_matrix;
	unordered_map<string, GameComponent> components;
	vector<LoopingComponent> updateList;
};