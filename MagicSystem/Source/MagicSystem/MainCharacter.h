#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "MainCharacter.generated.h"

class UMagicSystemAbilityComponent;
class UMagicSystemAttributeSet;

UCLASS()
class MAGICSYSTEM_API AMainCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS" )
	UMagicSystemAbilityComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS")
	const UMagicSystemAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> InitialAbilities;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION()
	virtual void OnHealthChangedNative(float health, int32 staticCounut);
	UFUNCTION()
	virtual void OnManaChangedNative(float mana, int32 staticCounut);
	UFUNCTION()
	virtual void OnAttackDamageChangedNative(float attackDamage, int32 staticCounut);
	UFUNCTION()
	virtual void OnSpeedMultiplierChangedNative(float speedMultiplier, int32 staticCounut);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnHealthChanged(float health, int32 staticCounut);
	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnManaChanged(float mana, int32 staticCounut);
	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnAttackDamageChanged(float attackDamage, int32 staticCounut);
	UFUNCTION(BlueprintImplementableEvent, Category = "GAS")
	void OnSpeedMultiplierChanged(float speedMultiplier, int32 staticCounut);


	UFUNCTION(BlueprintCallable, Category = "GAS")
	void InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel);
	
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void InitializeAbilities(TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGet, int32 AbilityLevel);

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void RemoveAbilityWithTags(FGameplayTagContainer tagContainer);
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void ChangeAbilityLevelWithTags(FGameplayTagContainer tagContainer, int32 newAbilityLevel);
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void CancelAbilityWithTags(FGameplayTagContainer tagContainer);

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(Blueprintpure, Category = "GAS")
	void GetCurrentHealthValues(float& currentHealth, float& MaxHealth);
	UFUNCTION(Blueprintpure, Category = "GAS")
	void GetCurrentManaValues(float& currentMana, float& MaxMana);
	UFUNCTION(Blueprintpure, Category = "GAS")
	void GetCurrentAttackDamageValues(float& currentAttackDamage);
	UFUNCTION(Blueprintpure, Category = "GAS")
	void GetCurrentSpeedMultiplierValues(float& currentSpeedMultiplier);

	UFUNCTION(BlueprintCallable, Category = "GAS")
	void AddLoseGameplayTag(FGameplayTag tagToAdd);
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void RemoveLoseGameplayTag(FGameplayTag tagToRemove);
};
