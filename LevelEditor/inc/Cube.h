#ifndef _CUBE_H_
#define	_CUBE_H_

#include "glm.hpp"

class Cube
{
public:
	Cube(glm::vec2 _pos);
	~Cube();

	void Update(double _dt);
	void Draw();

	bool ComparePos(glm::vec2 _pos) { return _pos == m_position; }
protected:
private:
	glm::vec2 m_position;
	glm::vec4 m_colour;
};

#endif