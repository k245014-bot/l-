#pragma once
#include "../Object/objectBase.h"

static const int KEYCOOLTIME = 20;
static const int STICK_MAX = 32767;
static const int MOUSE_OFFSET_X = 872 / 2;
static const int MOUSE_OFFSET_Y = 1280 / 2;
static const int RESTAINT = 40;//抑制

struct KeyPush
{
public:
	float stickLX;
	float stickLY;
	float sickRX;
	float sickRY;

	bool isAtk;				//プレイヤーが攻撃キーを押したとき
	
	bool isLeftClick;		//左クリック時
	bool isRightClick;		//右クリック時
	bool isMouseControlOn;

	KeyPush()
	{
		stickLX = 0;
		stickLY = 0;
		sickRX = 0;
		sickRY = 0;

		isAtk = false;
		isLeftClick = false;
		isRightClick = false;
		isMouseControlOn = false;
	}
};

class InputManager :public ObjectBase
{
public:
	InputManager();
	~InputManager();
	void Update()override;

	//ゲッター
	KeyPush GetKeyPush() { return isKey; }
	//セッター


	void MouseControlOn();
private:
	XINPUT_STATE controller;
	int mouseX, mouseY;

	void KeyBoardMove();			//キーボード操作
	void ControllerMove();			//コントローラー操作
	bool CheckKey();				//ボタンを押したあとの処理
	VECTOR3 Normalize(VECTOR3 vec);
	bool KeyCoolTime();				//ボタンを再度押せるようにする関数

	bool isController;
	bool isCheckkey;				//ボタンが押されているか
	int keyCounter;
	int mouseMoveX;					//カーソルX軸
	int mouseMoveY;					//カーソルY軸
	int restraint;					//抑制

	VECTOR2 min;
	VECTOR2 max;
	VECTOR2 mouseCopy;
	KeyPush isKey;

	bool mouseControlOn;
};
