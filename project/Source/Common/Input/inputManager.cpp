#include "inputManager.h"

InputManager::InputManager() 
{
	SetMousePoint(MOUSE_OFFSET_X, MOUSE_OFFSET_Y);
	isCheckkey = false;
	keyCounter = 0;

	if (GetJoypadNum() != 0)
		isController = true;
	else
		isController = false;

	mouseMoveX = 0;
	mouseMoveY = 0;

	restraint = RESTAINT;

	min = VECTOR2(0, 0);
	max = VECTOR2(MOUSE_OFFSET_X * 2 - 1, MOUSE_OFFSET_Y * 2);

	mouseCopy = VECTOR2(MOUSE_OFFSET_X, MOUSE_OFFSET_Y);

	mouseControlOn = false;
}

InputManager::~InputManager()
{

}

void InputManager::Update()
{
	if (isController)
		ControllerMove();	//コントローラーのとき
	else  
		KeyBoardMove();		//キーボードのとき
}

void InputManager::ControllerMove()
{
	GetJoypadXInputState(DX_INPUT_PAD1, &controller);

	VECTOR3 InVecL = Normalize(VECTOR3(controller.ThumbLX, controller.ThumbLY, 0));
	VECTOR3 InVecR = Normalize(VECTOR3(controller.ThumbRX, controller.ThumbRY, 0));

	isKey.stickLX = InVecL.x;
	isKey.stickLY = InVecL.y;
	isKey.sickRX = InVecR.x;
	isKey.sickRY = InVecR.y;

	if (controller.Buttons[XINPUT_BUTTON_B] && !isCheckkey)//攻撃ボタン
		isKey.isAtk = CheckKey();
	else
		isKey.isAtk = KeyCoolTime();
}

void InputManager::MouseControlOn()
{
	if(!mouseControlOn)
		mouseControlOn = true;
	else
		mouseControlOn = false;

	isCheckkey = false;
}

void InputManager::KeyBoardMove()//updata
{
	//上下移動
	if (CheckHitKey(KEY_INPUT_W))
		isKey.stickLY = 1;
	else if (CheckHitKey(KEY_INPUT_S))
		isKey.stickLY = -1;
	else
		isKey.stickLY = 0;

	//左右移動
	if (CheckHitKey(KEY_INPUT_D))
		isKey.stickLX = 1;
	else if (CheckHitKey(KEY_INPUT_A))
		isKey.stickLX = -1;
	else
		isKey.stickLX = 0;

	if (CheckHitKey(KEY_INPUT_P) != 0)
	{
		if (!isCheckkey)
			return;
		MouseControlOn();
	}
	else
		isCheckkey = true;

	// マウスポインタの位置を取得する
	GetMousePoint(&mouseX, &mouseY);

	//画面の中心から動いていた分だけマウスが移動したことになる。
	mouseMoveX = mouseX - (int)mouseCopy.x;
	mouseMoveY = mouseY - (int)mouseCopy.y;

	if (mouseControlOn)
	{
		SetMouseDispFlag(false);

		 //マウスポインタの位置を画面中央に設定する
		if (mouseX <= (int)min.x || mouseX >= (int)max.x || mouseY <= (int)min.y || mouseY >= (int)max.y)
		{
			SetMousePoint(MOUSE_OFFSET_X, MOUSE_OFFSET_Y);
			mouseCopy = VECTOR2(MOUSE_OFFSET_X, MOUSE_OFFSET_Y);
		}
		else
			mouseCopy = VECTOR2((float)mouseX, (float)mouseY);
	}
	else
		SetMouseDispFlag(true);

	//マウスの移動量を格納する。そのまま入れるとハイセンシ(感度が良）すぎるので割った数値を入れる
	isKey.sickRX = (float)mouseMoveX / restraint;
	isKey.sickRY = (float)mouseMoveY / restraint;

	//攻撃ボタン
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && !isCheckkey)
		isKey.isAtk = CheckKey();
	else
		isKey.isAtk = KeyCoolTime();

	//左クリックの判定
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) && mouseControlOn)
		isKey.isLeftClick = true;
	else
		isKey.isLeftClick = false;

	//右クリックの判定
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) && mouseControlOn)
		isKey.isRightClick = true;
	else
		isKey.isRightClick = false;
}

bool InputManager::CheckKey()
{
	isCheckkey = true;
	return true;
}

VECTOR3 InputManager::Normalize(VECTOR3 vec)
{
	if (vec.Size() >= 6000)
		if (vec.Size() >= 32767) //最大まで倒している
			return vec.Normalize();
		else
			return vec / vec.Size();
	else// 入力がないとみなす
		return VZero;
}

bool InputManager::KeyCoolTime()
{
	if (!isCheckkey)
		return false;

	keyCounter++;
	if (keyCounter >= KEYCOOLTIME)
	{
		isCheckkey = false;
		keyCounter = 0;
	}
	return false;
}