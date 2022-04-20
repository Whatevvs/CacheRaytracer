#pragma once

// Based on: https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/simulating-sky/simulating-colors-of-the-sky
// Which references: 
//      - Display of The Earth Taking into Account Atmospheric Scattering, Nishita et al., Siggraph 1993.
//      - Display Method of the Sky Color Taking into Account Multiple Scattering, Nishita et al., Siggraph 1996.
//      - Precomputed Atmospheric Scattering, Eric Bruneton and Fabrice Neyret, Eurographics 2008.
//      - A Practical Analytic Model for Daylight, A. J. Preetham et al. Siggraph 1999.
//      - A Framework for the Experimental Comparison of Solar and Skydive Illumination, Joseph T. Kider Jr et al., Cornell University 2014.

class Atmosphere 
{ 
public: 

    // Defaults for earth
    Atmosphere( Vector3 sd = Vector3(0, 1, 0), 
        float gr = 6360e3, float ar = 6420e3, 
        float hr = 7994, float hm = 1200) : 
        m_sunDirection(sd), 
        m_groundRadius(gr), 
        m_atmosphereRadius(ar), 
        m_Hr(hr), 
        m_Hm(hm) 
    {} 
 
    Vector3 computeIncidentLight(const Vector3& orig, const Vector3& dir, float tmin, float tmax) const; 
 
    Vector3 m_sunDirection { Vector3(0, 1, 0) };     // The sun direction (normalized) 
    float m_groundRadius { 6360e3 };      // In the paper this is usually Rg or Re (radius ground, eart) 
    float m_atmosphereRadius { 6420e3 }; // In the paper this is usually R or Ra (radius atmosphere) 
    float m_Hr { 7994 };               // Thickness of the atmosphere if density was uniform (Hr) 
    float m_Hm { 1200 };               // Same as above but for Mie scattering (Hm) 
 
    const Vector3 betaR{3.8e-6f, 13.5e-6f, 33.1e-6f}; 
    const Vector3 betaM{21e-6f}; 
}; 

static Atmosphere atmosphere;  
 
inline bool solveQuadratic(float a, float b, float c, float& x1, float& x2) 
{ 
    if (b == 0) { 
        // Handle special case where the the two vector ray.dir and V are perpendicular
        // with V = ray.orig - sphere.centre
        if (a == 0) return false; 
        x1 = 0; x2 = std::sqrtf(-c / a); 
        return true; 
    } 
    float discr = b * b - 4 * a * c; 
 
    if (discr < 0) return false; 
 
    float q = (b < 0.f) ? -0.5f * (b - std::sqrtf(discr)) : -0.5f * (b + std::sqrtf(discr)); 
    x1 = q / a; 
    x2 = c / q; 
 
    return true; 
} 

inline bool raySphereIntersect(const Vector3& orig, const Vector3& dir, const float& radius, float& t0, float& t1) 
{ 
    // They ray dir is normalized so A = 1 
    float A = dir.x * dir.x + dir.y * dir.y + dir.z * dir.z; 
    float B = 2 * (dir.x * orig.x + dir.y * orig.y + dir.z * orig.z); 
    float C = orig.x * orig.x + orig.y * orig.y + orig.z * orig.z - radius * radius; 
 
    if (!solveQuadratic(A, B, C, t0, t1)) return false; 
 
    if (t0 > t1) std::swap(t0, t1); 
 
    return true; 
} 

inline float raySphereIntersectNew(const Vector3& orig, const Vector3& dir, float tMin, float tMax) 
{ 
    Vector3 m_position {0,0,0}; // Planet position

    Vector3 oc = orig - m_position;
	float a = dir.SqrLength();
	float half_b = Dot(oc, dir);
	float c = oc.SqrLength() - (atmosphere.m_groundRadius * atmosphere.m_groundRadius);

	float discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	float sqrtd = sqrtf(discriminant);

	// Find the nearest root that lies in the acceptable range.
	float root = (-half_b - sqrtd) / a;
	if (root < tMin || tMax < root)
	{
		root = (-half_b + sqrtd) / a;

		if (root < tMin || tMax < root)
			return -1.0f;
	}

	return root;
} 

static float g = 0.76f; 
static float gg = g * g;
static float phaseRBase = 3.0f / (16.0f * PI);
static float phaseMBase = 3.0f / (8.0f * PI);
static uint32_t numSamples = 8; // 16
static uint32_t numSamplesLight = 8; // 8 
static int width = 1280;
static int height = 720;

inline Vector3 Atmosphere::computeIncidentLight(const Vector3& orig, const Vector3& dir, float tmin, float tmax) const 
{ 

    float t0, t1; 
    if (!raySphereIntersect(orig, dir,atmosphere.m_atmosphereRadius,  t0, t1) || t1 < 0) 
        return 0; 

    if (t0 > tmin && t0 > 0) tmin = t0; 
    if (t1 < tmax) tmax = t1; 

    float segmentLength = (tmax - tmin) / numSamples; 
    float tCurrent = tmin; 

    Vector3 sumR(0); // rayleigh contribution 
    Vector3 sumM(0); // mie contribution 

    float opticalDepthR = 0;
    float opticalDepthM = 0; 

    // (mu in the paper)
    // Dot between the sun direction and the ray direction 
    float mu = Dot(dir, m_sunDirection); 
    float mumuA = mu * mu + 1;

    float phaseR = phaseRBase * mumuA; 
    float phaseM = phaseMBase * ((1.0f - g) * mumuA) / ((2.0f + gg) * pow((1.0f + gg) - (2.0f * g * mu), 1.5f));
        
    for (uint32_t i = 0; i < numSamples; ++i) 
    { 
        Vector3 samplePosition = orig + dir * (tCurrent + segmentLength * 0.5f); 
        float height = samplePosition.Length() - m_groundRadius; 

        // compute optical depth for light
        float hr = exp(-height / m_Hr) * segmentLength; 
        float hm = exp(-height / m_Hm) * segmentLength;

        opticalDepthR += hr; 
        opticalDepthM += hm; 

        // light optical depth
        float t0Light {0};
        float t1Light {0}; 
        raySphereIntersect(samplePosition, m_sunDirection, m_atmosphereRadius, t0Light, t1Light); 

        float segmentLengthLight = t1Light / numSamplesLight, tCurrentLight = 0; 
        float opticalDepthLightR = 0;
        float opticalDepthLightM = 0; 
        uint32_t j; 
        for (j = 0; j < numSamplesLight - i; ++j) 
        { 
            Vector3 samplePositionLight = samplePosition + m_sunDirection * (tCurrentLight + segmentLengthLight * 0.5f); 
            float heightLight = samplePositionLight.Length() - m_groundRadius; 
            if (heightLight < 0) break; 
            opticalDepthLightR += exp(-heightLight / m_Hr) * segmentLengthLight; 
            opticalDepthLightM += exp(-heightLight / m_Hm) * segmentLengthLight; 
            tCurrentLight += segmentLengthLight; 
        } 
        if (j == numSamplesLight - i) 
        { 
            Vector3 tau = betaR * (opticalDepthR + opticalDepthLightR) + betaM * 1.1f * (opticalDepthM + opticalDepthLightM); 
            Vector3 attenuation(exp(-tau.x), exp(-tau.y), exp(-tau.z)); 

            sumR += attenuation * hr; 
            sumM += attenuation * hm; 
        } 
        tCurrent += segmentLength; 
    } 

    return (sumR * betaR * phaseR + sumM * betaM * phaseM) * 20; 
} 
 
inline Vector3 renderSkydome(const Ray& ray, int x, int y) 
{ 
    // camera position
    Vector3 orig(0, atmosphere.m_groundRadius + 1000, 0); 

    return atmosphere.computeIncidentLight(orig, ray.direction, 0, 1000000.0f);     
} 
 
inline Vector3 GeneratePixel(const Ray& ray, int x, int y) 
{ 
    return renderSkydome(ray, x, y);  
    return 0; 
} 