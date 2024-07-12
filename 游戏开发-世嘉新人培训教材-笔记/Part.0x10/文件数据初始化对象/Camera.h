#pragma once
#include "Vector3.h"
class Matrix44;
class Camera
{
public:
	Camera();
	void setFov(double);
	void setNearClip(double);
	void setFarClip(double);
	void setTarget(const Vector3&);
	void setPosition(const Vector3&);

	double getFov();
	double getNearClip();
	double getFarClip();
	const Vector3* getTarget();
	const Vector3* getPosition();

	void createPerspectiveViewMatrix(Matrix44* pvm)const;
private:
	double mFov;
	double mNearClip;
	double mFarClip;
	Vector3 mTarget;
	Vector3 mPosition;
};

