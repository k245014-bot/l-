#include "StateManager.h"
#include "StateBase.h"

StateManager::StateManager()
{
    currentState = nullptr;
}

StateManager::~StateManager()
{
}

void StateManager::Update()
{
    if (currentState)
        currentState->Update(); //現在の状態を実行
}

void StateManager::Draw()
{
}

void StateManager::ChangeState(StateBase* _state)
{
    //今のステートを終了する
    if (currentState)
        currentState->Finish();

    currentState = nullptr;
   
    //新しいステートに切り替える
    currentState = std::move(_state);

    if (currentState)
        currentState->Start();
}
