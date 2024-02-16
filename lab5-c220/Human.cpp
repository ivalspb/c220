#include "Human.h"

void Human::printParents()
{
	if(m_father)
	{
		std::cout << (*m_father).m_name << "\t";
		(*m_father).printParents();
	}
	if(m_mother)
	{
		std::cout << (*m_mother).m_name << "\n";
		(*m_mother).printParents();
	}
}

void Human::printChilds()
{
	std::cout << m_name << " ";
	if (!m_childs.empty())
		for (const auto& i : m_childs) i.lock().get()->printChilds();
	std::cout << "\n";
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
		for (const auto& i : m_childs) i.lock().get()->printChilds();
	std::cout << "\nParents:\n";
	this->printParents();
	
}
