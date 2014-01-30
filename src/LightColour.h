#ifndef LIGHTCOLOUR_H
#define LIGHTCOLOUR_H

class LightColour {
public:
	LightColour(void);
	LightColour(float, float, float, float);
	LightColour(const LightColour&);
	~LightColour();
	void setRedChannel(float);
	void setGreenChannel(float);
	void setBlueChannel(float);
	void setAlphaChannel(float);
	void setColour(float, float, float, float);
	float getRedChannel(void);
	float getGreenChannel(void);
	float getBlueChannel(void);
	float getAlphaChannel(void);
private:
	float _red, _green, _blue, _alpha;
};

#endif