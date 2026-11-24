#include "CameraEditor.h"
#include "../../../ImGui/imgui.h"
#include "../../Camera/Camera.h"

CameraEditor::CameraEditor()
{
	camera = FindGameObject<Camera>();
	input = FindGameObject<InputManager>();

	copyPos = camera->GetTransform().position;
}

CameraEditor::~CameraEditor()
{
}

void CameraEditor::Update()
{
	CameraControl();

	camera->SetPosition(copyPos);
	camera->SetRotation(copyRot);
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
	/*ImGui::Text("CameraPosition: X:%f ,Y:%f , Z:%f", Pos.x, Pos.y, Pos.z);
	ImGui::Text("CameraRotation: X:%f ,Y:%f , Z:%f", Rot.x, Rot.y, Rot.z);*/
	
	ImGui::DragFloat("PositionX", &copyPos.x, 3.0f, -100000.0f, 100000.0f, "%.2f");
	ImGui::DragFloat("PositionY", &copyPos.y, 3.0f, -100000.0f, 100000.0f, "%.2f");
	ImGui::DragFloat("PositionZ", &copyPos.z, 3.0f, -100000.0f, 100000.0f, "%.2f");

	ImGui::DragFloat("RotionX", &copyRot.x, 0.005f, -180.0f, 180.0f, "%.2f");
	ImGui::DragFloat("RotionY", &copyRot.y, 0.005f, -180.0f, 180.0f, "%.2f");

	ImGui::End();
}

void CameraEditor::CameraControl()
{
	auto rotation = camera->GetTransform().rotation;

	if (input->GetKeyPush().isLeftClick)
	{
		MATRIX rot = MGetRotY(rotation.y);

		VECTOR3 right = VTransform(VECTOR3(1, 0, 0), rot);

		copyPos -= right * input->GetKeyPush().sickRX * 10;
		copyPos += VECTOR3(0, 1, 0) * input->GetKeyPush().sickRY * 10;
	}
}