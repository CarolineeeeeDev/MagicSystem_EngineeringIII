#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffect.h"
#include "MagicSystemAbilityComponent.h"
#include "MagicSystemAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


struct FGameplayEffectModCallbackData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttrChangeDelegate, float, Attr, int32, stackCount);

UCLASS()
class MAGICSYSTEM_API UMagicSystemAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMagicSystemAttributeSet();


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_currentHealth)
	FGameplayAttributeData currentHealth;
	ATTRIBUTE_ACCESSORS(UMagicSystemAttributeSet, currentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_maxHealth)
	FGameplayAttributeData maxHealth;
	ATTRIBUTE_ACCESSORS(UMagicSystemAttributeSet, maxHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_currentMana)
	FGameplayAttributeData currentMana;
	ATTRIBUTE_ACCESSORS(UMagicSystemAttributeSet, currentMana);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_maxMana)
	FGameplayAttributeData maxMana;
	ATTRIBUTE_ACCESSORS(UMagicSystemAttributeSet, maxMana);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_attackDamage)
	FGameplayAttributeData attackDamage;
	ATTRIBUTE_ACCESSORS(UMagicSystemAttributeSet, attackDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_speedMultiplier)
	FGameplayAttributeData speedMultiplier;
	ATTRIBUTE_ACCESSORS(UMagicSystemAttributeSet, speedMultiplier);

	FAttrChangeDelegate HealthChangeDelegate;
	FAttrChangeDelegate ManaChangeDelegate;
	FAttrChangeDelegate AttackDamageChangeDelegate;
	FAttrChangeDelegate SpeedMultiplierChangeDelegate;

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	
	UFUNCTION()
	virtual void OnRep_currentHealth(const FGameplayAttributeData& oldCurrentHealth);
	UFUNCTION()
	virtual void OnRep_maxHealth(const FGameplayAttributeData& oldMaxHealth);
	UFUNCTION()
	virtual void OnRep_currentMana(const FGameplayAttributeData& oldCurrentMana);
	UFUNCTION()
	virtual void OnRep_maxMana(const FGameplayAttributeData& oldMaxMana);
	UFUNCTION()
	virtual void OnRep_attackDamage(const FGameplayAttributeData& oldAttackDamage);
	UFUNCTION()
	virtual void OnRep_speedMultiplier(const FGameplayAttributeData& oldSpeedMultiplier);
};
