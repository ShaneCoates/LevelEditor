#ifndef _TILE_H_
#define	_TILE_H_

#include "glm.hpp"

class Tile
{
public:
	Tile(glm::vec2 _pos);
	~Tile();

	void Update(double _dt);
	void Draw();

	void Hover();
	bool ComparePos(glm::vec2 _pos) { return _pos == m_position; }
protected:
private:
	glm::vec3 m_lines[4];
	glm::vec2 m_position;
	glm::vec4 m_colour;
	bool m_hover;
};

#endif