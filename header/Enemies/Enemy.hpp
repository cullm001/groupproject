#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "../entity.hpp"
#include <string>
using namespace std;

class Enemy{
	protected:
		string name;
	public:
		int Move();
}; 
#endif
