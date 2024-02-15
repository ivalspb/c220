#include "Human.h"

std::shared_ptr<Human> Human::child(std::shared_ptr<Human> mother, std::shared_ptr<Human> father, const std::string& name)
{
	std::vector<std::weak_ptr<Human>> childfree{};
	std::shared_ptr<Human> newborn (new Human(name, true, mother, father, childfree));
	mother->m_childs.push_back(newborn);
	if (father) father->m_childs.push_back(newborn);
	return newborn;
}
