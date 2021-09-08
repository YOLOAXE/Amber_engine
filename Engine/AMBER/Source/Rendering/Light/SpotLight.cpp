#include "SpotLight.hpp"

namespace Ge
{
	SpotLight::SpotLight(int index, VulkanMisc * vM) : Lights(index, vM)
	{
		/*m_ubl.constant = 1.0f;
		m_ubl.linear = 0.09f;
		m_ubl.quadratic = 0.032f;
		m_ubl.cutOff = 1.0f;
		m_ubl.outerCutOff = 2.0f;*/
		m_ubl.status = 2;
	}

	float SpotLight::getConstant()
	{
		return 0;//m_ubl.constant;
	}

	void SpotLight::setConstant(float constant)
	{
		//m_ubl.constant = constant;
	}

	float SpotLight::getLinear()
	{
		return 0;//m_ubl.linear;
	}

	void SpotLight::setLinear(float linear)
	{
		//m_ubl.linear = linear;
	}

	float SpotLight::getQuadratic()
	{
		return 0;//m_ubl.quadratic;
	}

	void SpotLight::setQuadratic(float quadratic)
	{
		//m_ubl.quadratic = quadratic;
	}

	float SpotLight::getCutOff()
	{
		return 0;//m_ubl.cutOff;
	}

	void SpotLight::setCutOff(float cutOff)
	{
		//m_ubl.cutOff = cutOff;
	}

	float SpotLight::getOuterCutOff()
	{
		return 0;//m_ubl.outerCutOff;
	}

	void SpotLight::setOuterCutOff(float outerCutOff)
	{
		//m_ubl.outerCutOff = outerCutOff;
	}
}