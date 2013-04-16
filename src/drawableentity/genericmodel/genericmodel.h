#ifndef INCLUDED_GENERIC_MODEL_
#define INCLUDED_GENERIC_MODEL_

#include <vector>
#include <glm/glm.hpp>
#include "../drawableentity.h"
#include "../../model/model.h"
#include "../../texture/texture.h"
#include "../../shaderprogram/shaderprogram.h"


class GenericModel : public DrawableEntity
{
    Model &d_model;
    Texture &d_texture;

    public:
        GenericModel(std::string const &texName, std::string const &modelName);
        ~GenericModel();

        virtual bool needsLighting() const;

    private:
    	virtual void updateImpl(float deltaTime);
    	virtual void drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat);
};

inline bool GenericModel::needsLighting() const
{
	return true;
}
        
#endif
