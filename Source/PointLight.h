#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(Vector3 position, Vector3 color, float intensity = 1.0f);

	virtual Vector3 GetPosition() const override;
	virtual Vector3 GetColor() const override;
	virtual void Debug(std::string ID) override;

	Vector3 m_position;
};