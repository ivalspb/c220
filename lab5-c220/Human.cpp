#include "Human.h"

void Human::child(std::shared_ptr<Human> mother, std::shared_ptr<Human> father, std::string& name)
{
	std::vector<std::weak_ptr<Human>> childfree{};
	Human newborn (name, true, mother, father, childfree);
	mother->m_childs.push_back(std::make_shared<Human>(newborn));
}
