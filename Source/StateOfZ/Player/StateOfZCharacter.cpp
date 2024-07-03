// Copyright Epic Games, Inc. All Rights Reserved.

#include "StateOfZCharacter.h"

#include "AITestsCommon.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "StateOfZ/SearchBox.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AStateOfZCharacter

AStateOfZCharacter::AStateOfZCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	bIsJumping = false;
}

void AStateOfZCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void AStateOfZCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InteractCheck();
	VaultCheck();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AStateOfZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AStateOfZCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AStateOfZCharacter::Look);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AStateOfZCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AStateOfZCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AStateOfZCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AStateOfZCharacter::InteractCheck()
{
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);

	FHitResult hitResult;
	//FVector interactionRayPoint = FollowCamera->GetComponentLocation();
	FVector interactionRayPoint = GetActorLocation();
	FVector interactionRayEnd = interactionRayPoint + (FollowCamera->GetForwardVector() * maxInteractRayDistance);
	
	bool bCanInteract = GetWorld()->LineTraceSingleByChannel(hitResult, interactionRayPoint, interactionRayEnd, ECC_Visibility, collisionParams);
	// DrawDebugLine(GetWorld(), interactionRayPoint, interactionRayEnd, FColor::Yellow, false, 5, 0, 1);
	
	if(bCanInteract)
	{
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		if(hitComponent && hitComponent->IsA(USearchBox::StaticClass())/**&& hitActor inplements interactable interface*/)
		{
			if(currentInteractable == hitComponent)
			{
				return;
			}
			currentInteractable = hitComponent;
			
			searchBoxOnCurrent = Cast<USearchBox>(currentInteractable);
			if(searchBoxOnCurrent)
			{
				searchBoxOnCurrent->OnHover();
			}
			// UE_LOG(LogTemplateCharacter, Log, TEXT("current Interactable Actor Set: %s"), *hitActor->GetName());
		}
		else
		{
			currentInteractable = nullptr;
			return;
		}
	}
	else
	{
		currentInteractable = nullptr;
	}
}


void AStateOfZCharacter::Interact()
{
	if(currentInteractable)
	{
		searchBoxOnCurrent = Cast<USearchBox>(currentInteractable);
		
		if(searchBoxOnCurrent != nullptr)
		{
			searchBoxOnCurrent->OnInteract();
			// UE_LOG(LogTemplateCharacter, Log, TEXT("Interact triggered"));
		}
	}
}

void AStateOfZCharacter::Jump()
{
	Super::Jump();
	bIsJumping = true;
}

void AStateOfZCharacter::StopJumping()
{
	Super::StopJumping();
	bIsJumping = false;
}

void AStateOfZCharacter::VaultCheck()
{
	if (!GetCharacterMovement()->IsMovingOnGround() && bIsJumping)
	{
		PerformVault();
	}
}

void AStateOfZCharacter::PerformVault()
{
	if (bIsJumping)
	{
		FVector rayStart = GetActorLocation() + rayDetectionPoint;
		FVector rayEnd = rayStart + (GetActorForwardVector() * VaultCheckForwardRayLength);

		FHitResult hitResult;
		FCollisionQueryParams collisionParams;
		collisionParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, rayStart, rayEnd, ECC_Visibility, collisionParams);
		DrawDebugLine(GetWorld(), rayStart, rayEnd, FColor::Green, false, 1, 0, 1);

		if (bHit)
		{
			FVector vaultLocation;

			if (hitResult.GetActor()->ActorHasTag("Tag_Fence"))
			{
				UE_LOG(LogTemplateCharacter, Log, TEXT("fence detected, tryng to vault"));

				vaultOffset = (GetActorForwardVector() * VaultFenceForwardOffest);

				vaultLocation = hitResult.ImpactPoint + vaultOffset;

				DrawDebugSphere(GetWorld(), vaultLocation, 30.0f, 12, FColor::Red, false, 5.0f);
			}
			else
			{
				UE_LOG(LogTemplateCharacter, Log, TEXT("going here"));

				vaultOffset = (GetActorForwardVector() * VaultForwardOffest) + FVector(0.0f, 0.0f, MaxVaultHight);
				vaultLocation = hitResult.ImpactPoint + vaultOffset;
			}

			ClearToVaultCheck(vaultLocation, collisionParams);
		}
	}
}

void AStateOfZCharacter::ClearToVaultCheck(const FVector& vaultLocation, const FCollisionQueryParams& collisionParams)
{
	FHitResult vaultCheckHit;
	bool bClearToVault = !GetWorld()->SweepSingleByChannel(vaultCheckHit, vaultLocation, vaultLocation, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeCapsule(GetCapsuleComponent()->GetScaledCapsuleRadius(), GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		collisionParams);
	DrawDebugCapsule(GetWorld(), vaultLocation, GetCapsuleComponent()->GetScaledCapsuleHalfHeight(), GetCapsuleComponent()->GetScaledCapsuleRadius(), FQuat::Identity, FColor::Blue, false, 1, 0, 1);

	if (bClearToVault)
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("clear to vault"));

		FVector downRayStart = vaultLocation;
		FVector downRayEnd = vaultLocation - FVector(0.0f, 0.0f,VaultSurfaceFinderDownRayLength);

		FHitResult downRayHitResult;
		bool bDownHit = GetWorld()->LineTraceSingleByChannel(downRayHitResult, downRayStart, downRayEnd, ECC_Visibility, collisionParams);
		DrawDebugLine(GetWorld(), downRayStart, downRayEnd, FColor::Yellow, false, 1, 0, 1);

		if(bDownHit)
		{
			FVector finalVaultLocation = downRayHitResult.ImpactPoint;
			UE_LOG(LogTemplateCharacter, Log, TEXT("Downward ray hit surface, setting final vault location"));

			targetVaultPosition = finalVaultLocation;
		}
		else
		{
			targetVaultPosition = vaultLocation;
		}
		bIsJumping = false;

		// Getting the offset of the mesh as pivot of the BP will be at center and this offset need to be added back (Hack)
		targetVaultPosition.Z += (GetMesh()->GetRelativeLocation().Z * -1.0f);
		
		SetActorLocation(targetVaultPosition); 
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Log, TEXT("Location not clear to vault"));
	}
}