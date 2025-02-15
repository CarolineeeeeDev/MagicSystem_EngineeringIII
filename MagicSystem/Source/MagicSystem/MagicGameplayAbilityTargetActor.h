#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "MagicGameplayAbilityTargetActor.generated.h"

UCLASS()
class MAGICSYSTEM_API AMagicGameplayAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	AMagicGameplayAbilityTargetActor();

	virtual void Tick(float DeltaSeconds) override;

	AGameplayAbilityWorldReticle* DebugReticle;

	virtual AGameplayAbilityWorldReticle* SpawnReticleActor(FVector Location, FRotator Rotation);
	virtual void DestoryReticleActors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "GAS")
	float traceRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS")
	FHitResult hitTraceResults;

	virtual void StartTargeting(UGameplayAbility* ability) override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void CancelTargeting() override;
	bool LineTraceHit(FHitResult& hitResult);
};
 