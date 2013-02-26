#include "portal.ih"

inline float sgn(float a)
{
    if (a > 0.0f) return 1.0f;
    if (a < 0.0f) return -1.0f;
    return 0.0f;
}

glm::mat4 const Portal::clippedProjMat(glm::mat4 const &viewMat, glm::mat4 const &projMat) const
{
	// (Portal faces at positive Z by default, camera looks at it from behind,
	//  so the default normal to rotate by is negative Z)

	// Portal "normal" in camera space
	glm::vec3 normalCam = d_orientation * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 posCam = glm::vec3(viewMat * glm::vec4(d_position, 1.0));

	// Ax + By + Cz + D = 0
	// (x, y, z) == d_position
	// (A, B, C) == normal
	glm::vec3 prod(normalCam.x * posCam.x,
		normalCam.y * posCam.y,
		normalCam.z * posCam.z);
	float d = -(prod.x + prod.y + prod.z);

	// D has to be negative (towards camera),
	// otherwise use normal proj mat
	if (d >= 0.0f)
	{
		cout << "returning" << endl << endl << endl;
		return projMat;
	}
	else
	{
		cout << "normalCam = (" << normalCam.x << ", " << normalCam.y << ", " << normalCam.z << ")" << endl;
		cout << "posCam    = (" << posCam.x << ", " << posCam.y << ", " << posCam.z << ")" << endl;
		cout << "d         = " << d << endl << endl;
	}

	// Clip plane is vec4(A, B, C, D)
	glm::vec4 clipPlane(normalCam, d);


	// Using technique in:
	// Lengyel, Eric. “Oblique View Frustum Depth Projection and Clipping”.
	// Journal of Game Development, Vol. 1, No. 2 (2005), Charles River Media, pp. 5–16.
	// Explained here http://www.terathon.com/code/oblique.html

	//glm::vec4 q = glm::inverse(projMat) *
	//	glm::vec4(sgn(clipPlane.x), sgn(clipPlane.y), 1.0f, 1.0f);

	glm::vec4 q;
	q.x = sgn(clipPlane.x);
	q.y = sgn(clipPlane.y);
	q.z = -sgn(clipPlane.z);
	q.w = 1.0f;
	q = glm::inverse(projMat) * q;


	glm::vec4 c = clipPlane * (2.0f / glm::dot(clipPlane, q));

	glm::mat4 newProjMat = projMat;
	newProjMat = glm::row(newProjMat, 2, glm::vec4(c.x, c.y, c.z + 1.0f, c.w));

	return newProjMat;

	/*
	void ModifyProjectionMatrix(const Vector4D& clipPlane)
	{
	    float       matrix[16];
	    Vector4D    q;

	    // Grab the current projection matrix from OpenGL
	    glGetFloatv(GL_PROJECTION_MATRIX, matrix);
	    
	    // Calculate the clip-space corner point opposite the clipping plane
	    // as (sgn(clipPlane.x), sgn(clipPlane.y), 1, 1) and
	    // transform it into camera space by multiplying it
	    // by the inverse of the projection matrix
	    
	    q.x = (sgn(clipPlane.x) + matrix[8]) / matrix[0];
	    q.y = (sgn(clipPlane.y) + matrix[9]) / matrix[5];
	    q.z = -1.0F;
	    q.w = (1.0F + matrix[10]) / matrix[14];
	    
	    // Calculate the scaled plane vector
	    Vector4D c = clipPlane * (2.0F / Dot(clipPlane, q));
	    
	    // Replace the third row of the projection matrix
	    matrix[2] = c.x;
	    matrix[6] = c.y;
	    matrix[10] = c.z + 1.0F;
	    matrix[14] = c.w;

	    // Load it back into OpenGL
	    glMatrixMode(GL_PROJECTION);
	    glLoadMatrix(matrix);
	}
	*/

}