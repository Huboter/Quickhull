#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point();
	Point(float x, float y);
	~Point();

	void setValues(float x, float y);
	void setValues(Point& point);
	bool hasSameValues(float x, float y) const;
	bool hasSameValues(const Point& point) const;

	void print() const;

	float xPosition;
	float yPosition;

private:

}; 

#endif
