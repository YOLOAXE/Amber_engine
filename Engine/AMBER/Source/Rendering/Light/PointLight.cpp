#include "PointLight.hpp"

namespace Ge
{
	PointLight::PointLight(int index, VulkanMisc * vM) : Lights(index,vM)
	{
		m_ubl.status = 1;
	}

	float PointLight::getConstant()
	{
		return 0;// m_ubl.constant;
	}

	void PointLight::setConstant(float constant)
	{
		//m_ubl.constant = constant;
	}

	float PointLight::getLinear()
	{
		return 0;//m_ubl.linear;
	}

	void PointLight::setLinear(float linear)
	{
		//m_ubl.linear = linear;
	}

	float PointLight::getQuadratic()
	{
		return 0;//m_ubl.quadratic;
	}

	void PointLight::setQuadratic(float quadratic)
	{
		//m_ubl.quadratic = quadratic;
	}
}