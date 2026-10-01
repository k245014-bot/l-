#include "collision.h"
#include "object3D.h"


Collision::Collision()
{
}

Collision::~Collision()
{
}


bool Collision::Sphere(VECTOR3 pos1, VECTOR3 pos2, float radius)
{
	return VSize(VSub(pos2, pos1)) <= radius;
}


const CapsuleData& Collision::SetCapsuleData(VECTOR3& sPos, VECTOR3& ePos, const float& radius, const float& height, const int& mainModel, const std::string& handle)
{
	CapsuleData capsule;

	capsule.radius = radius;
	capsule.height = height;
	capsule.centerPosition = GetModelRigPosition(mainModel, handle);

	capsule.sPosition = VAdd(sPos, capsule.centerPosition);
	capsule.ePosition = VAdd(ePos, capsule.centerPosition);

	capsule.sPosition.y -= height / 2.0f;
	capsule.ePosition.y += height / 2.0f;

	return capsule;
}

const CapsuleData& Collision::SetCapsuleData(VECTOR3& sPos, VECTOR3& ePos, const float& radius, const float& height, VECTOR3& centerPos)
{
	CapsuleData capsule;

	capsule.radius = radius;
	capsule.height = height;
	capsule.centerPosition = centerPos;

	capsule.sPosition = VAdd(sPos, capsule.centerPosition);
	capsule.ePosition = VAdd(ePos, capsule.centerPosition);

	capsule.sPosition.y -= height / 2.0f;
	capsule.ePosition.y += height / 2.0f;

	return capsule;
}

const CapsuleData& Collision::SetCapsuleData(VECTOR3& sPos, VECTOR3& ePos, const float& radius, const float& height, VECTOR3& pos, VECTOR3& centerPos)
{
	CapsuleData capsule;

	capsule.radius = radius;
	capsule.height = height;
	capsule.centerPosition = centerPos;

	capsule.sPosition = VAdd(pos, capsule.centerPosition);
	capsule.ePosition = VAdd(pos, capsule.centerPosition);

	capsule.sPosition.y -= height / 2.0f;
	capsule.ePosition.y += height / 2.0f;

	return capsule;
}

SEGMENT Collision::SetSegment(const Transform& data, const VECTOR3& osp, const VECTOR3& oep)
{
	MATRIX mTrans = MGetTranslate(data.position);
	MATRIX mRot = MGetRotatation(data.rotation);

	MATRIX m = MMult(mRot, mTrans);

	SEGMENT s;
	s.sp = VTransform(osp, m);
	s.ep = VTransform(oep, m);
	s.vec = VSub(s.ep, s.sp);

	return s;
}

SEGMENT Collision::SetSegment(const VECTOR3& pos, const VECTOR3& rot, const VECTOR3& osp, const VECTOR3& oep)
{
	MATRIX mTrans = MGetTranslate(pos);
	MATRIX mRot = MGetRotatation(rot);

	MATRIX m = MMult(mRot, mTrans);

	SEGMENT s;
	s.sp = VTransform(osp, m);
	s.ep = VTransform(oep, m);
	s.vec = VSub(s.ep, s.sp);

	return s;
}

SEGMENT Collision::SetSegment(const VECTOR3& rot, const VECTOR3& osp, const VECTOR3& oep)
{
	MATRIX m = MGetRotatation(rot);

	SEGMENT s;
	s.sp = VTransform(osp, m);
	s.ep = VTransform(oep, m);
	s.vec = VSub(s.ep, s.sp);

	return s;
}

SEGMENT Collision::SetSegment(const VECTOR3& osp, const VECTOR3& oep)
{
	SEGMENT s;

	s.sp = osp;
	s.ep = oep;
	s.vec = VSub(s.ep, s.sp);

	return s;
}

void Collision::AttackPositionUpdate(const VECTOR3& nearPos, const VECTOR3& farPos, const int& index)
{
	auto itr = atkColl.at(index);

	//std::advance(itr, index);

	//追加できる最大数より大きい場合は一つ減らす。
	if ((*itr).ValidPositionNum >= atk::CHARA_ATTACK_POS_NUM)
	{
		(*itr).ValidPositionNum = atk::CHARA_ATTACK_POS_NUM - 1;
	}

	//既に入っている座標を一個分ずらす
	for (int i = (*itr).ValidPositionNum - 1; i >= 0; i--)
	{
		(*itr).NearPosition[i + 1] = (*itr).NearPosition[i];
		(*itr).FarPosition[i + 1] = (*itr).FarPosition[i];
	}

	//先頭に座標を追加

	(*itr).NearPosition[0] = nearPos;
	(*itr).FarPosition[0] = farPos;
	//有効な座標の数を増やす
	(*itr).ValidPositionNum++;
}

bool Collision::AttackCollision(const VECTOR3& pos, const VECTOR3& rot, const float& collRadius, const int& type, const int& index)
{

	auto itr = atkColl.at(index);

	//std::advance(itr, index);

	int  HitResult = 0;
	float radius = atk::CHARA_ATTACK_RADIUS;
	float height = atk::CHARA_ATTACK_HEGIHT;
	VECTOR3 centerPos = VGet(0, atk::CHARA_ATTACK_CENTER_POS, 0);
	VECTOR3 hitPos = pos;

	if ((*itr).ValidPositionNum < 2)
	{
		return false;
	}

	CapsuleData atkCapsule = SetCapsuleData(hitPos, hitPos, radius, height, centerPos);

	(*itr).hitSegment = SetSegment(atkCapsule.sPosition, atkCapsule.ePosition);
	(*itr).atkSegment = SetSegment((*itr).NearPosition[0], (*itr).NearPosition[1]);

	switch (type)
	{
	case atk::POLY:

		HitResult = HitCheck_Capsule_Triangle((*itr).hitSegment.sp, (*itr).hitSegment.ep, radius,
			(*itr).FarPosition[0], (*itr).FarPosition[1], (*itr).NearPosition[0]);

		if (HitResult == FALSE)
		{
			HitResult = HitCheck_Capsule_Triangle((*itr).hitSegment.sp, (*itr).hitSegment.ep, radius,
				(*itr).NearPosition[0], (*itr).FarPosition[1], (*itr).NearPosition[1]);
		}

		break;
	case atk::SPHERE:

		HitResult = Capsule((*itr).hitSegment, (*itr).atkSegment, radius, collRadius);

		break;
	}

	//当たっていなかったら終了
	if (HitResult == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Collision::AddAttackCollison(const int& index)
{
	atkColl.emplace_back(new AtkCollInfo);

	auto itr = atkColl.at(index);

	(*itr).active = true;
}

//int Collision::AddAttackCollison()
//{
//	
//	atkColl.emplace_back(new AtkCollInfo);
//
//	auto itr = atkColl.back();
//
//	(*itr).active = true;
//	return ;
//	
//}

void Collision::AttackCollDelete()
{
	for (auto itr = atkColl.begin(); itr != atkColl.end();)
	{
		if ((*itr)->active == false)
		{

			itr = atkColl.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

bool Collision::GetAttackCollActive(const int& index)
{
	auto itr = atkColl.at(index);

	if (itr->active == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void Collision::Clamp0to1(float& ratio)
{
	if (ratio < 0.0f)
	{
		ratio = 0.0f;
	}
	else if (ratio > 1.0f)
	{
		ratio = 1.0f;
	}
}

float Collision::CalcPointLineDistance(const VECTOR3& pos, const SEGMENT& s, VECTOR3& mp, float& ratio)
{
	ratio = 0.0f;
	//始点から終点のベクトルを二乗したサイズを求める
	float dvv = VSquareSize(s.vec);
	if (dvv > 0.0f)
	{
		//ratio=内積で計算した長さ÷s.vecの長さという割合になる
		ratio = VDot(s.vec, VSub(pos, s.sp)) / dvv;
	}
	mp = VAdd(s.sp, VScale(s.vec, ratio));

	return VSize(VSub(pos, mp));
}

float Collision::CalcPointSegmentDistance(const VECTOR3& pos, const SEGMENT& s, VECTOR3& mp, float& ratio)
{
	//先に点と直線の最短距離を求める
	float distance = CalcPointLineDistance(pos, s, mp, ratio);

	//線分を1.0fとした割合のため0.0f～1.0f以外の数字は判定がない
	//点と直線の最短距離の計算で割合も出しているのでこれを使う

	//mpが線分の外にある(始点寄り)
	if (ratio < 0.0f)
	{
		//posから線分の始点までの距離が最短のため
		//mpに始点の値(spを入れる)
		mp = s.sp;
		return VSize(VSub(pos, mp));
	}
	//mpが線分の外にある(始点寄り)
	if (ratio > 1.0f)
	{
		//posから線分の終点までの距離が最短のため
		//mpに始点の値(spを入れる)
		mp = s.ep;
		return VSize(VSub(pos, mp));
	}

	//mpが線分の内側にある場合distをreturnする
	return distance;
}

float Collision::CalcLineLineDistance(const SEGMENT& s1, const SEGMENT& s2, VECTOR3& mp1, VECTOR3& mp2, float& ratio1, float& ratio2)
{
	//二つの直線が平行かどうか調べるため外積を使う
	//平行の場合、外積を使うとベクトル値が0になる
	//誤差があるため0.000001f寄り小さいか調べる
	//平行の場合
	if (VSquareSize(VCross(s1.vec, s2.vec)) < 0.000001f)
	{

		mp1 = s1.sp;
		ratio1 = 0.0f;

		//点と直線の最短距離を求める
		float dist = CalcPointLineDistance(mp1, s2, mp2, ratio2);
		return dist;
	}

	//平行ではない場合
	//互いに垂直になるような最短線の端点mp1,mp2を求める
	//次の順で求めていく ratio1 → mp1 → ratio2 → mp2

	/*
	両直線の最短距離を結ぶ線は、両直線に共通の垂線となる。。。その垂線の端点mp1,mp2
	mp1 = s1.sp + s1.v * ratio1
	mp2 = s2.sp + s2.v * ratio2
	*/

	float dotv1v2 = VDot(s1.vec, s2.vec);
	float dotv1v1 = VSquareSize(s1.vec);	//VDot(s1.v, s1.v)と同じ
	float dotv2v2 = VSquareSize(s2.vec);	//VDot(s2.v, s2.v)と同じ
	VECTOR3 spDistance = VSub(s1.sp, s2.sp);
	ratio1 = (dotv1v2 * VDot(s2.vec, spDistance) - dotv2v2 * VDot(s1.vec, spDistance))
		/ (dotv1v1 * dotv2v2 - dotv1v2 * dotv1v2);
	mp1 = VAdd(s1.sp, VScale(s1.vec, ratio1));
	ratio2 = VDot(s2.vec, VSub(mp1, s2.sp)) / dotv2v2;
	mp2 = VAdd(s2.sp, VScale(s2.vec, ratio2));

	return VSize(VSub(mp2, mp1));
}

float Collision::CalcSegmentSegmentDistance(const SEGMENT& s1, const SEGMENT& s2, VECTOR3& mp1, VECTOR3& mp2, float& ratio1, float& ratio2)
{
	float distance = 0.0f;


	// 縮退しているときの処理

	// 縮退とは？
	// 二つのベクトルが同じ向き（または逆向き）になると、実質1本分の情報しか持たなくなる。
	// 本来、2つのベクトルが異なる方向を向いていれば、平面（2次元）の広がりを作れる。
	// しかし、2つが同じ向きになったら？ → 実質1つの方向しか持たない！
	// これによって「次元が減った」ことを意味し、この状態を「縮退」しているという。

	// s1.vecが縮退している場合
	if (VSquareSize(s1.vec) < 0.000001f)
	{
		// かつs2.vecも縮退している場合
		if (VSquareSize(s2.vec) < 0.000001f)
		{
			// 球と球(点と点)の最短距離を返す
			distance = VSize(VSub(s2.sp, s1.sp));
			mp1 = s1.sp;
			mp2 = s2.sp;
			ratio1 = ratio2 = 0.0f;
			return distance;
		}
		else
		{
			// s1.spとs2.vecの球(点)とカプセル(線分)の最短距離を返す
			distance = CalcPointSegmentDistance(s1.sp, s2, mp2, ratio2);
			mp1 = s1.sp;
			ratio1 = 0.0f;
			Clamp0to1(ratio2);
			return distance;
		}
	}
	// s2.vecが縮退している場合
	else if (VSquareSize(s2.vec) < 0.000001f)
	{
		// s2.spとsvec1の球(点)とカプセル(線分)の最短距離を返す
		distance = CalcPointSegmentDistance(s2.sp, s1, mp1, ratio1);
		mp2 = s2.sp;
		Clamp0to1(ratio1);
		ratio2 = 0.0f;
		return distance;
	}

	//最初のチェック
	//0.0f～1.0fの内側にいた場合に最短距離を返す
	distance = CalcLineLineDistance(s1, s2, mp1, mp2, ratio1, ratio2);
	if (ratio1 >= 0.0f && ratio1 <= 1.0f && ratio2 >= 0.0f && ratio2 <= 1.0f)
	{
		return distance;
	}

	//mp1,mp2の両方、またはどちらかが線分の中に入ってない場合
	//2回目のチェック
	//0に近ければ始点が近くて1に近ければ終点に近い
	//mp1,t1を求めなおす→t2を0～1にクランプしてmp2からs1.vに垂線をたらす
	Clamp0to1(ratio2);
	mp2 = VAdd(s2.sp, VScale(s2.vec, ratio2));
	distance = CalcPointLineDistance(mp2, s1, mp1, ratio1);
	if (ratio1 >= 0.0f && ratio1 <= 1.0f)
	{
		//mp1が線分内にある場合
		return distance;
	}

	//mp1が線分内にない場合
	//3回目のチェック
	//上のやつの数値を入れ替えた判定をとる
	//mp2,t2を求めなおす→t2を0～1にクランプしてmp1からs2.vに垂線をたらしてみる
	Clamp0to1(ratio1);
	mp1 = VAdd(s1.sp, VScale(s1.vec, ratio1));
	distance = CalcPointLineDistance(mp1, s2, mp2, ratio2);
	if (ratio2 >= 0.0f && ratio2 <= 1.0f)
	{
		//mp1が線分内にある場合
		return distance;
	}

	//どれも入らなかった場合mp2からmp1の距離を返す
	Clamp0to1(ratio2);
	mp2 = VAdd(s2.sp, VScale(s2.vec, ratio2));
	return VSize(VSub(mp2, mp1));
}


bool Collision::Capsule(SEGMENT segment1, SEGMENT segment2, float radius)
{
	VECTOR3 mp1;
	VECTOR3 mp2;
	float ratio1, ratio2;

	float distace = CalcSegmentSegmentDistance(segment1, segment2, mp1, mp2, ratio1, ratio2);

	if (distace < radius + radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::Capsule(SEGMENT segment1, SEGMENT segment2, float radius1, float radius2)
{
	VECTOR3 mp1;
	VECTOR3 mp2;
	float ratio1, ratio2;

	float distace = CalcSegmentSegmentDistance(segment1, segment2, mp1, mp2, ratio1, ratio2);

	if (distace < radius1 + radius2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::SphereToCapsule(VECTOR3 pos, SEGMENT segment, float radius)
{
	VECTOR3 mp;
	float ratio;

	float distace = CalcPointSegmentDistance(pos, segment, mp, ratio);

	if (distace < radius + radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Collision::Fan(VECTOR3 fanPos, VECTOR3 pos, float range, float length, VECTOR3 direction)
{
	//距離を求める
	VECTOR3 targetVec = VSub(pos, fanPos);

	//ベクトルの大きさを出す
	float distance = VSize(targetVec);

	//内側に入っていない場合falseを返して終了
	if (length < distance)
	{
		return false;
	}

	// 内積計算
	//cosθ(なす角)を出す
	float dot = VDot(VNorm(direction), VNorm(targetVec));
	
	//扇の範囲もcosの値にする。
	float fanCos = cosf((range / 2.0f) * DegToRad);

	//なす角が扇の範囲の内側に入っていない場合falseを返して終了
	if (fanCos > dot)
	{
		return false;
	}
	
	
	
	return true;
}

