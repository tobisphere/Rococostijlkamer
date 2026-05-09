// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ChaunceyWebEditorStyle.h"

class FChaunceyWebEditorCommands : public TCommands<FChaunceyWebEditorCommands>
{
public:

	FChaunceyWebEditorCommands()
		: TCommands<FChaunceyWebEditorCommands>(TEXT("ChaunceyWebEditor"), NSLOCTEXT("Contexts", "ChaunceyWebEditor", "ChaunceyWebEditor Plugin"), NAME_None, FChaunceyWebEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};