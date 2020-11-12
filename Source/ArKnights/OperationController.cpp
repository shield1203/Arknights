#include "OperationController.h"

AOperationController::AOperationController()
{

}

void AOperationController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void AOperationController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AOperationController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AOperationController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Released, this, &Atest00PlayerController::TouchEnd);
}