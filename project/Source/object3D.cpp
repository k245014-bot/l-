#include "object3D.h"

Object3D::Object3D()
{
	hModel = -1;
	velocity = VECTOR3(0, 0, 0);
}

Object3D::~Object3D()
{
	if (resourceKeep == false)
	{
		DeleteModel();
	}
}

void Object3D::Draw()
{
	/*if (hModel > 0)
	{
		MV1SetMatrix(hModel, Matrix());
		MV1DrawModel(hModel);
	}*/
}

void Object3D::ObjectDraw()
{
	if (hModel > 0)
	{
		MV1SetMatrix(hModel, Matrix());
		MV1DrawModel(hModel);
	}
}

const MATRIX Object3D::Matrix() const
{
	MATRIX m = MGetIdent();

	MATRIX mTrans = MGetTranslate(data.position);
	MATRIX mRot = MGetRotatation(data.rotation);
	MATRIX mScale = MGetScale(data.scale);

	m = MMult(mScale, mRot);
	m = MMult(m, mTrans);

	return m;
}

void Object3D::LoadModel(const std::string& handle)
{
	const char* copy = handle.c_str();
	hModel = MV1LoadModel(copy);
}

void Object3D::DeleteModel()
{
	MV1DeleteModel(hModel);
}
