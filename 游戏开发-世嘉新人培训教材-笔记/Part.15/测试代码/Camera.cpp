#include "Camera.h"
#include "Matrix44.h"
#include "Matrix34.h"
#include "Vector3.h"
#include <GameLib/Framework.h>

Camera::Camera() :mFov(60), mNearClip(1.0), mFarClip(10000.0), mTarget(0.0, 0.0, 0.0), mPosition(0.0, 0.0, 1.0)
{
}

void Camera::setFov(double iFov)
{
	mFov = iFov;
}

void Camera::setNearClip(double iNearClip)
{
	mNearClip = iNearClip;
}

void Camera::setFarClip(double iFarClip)
{
	mFarClip = iFarClip;
}

void Camera::setTarget(const Vector3& target)
{
	mTarget = target;
}

void Camera::setPosition(const Vector3& viewPosition)
{
	mPosition = viewPosition;
}

double Camera::getFov()
{
	return mFov;
}

double Camera::getNearClip()
{
	return mNearClip;
}

double Camera::getFarClip()
{
	return mFarClip;
}

const Vector3* Camera::getTarget()
{
	return &mTarget;
}

const Vector3* Camera::getPosition()
{
	return &mPosition;
}

void Camera::createPerspectiveViewMatrix(Matrix44* pvm) const
{
	GameLib::Framework frame = GameLib::Framework::instance();
	// 世界矩阵
	pvm->setPerspectiveTransform(mFov, frame.width(), frame.height(), mNearClip, mFarClip);
	// 观察举证
	Matrix34 viewMatrix;
	viewMatrix.setView(mPosition, mTarget);
	*pvm *= viewMatrix;
}