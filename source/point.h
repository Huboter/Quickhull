#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point();
	Point(float x, float y);
	~Point();

	void setValues(float x, float y);
	void setValues(Point& point);

	void print();

	float xPosition;
	float yPosition;

private:

}; 

#endif
