#include "LSpot.hpp"

namespace Ge
{
	LSpot::LSpot(int index, VulkanMisc * vM) : Lights(index, vM)
	{
		m_ubl.constant = 1.0f;
		m_ubl.linear = 0.09f;
		m_ubl.quadratic = 0.032f;
		m_ubl.cutOff = 1.0f;
		m_ubl.outerCutOff = 2.0f;
		m_ubl.status = 2;
	}

	float LSpot::getConstant()
	{
		return m_ubl.constant;
	}

	void LSpot::setConstant(float constant)
	{
		m_ubl.constant = constant;
	}

	float LSpot::getLinear()
	{
		return m_ubl.linear;
	}

	void LSpot::setLinear(float linear)
	{
		m_ubl.linear = linear;
	}

	float LSpot::getQuadratic()
	{
		return m_ubl.quadratic;
	}

	void LSpot::setQuadratic(float quadratic)
	{
		m_ubl.quadratic = quadratic;
	}

	float LSpot::getCutOff()
	{
		return m_ubl.cutOff;
	}

	void LSpot::setCutOff(float cutOff)
	{
		m_ubl.cutOff = cutOff;
	}

	float LSpot::getOuterCutOff()
	{
		return m_ubl.outerCutOff;
	}

	void LSpot::setOuterCutOff(float outerCutOff)
	{
		m_ubl.outerCutOff = outerCutOff;
	}
}