#pragma once
class CFieldOfArea
{
public:
	bool m_isOccupied;
	float m_topY;
	float m_bottomY;
	float m_leftX;
	float m_rightX;

	CFieldOfArea(float _topY, float _bottomY, float _leftX, float _rightX);
	~CFieldOfArea();
};

