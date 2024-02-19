#include "Human.h"

void Human::printParents(size_t space)
{
	size_t count = m_name.size();
	space += count;
	if(m_father)
	{
		(*m_father).printParents(space);
	}
	for (size_t i = count; i < space; ++i) std::cout << " ";
	std::cout << m_name << std::endl;
	if(m_mother)
	{
		(*m_mother).printParents(space);
	}
}

void Human::printChilds(size_t space)
{
	size_t count = m_name.size();
	space += count;
	for (size_t i = count; i < space; ++i) std::cout << " ";
	std::cout << m_name << std::endl;
	if (!m_childs.empty())
		for (const auto& i : m_childs) i.lock().get()->printChilds(space);
	//std::cout << "\n";
}

std::shared_ptr<Human> Human::child(std::shared_ptr<Human> mother, std::shared_ptr<Human> father, const std::string& name)
{
	std::vector<std::weak_ptr<Human>> childfree{};
	std::shared_ptr<Human> newborn (new Human(name, true, mother, father, childfree));
	mother->m_childs.push_back(newborn);
	if (father) father->m_childs.push_back(newborn);
	return newborn;
}

void Human::printGenTree()
{
	std::cout << "\nGenialogy tree of "<<m_name;
	std::cout << "\nChilds:\n";
	if (!m_childs.empty())
		this->printChilds();
		//for (const auto& i : m_childs) i.lock().get()->printChilds();
	else
		std::cout << "No childs yet";
	std::cout << "\nParents:\n";
	this->printParents();
	
}
