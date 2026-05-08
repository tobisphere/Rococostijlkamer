#pragma once

#include "GameFramework/SaveGame.h"
#include "SaveToken.generated.h"

/**
* 
*/
UCLASS()
class CHAUNCEYCLIENT_API USaveToken : public USaveGame
{
	GENERATED_BODY()

	public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString Token;
};