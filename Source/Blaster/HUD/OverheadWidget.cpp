// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

void UOverheadWidget::ShowPlayNetRole(APawn* InPawn)
{
	// LocalRole gets the role of the pawn on the machine itself
	// - On the server, all pawns are Authority
	// - On the client, the controlled pawn is Autonomous Proxy and others are Simulated Proxy 
	
	// RemoteRole gets the role of the pawn on the remote machine
	// - On the server, the controlled pawn is Autonomous Proxy and others are Simulated Proxy
	// - On the client, all pawns are Authority


	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;
	switch (RemoteRole)
	{
	case ENetRole::ROLE_Authority:
		Role = FString(TEXT("Authority"));
		break;
	case ENetRole::ROLE_AutonomousProxy:
		Role = FString(TEXT("Autonomous Proxy"));
		break;
	case ENetRole::ROLE_SimulatedProxy:
		Role = FString(TEXT("Simulated Proxy"));
		break;
	case ENetRole::ROLE_None:
		Role = FString(TEXT("None"));
		break;
	}
	FString RemoteRoleString = FString::Printf(TEXT("Remote Role: %s"), *Role);
	SetDisplayText(RemoteRoleString);
}

void UOverheadWidget::NativeDestruct()
{
	RemoveFromParent();
	Super::NativeDestruct();
}
