#include "portal.ih"

// Lengyel, Eric. "Oblique View Frustum Depth Projection and Clipping".
// Journal of Game Development, Vol. 1, No. 2 (2005)
// http://www.terathon.com/code/oblique.html

glm::mat4 const Portal::clippedProjMat(glm::mat4 const &viewMat, glm::mat4 const &projMat) const
{
	float dist = glm::length(d_position);
	glm::vec4 clipPlane(d_orientation * glm::vec3(0.0f, 0.0f, -1.0f), dist);
	clipPlane = glm::inverse(glm::transpose(viewMat)) * clipPlane;

	glm::vec4 q = glm::inverse(projMat) * glm::vec4(
        glm::sign(clipPlane.x),
        glm::sign(clipPlane.y),
        1.0f,
        1.0f
    );

    glm::vec4 c = clipPlane * (2.0f / (glm::dot(clipPlane, q)));

    glm::mat4 newProj = projMat;
    // third row = clip plane - fourth row
    newProj = glm::row(newProj, 2, c - glm::row(newProj, 3));

    return newProj;
}