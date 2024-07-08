// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "inputAction.h"
#include "Logging/LogMacros.h"
#include "StateOfZ/Interfaces/Interactable.h"
#include "StateOfZCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USearchBox;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AStateOfZCharacter : public ACharacter
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
	
	UPROPERTY(EditAnywhere)
		float vaultInterpSpeed = 5.0f;

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
		FVector rayDetectionPoint;

	// UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
	// 	FVector interactionRayPoint;
	UPROPERTY(EditAnywhere, meta=(MakeEditWidget=true))
		float maxInteractRayDistance = 10.0f;

private:
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
	USearchBox* searchBoxOnCurrent;
	AActor* itemBaseOnCurrent;

	bool bIsInteractHeld;
	float interactionStartTime;
	
	void StartInteract();
	void StopInteract();
	
	void LockMovement();
	void UnlockMovement();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Jump Functions */
	virtual void Jump();
	virtual void StopJumping();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	
	/** Called for looking Interact Input */
	void Interact();
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

	virtual void Tick(float DeltaTime);

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

