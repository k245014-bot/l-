#include "Mao.h"
#include "../../../ImGui/imgui.h"

Mao::Mao()
{
	LoadModel(fileName);
	data.position = VZero;
	animation = new AnimationManager(hModel);
	LoadAnim(animData.dance, "data/model/mao/Motion/Dance.mv1");
	LoadAnim(animData.attack, "data/model/mao/Motion/Attack.mv1");
	
	SetAnimation(0, animData.dance, 30.0f, true);
	//SetAnimation(1, animData.attack, 40.0f, true);

}

Mao::~Mao()
{
}

void Mao::Update()
{
	animation->Play(motionId, playMotion, motionSpeed, isMotionLoop);
}

void Mao::Draw()
{
	ImGuiDraw();
}

void Mao::ImGuiDraw()
{
	ImGui::Begin("CameraEditor");

	if (ImGui::Button("DanceAnim"))
		SetAnimation(0, animData.dance, 30.0f, true);
	if (ImGui::Button("AtkAnim"))
		SetAnimation(1, animData.attack, 40.0f, false);
	/*
	if (ImGui::Button("enemySpwn"))
		CreateEnemy(VZero, 1, 0);
	if (ImGui::Button("ack1"))
		Cooperate();
	if (ImGui::Button("ack2"))
	{
		startRangedAtk = true;
		enemyGroup->RangedDebugAtk();
	}
	if (ImGui::Button("DeadMeleeEnemy"))
		enemyGroup->DeadMeleeEnemy();
	if (ImGui::Button("DeadRangedReader"))
		enemyGroup->DeadRangedEnemy(true);
	if (ImGui::Button("DeadRanged"))
		enemyGroup->DeadRangedEnemy(false);
	*/
	ImGui::End();
}