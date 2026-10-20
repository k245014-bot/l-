#include "CameraEditor.h"
#include "../../../ImGui/imgui.h"
#include "../../Camera/Camera.h"

CameraEditor::CameraEditor()
{
	camera = FindGameObject<Camera>();
	input = FindGameObject<InputManager>();
}

CameraEditor::~CameraEditor()
{
}

void CameraEditor::Update()
{
	CameraControl();
}

void CameraEditor::Draw()
{
	ImGuiDraw();
}

void CameraEditor::ImGuiDraw()
{
	ImGui::Begin("CameraEditor");
	const VECTOR3 Pos = camera->GetTransform().position;
	const VECTOR3 Rot = camera->GetTransform().rotation;
	ImGui::Text("CameraPosition: X:%f ,Y:%f , Z:%f", Pos.x, Pos.y, Pos.z);
	ImGui::Text("CameraRotation: X:%f ,Y:%f , Z:%f", Rot.x, Rot.y, Rot.z);

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

void CameraEditor::CameraControl()
{
	//if (input->GetKeyPush().sickLY)
	camera->NormalMove(-input->GetKeyPush().sickLY);
	camera->Move(VECTOR3(1, 0, 0), input->GetKeyPush().sickLX);
}
