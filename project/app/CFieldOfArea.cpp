#include "CFieldOfArea.h"

CFieldOfArea::CFieldOfArea(float _topY, float _bottomY, float _leftX, float _rightX)
	: m_isOccupied(false)
	, m_topY(_topY)
	, m_bottomY(_bottomY)
	, m_leftX(_leftX)
	, m_rightX(_rightX)
{
}

CFieldOfArea::~CFieldOfArea()
{
}
