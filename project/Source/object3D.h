#pragma once
#include "objectBase.h"
#include "Transform.h"

class Object3D :public ObjectBase
{
public:
	Object3D();
	~Object3D();
	virtual void Update()override {};
	virtual void Draw()override;

	//ゲッター

	inline const Transform& GetPosition() { return data; }
	inline const VECTOR3& GetVelocity() { return velocity; }
	inline const int& GetModel() const { return hModel; }
	virtual const MATRIX Matrix()const;

	//セッター
	inline void SetPosition(const VECTOR3& pos) { data.position = pos; }
	inline void SetRotation(const VECTOR3& rot) { data.rotation = rot; }
	inline void SetScale(const VECTOR3& _scale) { data.scale = _scale; }
	inline void SetVelocity(const VECTOR3& vel) { velocity = vel; }

	
	void LoadModel(const std::string& handle);
	void DeleteModel();

protected:
	int hModel;
	Transform data;
	VECTOR3 velocity;
	
};


/// <summary>
/// 回転行列の取得
/// </summary>
inline MATRIX MGetRotatation(const VECTOR& rot)
{
	MATRIX mRotX = MGetRotX(rot.x);
	MATRIX mRotY = MGetRotY(rot.y);
	MATRIX mRotZ = MGetRotZ(rot.z);

	MATRIX mRot = MMult(mRotZ, mRotX);
	mRot = MMult(mRot, mRotY);

	return mRot;
}

/// <summary>
/// 同じ大きさのスケールを取得
/// </summary>
inline MATRIX MGetScale(const float& scale)
{
	return MGetScale(VGet(scale, scale, scale));
}

/// <summary>
	///  モデルのリグの座標に変換する行列を入手する
	/// </summary>
	/// <param name="mainModel">モデルのハンドル</param>
	/// <param name="rigName">リグの名前(文字列)</param>
	/// <returns>取得したフレームのワールド座標の行列</returns>
inline static const MATRIX GetModelRigMatrix(const int& mainModel, const std::string& handle)
{
	const char* copy = handle.c_str();

	// モデルリグのフレームを取得する
	int rig = MV1SearchFrame(mainModel, copy);
	// 取得したフレームの現在のワールド座標の行列を取得する
	MATRIX m = MV1GetFrameLocalWorldMatrix(mainModel, rig);

	return m;
}

inline static const VECTOR3 GetModelRigPosition(const int& mainModel, const std::string& handle)
{
	VECTOR pos = VGet(0, 0, 0);
	MATRIX m;
	m = GetModelRigMatrix(mainModel, handle);

	pos = VTransform(pos, m);

	return pos;
}