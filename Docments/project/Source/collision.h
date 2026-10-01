#pragma once
#include "objectBase.h"
#include <string.h>
#include <vector>
#include "Transform.h"

namespace atk
{
	static const int CHARA_ATTACK_POS_NUM = 2;

	static const float CHARA_ATTACK_RADIUS = 180.0f;
	static const float CHARA_ATTACK_HEGIHT = 280.0f;
	static const float CHARA_ATTACK_CENTER_POS = 150.0f;

	enum WeponType
	{
		SWORD,	//剣
		SPEAR	//槍
	};

	enum CollType
	{
		POLY,		// ポリゴン
		SPHERE,		// 球
	};
}

// 修正
struct SEGMENT
{
	VECTOR3 sp;	//始点のベクトル
	VECTOR3 ep;	//終点のベクトル
	VECTOR3 vec;	//始点から終点のベクトル
};

struct CapsuleData
{
	VECTOR3 sPosition;
	VECTOR3 ePosition;
	VECTOR3 centerPosition;
	float radius;
	float height;

};

class AtkCollInfo
{
public:

	// 情報が有効かどうかのフラグ( true:有効  false:無効 )
	bool Enable;
	// 攻撃判定に使用する SCharaBaseInfo 構造体のメンバー変数 AttackPosInfo の要素番号
	int	AttackPosIndex;
	// 攻撃の軌跡エフェクトへのポインタ
	 //LocusEffect;
	// 攻撃判定用の座標の有効数
	int	ValidPositionNum;
	// 攻撃判定用のフレームに近い側の座標
	VECTOR3	NearPosition[atk::CHARA_ATTACK_POS_NUM];
	// 攻撃判定用のフレームから遠い側の座標
	VECTOR3	FarPosition[atk::CHARA_ATTACK_POS_NUM];
	// 攻撃に当たったキャラやステージの情報
	//SCharaAttackHitInfo   HitInfo;

	bool active;

	SEGMENT hitSegment;
	SEGMENT atkSegment;

	AtkCollInfo()
	{
		Enable = false;
		AttackPosIndex = 0;
		ValidPositionNum = 0;
		
		for (int i = 0; i < atk::CHARA_ATTACK_POS_NUM; i++)
		{
			NearPosition[i] = VGet(0, 0, 0);
			FarPosition[i] = VGet(0, 0, 0);
		}

		hitSegment = SEGMENT();
		atkSegment = SEGMENT();

		active = false;
	}

};

class Collision : public ObjectBase
{
public:

	Collision();
	~Collision();
	void Update()override {};
	void Draw()override {};

	/// <summary>
	/// 「球」の当たり判定
	/// </summary>
	/// <param name="radius = 半径"></param>
	/// <returns></returns>
	static bool Sphere(VECTOR3 pos1, VECTOR3 pos2, float radius);

	/// <summary>
	/// カプセルの情報をセット
	/// </summary>
	/// <param name="sPos">始点の座標</param>
	/// <param name="ePos">終点の座標</param>
	/// <param name="radius">半径</param>
	/// <param name="height">カプセル高さの半分</param>
	/// <param name="mainModel">カプセルをかぶせたいモデル</param>
	/// <param name="handle">カプセルを出したい場所の文字列</param>
	/// <returns>カプセルの情報</returns>
	const CapsuleData& SetCapsuleData(VECTOR3& sPos, VECTOR3& ePos, const float& radius, const float& height, const int& mainModel, const std::string& handle);

	/// <summary>
	/// カプセルの情報をセット
	/// </summary>
	/// <param name="sPos">始点の座標</param>
	/// <param name="ePos">終点の座標</param>
	/// <param name="radius">半径</param>
	/// <param name="height">カプセル高さの半分</param>
	/// <param name="centerPos">カプセルを出したい場所の中心点</param>
	/// <returns>カプセルの情報</returns>
	const CapsuleData& SetCapsuleData(VECTOR3& sPos, VECTOR3& ePos, const float& radius, const float& height, VECTOR3& centerPos);

	/// <summary>
	/// カプセルの情報をセット
	/// </summary>
	/// <param name="sPos">始点の座標</param>
	/// <param name="ePos">終点の座標</param>
	/// <param name="radius">半径</param>
	/// <param name="height">カプセル高さの半分</param>
	/// 	/// <param name="position">キャラクターの座標</param>
	/// <param name="centerPos">カプセルを出したい場所の中心点の座標</param>
	/// <returns>カプセルの情報</returns>
	const CapsuleData& SetCapsuleData(VECTOR3& sPos, VECTOR3& ePos, const float& radius, const float& height, VECTOR3& pos, VECTOR3& centerPos);

	/// <summary>
	/// カプセルとカプセルの判定
	/// </summary>
	/// <param name="segment1">線分1</param>
	/// <param name="segment2">線分2</param>
	/// <param name="radius">半径(当たり判定の大きさ)</param>
	/// <returns>当たっているかどうか</returns>
	bool Capsule(SEGMENT segment1, SEGMENT segment2, float radius);

	/// <summary>
	/// カプセルとカプセルの判定
	/// </summary>
	/// <param name="segment1">線分1</param>
	/// <param name="segment2">線分2</param>
	/// <param name="radius1">一つ目の半径(当たり判定の大きさ)</param>
	/// <param name="radius2">二つ目の半径(当たり判定の大きさ)</param>
	/// <returns>当たっているかどうか</returns>
	bool Capsule(SEGMENT segment1, SEGMENT segment2, float radius1, float radius2);

	/// <summary>
	/// 球とカプセルの判定
	/// </summary>
	/// <param name="segment1">球の座標</param>
	/// <param name="segment2">線分</param>
	/// <param name="radius">当たり判定の大きさ</param>
	/// <returns>当たっているかどうか</returns>
	bool SphereToCapsule(VECTOR3 pos, SEGMENT segment, float radius);

	/// <summary>
	/// 扇型
	/// </summary>
	/// <param name="fanPos">扇型を出してる方の座標</param>
	/// <param name="pos">相手の方の座標</param>
	/// <param name="range">角度(度数法)</param>
	/// <param name="length">長さ</param>
	/// <param name="direction">回転行列を混ぜた座標</param>
	/// <returns></returns>
	bool Fan(VECTOR3 fanPos, VECTOR3 pos, float range, float length, VECTOR3 direction);

	/// <summary>
	/// 線分を作る(Transform型)
	/// </summary>
	static SEGMENT SetSegment(const Transform& data, const VECTOR3& osp, const VECTOR3& oep);

	/// <summary>
	/// 線分を作るVECTOR3型
	/// </summary>
	static SEGMENT SetSegment(const VECTOR3& pos, const VECTOR3& rot, const VECTOR3& osp, const VECTOR3& oep);

	static SEGMENT SetSegment(const VECTOR3& rot, const VECTOR3& osp, const VECTOR3& oep);

	static SEGMENT SetSegment(const VECTOR3& osp, const VECTOR3& oep);

	/// <summary>
	/// 攻撃用の座標を更新
	/// </summary>
	/// <param name="nearPos">持ち手の座標</param>
	/// <param name="farPos">剣先の座標</param>
	/// <param name="index">自身の番号</param>
	void AttackPositionUpdate(const VECTOR3& nearPos, const VECTOR3& farPos, const int& index);

	/// <summary>
	/// 剣などの武器の攻撃判定
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="collRadius">追加で判定を大きくする場合</param>
	/// <param name="type">ポリゴンを使うかカプセルを使うか</param>
	/// <param name="index">自身の番号</param>
	/// <returns>当たっているか</returns>
	bool AttackCollision(const VECTOR3& pos, const VECTOR3& rot, const float& collRadius, const int& type, const int& index);

	/// <summary>
	/// インスタンス生成
	/// </summary>
	/// <param name="index">自身の番号</param>
	void AddAttackCollison(const int& index);

	//int AddAttackCollison();

	/// <summary>
	/// 不要な攻撃判定の情報を削除(毎回呼ぶのを推奨)
	/// </summary>
	void AttackCollDelete();

	/// <summary>
	/// 攻撃判定が生きているか
	/// </summary>
	/// <param name="index">作った番号淳</param>
	bool GetAttackCollActive(const int& index);

private:

	//0か1の値を絶対に返す
	void Clamp0to1(float& ratio);

	/// <summary>
	/// 点と直線の最短距離の計算
	/// </summary>
	/// <param name="position">点(座標)</param>
	/// <param name="s">線分</param>
	/// <param name="mp">点pから直線に下した垂線の端点(座標)</param>
	/// <param name="ratio">s.vec(始点から終点のベクトル)の長さを1とした時の「s.sp(始点のベクトル)からs.mp(終点のベクトル)までの長さ」の割合</param>
	/// <returns>点と直線の最短距離</returns>
	float CalcPointLineDistance(const VECTOR3& pos, const SEGMENT& s, VECTOR3& mp, float& ratio);


	/// <summary>
	/// 点と線分の最短距離の計算
	/// </summary>
	/// <param name="position">点(座標)</param>
	/// <param name="segment">線分</param>
	/// <param name="mp">点pから直線に下した垂線の端点(座標)</param>
	/// <param name="ratio">s.vec(始点から終点のベクトル)の長さを1とした時の「s.sp(始点のベクトル)からs.mp(終点のベクトル)までの長さ」の割合</param>
	/// <returns>球とカプセルの最短距離</returns>
	float CalcPointSegmentDistance(const VECTOR3& pos, const SEGMENT& s, VECTOR3& mp, float& ratio);


	/// <summary>
	/// 直線と直線の最短距離の計算
	/// </summary>
	/// <param name="s1">直線1</param>
	/// <param name="s2">直線2</param>
	/// <param name="mp1">最短線の端点1</param>
	/// <param name="mp2">最短線の端点2</param>
	/// <param name="ratio1">s1.vec(始点から終点のベクトル)の長さを1とした時の「s1.sp(始点のベクトル)からs.mp(終点のベクトル)までの長さ」の割合</param>
	/// <param name="ratio2">s2.vec(始点から終点のベクトル)の長さを1とした時の「s2.sp(始点のベクトル)からs.mp(終点のベクトル)までの長さ」の割合</param>
	/// <returns>直線と直線の最短距離</returns>
	float CalcLineLineDistance(const SEGMENT& s1, const SEGMENT& s2, VECTOR3& mp1, VECTOR3& mp2, float& ratio1, float& ratio2);


	/// <summary>
	/// 線分と線分の最短距離の計算
	/// </summary>
	/// <param name="s1">線分1</param>
	/// <param name="s2">線分2</param>
	/// <param name="mp1">最短線の端点1</param>
	/// <param name="mp2">最短線の端点2</param>
	/// <param name="ratio1">s1.vec(始点から終点のベクトル)の長さを1とした時の「s1.sp(始点のベクトル)からs.mp(終点のベクトル)までの長さ」の割合</param>
	/// <param name="ratio2">s2.vec(始点から終点のベクトル)の長さを1とした時の「s2.sp(始点のベクトル)からs.mp(終点のベクトル)までの長さ」の割合</param>
	/// <returns>カプセルとカプセルの最短距離</returns>
	float CalcSegmentSegmentDistance(const SEGMENT& s1, const SEGMENT& s2, VECTOR3& mp1, VECTOR3& mp2, float& ratio1, float& ratio2);


	std::vector<AtkCollInfo*> atkColl;
};
