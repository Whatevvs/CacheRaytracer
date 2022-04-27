#include "Precomp.h"
#include "PointLight.h"

PointLight::PointLight(Vector3 position, Vector3 color, float intensity) : m_position(position)
{ 
    m_color = color; 
    m_intensity = intensity;
}

Vector3 PointLight::GetPosition() const
{
    return m_position;
}

Vector3 PointLight::GetColor() const
{
    return m_color;
}

void PointLight::Debug(std::string ID)
{
    ImguiHandler* imgui = ImguiHandler::GetInstance();
    imgui->CreateWindow("Debug: Lighting");
    imgui->ActivateWindow("Debug: Lighting");
    imgui->SliderFloat(ID + " Intensity", m_intensity, 0.0f, 25.0f);
    imgui->SliderVector3(ID + " Position", m_position, -10.0f, 10.0f);
    imgui->DisableWindow();
}