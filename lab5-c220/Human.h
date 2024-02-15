#pragma once
#include <string>
#include <memory>
#include <vector>

class Human
{
	std::string m_name;
	bool alive=true;
	std::shared_ptr<Human> m_mother;
	std::shared_ptr<Human> m_father;
	std::vector<std::weak_ptr<Human>> m_childs;
public:
	Human() = default;
	Human(const std::string& name, bool alive, std::shared_ptr<Human> mother, std::shared_ptr<Human> father, std::vector<std::weak_ptr<Human>>& childs) :
		m_name(name), alive(alive), m_mother(mother), m_father(father), m_childs(childs) {}
	//Human(std::string& name):m_name(name){}
	Human(const char* name) :m_name(name) {}
	Human(const Human& other) = delete;
	Human& operator=(const Human& other) = delete;
	Human(Human&& other) = delete;
	Human& operator=(Human&& other) = delete;
	static std::shared_ptr<Human> child(std::shared_ptr<Human> mother, std::shared_ptr<Human> father = nullptr, const std::string& name="noname");
	void make_dead() { alive = false; }
};

