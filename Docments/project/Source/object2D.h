#pragma once
#include "objectBase.h"

class Object2D:public ObjectBase
{
public:
	Object2D();
	~Object2D();
	virtual void Update()override {};
	virtual void Draw()override;

	//ゲッター

	inline const VECTOR2& GetPosition() { return position; }
	inline const VECTOR2& GetVelocity() { return velocity; }
	inline const float& GetRotation() { return rotation; }
	inline const float& GetScale() { return scale; }

	//セッター
	inline void SetPosition(const VECTOR2& pos) { position = pos; }
	inline void SetRotation(const float rot) { rotation = rot; }
	inline void SetScale(const float& _scale) { scale = _scale; }
	inline void SetVelocity(const VECTOR2& vel) { velocity = vel; }

	inline float Lerp(float a, float b, float t) 
	{
		return a + (b - a) * t;
	}

	inline float MoveTowards(float current, float target, float maxDelta) 
	{
		if (fabs(target - current) <= maxDelta) 
		{
			return target; // 一気に届いちゃうならピタッと止める！
		}
		return current + (target > current ? +1.0f : -1.0f) * maxDelta;
	}

	void LoadhImage(const std::string& handle);
	void DeleteImage();

protected:

	int hImage;
	VECTOR2 position;
	VECTOR2 velocity;
	float rotation;
	float scale;
};


