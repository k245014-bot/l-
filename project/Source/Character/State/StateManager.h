#pragma once
#include "../../Common/Object/objectBase.h"

class StateBase;

class StateManager :public ObjectBase
{
public:
	StateManager();
	~StateManager();

	void Update()override; 
	void Draw()override;

	void ChangeState(StateBase* _state);
	//void LoadState(StateBase& _state);
	//template <typename T>
	//std::shared_ptr<T>LoadState()
	//{
	//	/*stateData->push_back(T);*/
	//}
	
private:
	//std::unique_ptr<StateBase> currentState;
	StateBase* currentState;
	std::vector<StateBase>* stateData;
};