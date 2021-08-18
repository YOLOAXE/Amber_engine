#include "LPoint.hpp"

namespace Ge
{
	LPoint::LPoint(int index, VulkanMisc * vM) : Lights(index,vM)
	{
		m_ubl.constant = 1.0f;
		m_ubl.linear = 0.09f;
		m_ubl.quadratic = 0.032f;
		m_ubl.status = 1;
	}

	float LPoint::getConstant()
	{
		return m_ubl.constant;
	}

	void LPoint::setConstant(float constant)
	{
		m_ubl.constant = constant;
	}

	float LPoint::getLinear()
	{
		return m_ubl.linear;
	}

	void LPoint::setLinear(float linear)
	{
		m_ubl.linear = linear;
	}

	float LPoint::getQuadratic()
	{
		return m_ubl.quadratic;
	}

	void LPoint::setQuadratic(float quadratic)
	{
		m_ubl.quadratic = quadratic;
	}
}