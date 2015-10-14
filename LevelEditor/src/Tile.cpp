#include "Tile.h"
#include "aieutilities\Gizmos.h"

Tile::Tile(glm::vec2 _pos)
{
	m_position = _pos;
	m_lines[0] = glm::vec3(0.05f + _pos.x, 0, 0.05f + _pos.y);
	m_lines[1] = glm::vec3(0.05f + _pos.x, 0, 0.95f + _pos.y);
	m_lines[2] = glm::vec3(0.95f + _pos.x, 0, 0.05f + _pos.y);
	m_lines[3] = glm::vec3(0.95f + _pos.x, 0, 0.95f + _pos.y);
	m_colour = glm::vec4(1);
	m_hover = false;
}
Tile::~Tile()
{

}
void Tile::Update(double _dt)
{
	m_colour.r = (m_hover) ? 1 : 0;
	m_colour.b = (m_hover) ? 1 : 0;

}
void Tile::Draw()
{
	Gizmos::addLine(m_lines[0], m_lines[1], m_colour);
	Gizmos::addLine(m_lines[0], m_lines[2], m_colour);
	Gizmos::addLine(m_lines[3], m_lines[1], m_colour);
	Gizmos::addLine(m_lines[3], m_lines[2], m_colour);
	if (m_hover)
	{
		Gizmos::addAABBFilled(glm::vec3(m_position.x + 0.5f, 0.5f, m_position.y + 0.5f), glm::vec3(0.45f, 0.5f, 0.45f), glm::vec4(0.3f));
	}

	m_hover = false;
}
void Tile::Hover()
{
	m_hover = true;
}