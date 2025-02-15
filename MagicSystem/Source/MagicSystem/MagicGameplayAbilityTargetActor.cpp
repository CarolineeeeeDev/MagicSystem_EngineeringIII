#include "MagicGameplayAbilityTargetActor.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

AMagicGameplayAbilityTargetActor::AMagicGameplayAbilityTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	traceRange = 2000.0f;
	DebugReticle = nullptr;
	bDestroyOnConfirmation = true;
	ShouldProduceTargetDataOnServer = true;
}

void AMagicGameplayAbilityTargetActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	LineTraceHit(hitTraceResults);
	if (DebugReticle)
	{
		if (hitTraceResults.bBlockingHit)
		{
			DebugReticle->SetActorLocation(hitTraceResults.ImpactPoint, false, nullptr, ETeleportType::None);
		}
		else
		{
			DebugReticle->SetActorLocation(hitTraceResults.TraceEnd, false, nullptr, ETeleportType::None);
		}
	}
}

AGameplayAbilityWorldReticle* AMagicGameplayAbilityTargetActor::SpawnReticleActor(FVector Location, FRotator Rotation)
{
	if (ReticleClass)
	{
		if (!DebugReticle)
		{
			AGameplayAbilityWorldReticle* spawnReticleActor = GetWorld()->SpawnActor<AGameplayAbilityWorldReticle>(ReticleClass, Location, Rotation);
			if (spawnReticleActor)
			{
				spawnReticleActor->InitializeReticle(this, PrimaryPC, ReticleParams);
				spawnReticleActor->SetReplicates(false);
				return spawnReticleActor;
			}
		}
		else
		{
			return DebugReticle;
		}
	}
	return nullptr;
}

void AMagicGameplayAbilityTargetActor::DestoryReticleActors()
{
	if (DebugReticle)
	{
		DebugReticle->Destroy();
	}
}

void AMagicGameplayAbilityTargetActor::StartTargeting(UGameplayAbility* ability)
{
	OwningAbility = ability;
	PrimaryPC = Cast<APlayerController>(ability->GetOwningActorFromActorInfo()->GetInstigatorController());
	DebugReticle = SpawnReticleActor(GetActorLocation(), GetActorRotation());
}

void AMagicGameplayAbilityTargetActor::ConfirmTargetingAndContinue()
{
	FHitResult hitResult;
	bool bHitPos = LineTraceHit(hitResult);
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	TargetDataHandle = StartLocation.MakeTargetDataHandleFromHitResult(OwningAbility, hitResult);
	if (TargetDataHandle == nullptr)
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
	DestoryReticleActors();
}

void AMagicGameplayAbilityTargetActor::CancelTargeting()
{
	Super::CancelTargeting();
	DestoryReticleActors();
}

bool AMagicGameplayAbilityTargetActor::LineTraceHit(FHitResult& hitResult)
{
	FVector viewPoint;
	FRotator viewRotation;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* MasterPawn = PrimaryPC->GetPawn();
	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}
	PrimaryPC->GetPlayerViewPoint(viewPoint, viewRotation);

	bool bHitPos = GetWorld()->LineTraceSingleByChannel(
		hitResult,
		viewPoint,
		viewRotation.Vector() * traceRange + viewPoint,
		ECC_Visibility,
		QueryParams);

	return bHitPos;
}
