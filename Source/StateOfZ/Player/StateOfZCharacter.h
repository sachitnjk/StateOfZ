// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "inputAction.h"
#include "Logging/LogMacros.h"
#include "Blueprint/UserWidget.h"
#include "StateOfZ/Interfaces/Interactable.h"
#include "StateOfZ/Inventory/ItemBase.h"
#include "StateOfZ/Inventory/PlayerHUD.h"
#include "StateOfZCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USearchBox;
class UPlayerInventory;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHoverChanged, bool, bIsHovering);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSearchingChanged, bool, bIsSearching);

UCLASS(config=Game)
class AStateOfZCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

public:
	AStateOfZCharacter();

	void AddToPlayerInventory(AItemBase* Item);

	//Event
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnHoverChanged OnHoverChanged;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSearchingChanged OnSearchingChanged;
	
	UPROPERTY()
	class UPlayerHUD* PlayerHUD;
	
	UPROPERTY(EditAnywhere)
		float vaultInterpSpeed = 5.0f;

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
		FVector rayDetectionPoint;

	// UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
	// 	FVector interactionRayPoint;
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
		float maxInteractRayDistance = 10.0f;

	//Team Id interface sutff
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int IdOfTeam = 0;
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

private:

	
	UPROPERTY(EditAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPlayerHUD> PlayerHUDClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UPlayerInventory* PlayerInventoryComponent;
	
	bool bIsJumping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = true))
	float VaultCheckForwardRayLength = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = true))
	float MaxVaultHight = 145.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = true))
	float VaultForwardOffest = 55.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = true))
	float VaultFenceForwardOffest = 135.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement", meta = (AllowPrivateAccess = true))
	float VaultSurfaceFinderDownRayLength = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (AllowPrivateAccess = true))
	float interactionHoldDuration;

	IInteractable* currentInteractable;
	IInteractable* CachedInteractable;
	bool bIsCachedInteractableSearchBox;
	float interactionStartTime;
	
	void StartInteract();
	void StopInteract();
	
	void LockMovement();
	void UnlockMovement();

protected:
	FGenericTeamId TeamId;
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Jump Functions */
	virtual void Jump();
	virtual void StopJumping();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	/** Called for looking Interact Input */
	void InteractCheck();

	FVector targetVaultPosition;
	FVector vaultOffset;

	void VaultCheck();
	void PerformVault();

	void ClearToVaultCheck(const FVector& vaultLocation, const FCollisionQueryParams& collisionParams);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime);

public:
	bool bIsInteractHeld;
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	float GetInteractProgress();
};

