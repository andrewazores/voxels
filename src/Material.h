#ifndef MATERIAL_H
#define MATERIAL_H

class Material {
public:
	Material(void);
	Material(float, float, float, float);
	~Material(void);
	void setR(float);
	void setG(float);
	void setB(float);
	void setA(float);
	float getR(void);
	float getG(void);
	float getB(void);
	float getA(void);
private:
	float _r, _g, _b, _a;
};

#endif