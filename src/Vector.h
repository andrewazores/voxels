#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
	Vector(const Vector&);
	Vector(float, float, float);
	Vector();
	~Vector();
	Vector operator+(Vector);
	Vector operator-(Vector);
	Vector operator*(const Vector);
	Vector operator*(float);
	Vector operator/(float);
	bool operator==(Vector);
	bool operator!=(Vector);
	void setX(float);
	void setY(float);
	void setZ(float);
	float getX();
	float getY();
	float getZ();
	float getMagnitude();
	void normalize();
	float dot(Vector);

private:
	float _x, _y, _z;
};

#endif