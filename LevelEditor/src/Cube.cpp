#include "Cube.h"
#include "aieutilities\Gizmos.h"

Cube::Cube(glm::vec2 _pos)
{
	m_position = _pos;
	m_colour = glm::vec4(0.5f, 0.5f, 0.5f, 1);
}
Cube::~Cube()
{

}
void Cube::Update(double _dt)
{

}
void Cube::Draw()
{
	Gizmos::addAABBFilled(glm::vec3(m_position.x + 0.5f, 0.5f, m_position.y + 0.5f), glm::vec3(0.45f, 0.5f, 0.45f), glm::vec4(m_colour));
}
