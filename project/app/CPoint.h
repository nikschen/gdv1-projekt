#pragma once

/*
* Resembles 2D Point to track x and y values of middlepoints of the tetrominos single square parts
*/
class CPoint
{
public:
	CPoint();
	CPoint(float _x, float _y);
	~CPoint();

	float m_x;
	float m_y;
};

