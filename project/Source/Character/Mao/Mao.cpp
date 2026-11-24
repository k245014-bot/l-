#include "Mao.h"
#include "../../../ImGui/imgui.h"
#include "../State/StateManager.h"

Mao::Mao()
{
	LoadModel(fileName);
	data.position = VECTOR3(0,90,-6000);
	data.scale = VECTOR3(1.3f, 1.3f, 1.3f);

	animation			= new AnimationManager(hModel);
	state				= new StateManager;
	stateData.dance		= new MaoDanceState();
	stateData.danceAtk	= new MaoDanceAtkState();
	
	LoadAnim(animData.dance, "mao/Motion/Dance.mv1");
	LoadAnim(animData.attack, "mao/Motion/Attack.mv1");

	state->ChangeState(stateData.dance);
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
	ImGui::Begin("MaoUIDraw");

	if (ImGui::Button("Idel"))
		animation->Play(100, animData.idle, 20.0f, true);
	if (ImGui::Button("DanceAnim"))
		state->ChangeState(stateData.dance);
	if (ImGui::Button("AtkAnim"))
		state->ChangeState(stateData.danceAtk);
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