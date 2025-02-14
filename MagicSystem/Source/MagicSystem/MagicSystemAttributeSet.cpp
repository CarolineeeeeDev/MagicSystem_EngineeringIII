#include "MagicSystemAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UMagicSystemAttributeSet::UMagicSystemAttributeSet()
{

}

void UMagicSystemAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMagicSystemAttributeSet, currentHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMagicSystemAttributeSet, maxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMagicSystemAttributeSet, currentMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMagicSystemAttributeSet, maxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMagicSystemAttributeSet, attackDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMagicSystemAttributeSet, speedMultiplier, COND_None, REPNOTIFY_Always);
}

void UMagicSystemAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	if (Data.EvaluatedData.Attribute == GetcurrentHealthAttribute())
	{
		SetcurrentHealth(FMath::Clamp(GetcurrentHealth(), 0.0f, GetmaxHealth()));
		HealthChangeDelegate.Broadcast(GetcurrentHealth(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetcurrentManaAttribute())
	{
		SetcurrentMana(FMath::Clamp(GetcurrentMana(), 0.0f, GetmaxMana()));
		ManaChangeDelegate.Broadcast(GetcurrentMana(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetattackDamageAttribute())
	{
		SetattackDamage(FMath::Clamp(GetattackDamage(), 0.0f, 100.0f));
		AttackDamageChangeDelegate.Broadcast(GetattackDamage(), Data.EffectSpec.StackCount);
	}
	if (Data.EvaluatedData.Attribute == GetspeedMultiplierAttribute())
	{
		SetspeedMultiplier(FMath::Clamp(GetspeedMultiplier(), 0.1f, 2.0f));
		SpeedMultiplierChangeDelegate.Broadcast(GetspeedMultiplier(), Data.EffectSpec.StackCount);
	}
}

void UMagicSystemAttributeSet::OnRep_currentHealth(const FGameplayAttributeData& oldCurrentHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMagicSystemAttributeSet, currentHealth, oldCurrentHealth);

}

void UMagicSystemAttributeSet::OnRep_maxHealth(const FGameplayAttributeData& oldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMagicSystemAttributeSet, maxHealth, oldMaxHealth);
}

void UMagicSystemAttributeSet::OnRep_currentMana(const FGameplayAttributeData& oldCurrentMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMagicSystemAttributeSet, currentMana, oldCurrentMana);
}

void UMagicSystemAttributeSet::OnRep_maxMana(const FGameplayAttributeData& oldMaxMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMagicSystemAttributeSet, maxMana, oldMaxMana);
}

void UMagicSystemAttributeSet::OnRep_attackDamage(const FGameplayAttributeData& oldAttackDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMagicSystemAttributeSet, attackDamage, oldAttackDamage);
}

void UMagicSystemAttributeSet::OnRep_speedMultiplier(const FGameplayAttributeData& oldSpeedMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMagicSystemAttributeSet, speedMultiplier, oldSpeedMultiplier);
}
