#include "Human.h"

Human& Human::child(std::shared_ptr<Human> mother, std::shared_ptr<Human> father, const std::string& name)
{
	std::vector<std::weak_ptr<Human>> childfree{};
	Human newborn (name, true, mother, father, childfree);
	mother->m_childs.push_back(std::make_shared<Human>(newborn));
	if (father) father->m_childs.push_back(std::make_shared<Human>(newborn));
	return newborn;
}
