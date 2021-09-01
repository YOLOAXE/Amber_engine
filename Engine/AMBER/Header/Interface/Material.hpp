#ifndef __ENGINE_INTERFACE_MATERIAL__
#define __ENGINE_INTERFACE_MATERIAL__

#include "Texture.hpp"
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Component.hpp"
#include "Pipeline.hpp"

class Material : public Component
{
public:
	virtual void setColor(Vector3 color) = 0;
	virtual void setMetallic(float metal) = 0;
	virtual void setNormal(float normal) = 0;
	virtual void setOclusion(float ao) = 0;
	virtual void setAlbedoTexture(Texture * albedo) = 0;
	virtual void setNormalTexture(Texture * normal) = 0;
	virtual void setMetallicTexture(Texture * metal) = 0;
	virtual void setOclusionTexture(Texture * oclu) = 0;
	virtual Vector3 getColor() = 0;
	virtual float getMetallic() = 0;
	virtual float getNormal() = 0;
	virtual float getOclusion() = 0;
	virtual Texture * getAlbedoTexture() = 0;
	virtual Texture * getNormalTexture() = 0;
	virtual Texture * getMetallicTexture() = 0;
	virtual Texture * getOclusionTexture() = 0;
	virtual int getIndex() = 0;
	virtual bool getLightActive() = 0;
	virtual void setLightActive(bool state) = 0;
	virtual void setHDR(float hdr) = 0;
	virtual void setHDRTexture(Texture * hdr) = 0;
	virtual float getHDR() = 0;
	virtual Texture * getHDRTexture() = 0;
	virtual Vector2 getOffset() = 0;
	virtual void setOffset(Vector2 off) = 0;
	virtual void setPipeline(Pipeline * p) = 0;
	virtual int getPipelineIndex() = 0;
};

#endif // __ENGINE_INTERFACE_MATERIAL__
