#pragma once

class Light
{
public:
	virtual Vector3 GetPosition() const = 0;
	virtual Vector3 GetColor() const = 0;
	virtual void Debug(std::string ID) {}
	
	float GetIntensity() { return m_intensity; }

protected:
	float m_intensity;
	Vector3 m_color;
};