#include "MainCharacter.h"
#include "MagicSystemAbilityComponent.h"
#include "MagicSystemAttributeSet.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UMagicSystemAbilityComponent>("ACS Comp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AttributeSet = AbilitySystemComponent->GetSet<UMagicSystemAttributeSet>();
		const_cast<UMagicSystemAttributeSet*>(AttributeSet)->HealthChangeDelegate.AddDynamic(this, AMainCharacter::OnHealthChangedNative);
		const_cast<UMagicSystemAttributeSet*>(AttributeSet)->ManaChangeDelegate.AddDynamic(this, AMainCharacter::OnManaChangedNative);
		const_cast<UMagicSystemAttributeSet*>(AttributeSet)->AttackDamageChangeDelegate.AddDynamic(this, AMainCharacter::OnAttackDamageChangedNative);
		const_cast<UMagicSystemAttributeSet*>(AttributeSet)->SpeedMultiplierChangeDelegate.AddDynamic(this, AMainCharacter::OnSpeedMultiplierChangedNative);
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AMainCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMainCharacter::OnHealthChangedNative(float health, int32 staticCounut)
{
	OnHealthChanged(health, staticCounut);
}

void AMainCharacter::OnManaChangedNative(float mana, int32 staticCounut)
{
	OnManaChanged(mana, staticCounut);
}

void AMainCharacter::OnAttackDamageChangedNative(float attackDamage, int32 staticCounut)
{
	OnAttackDamageChanged(attackDamage, staticCounut);
}

void AMainCharacter::OnSpeedMultiplierChangedNative(float speedMultiplier, int32 staticCounut)
{
	OnSpeedMultiplierChanged(speedMultiplier, staticCounut);
}

void AMainCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> abilityToGet, int32 abilityLevel)
{
	if (HasAuthority && AbilitySystemComponent)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(abilityToGet, abilityLevel, 0));
	}
}

void AMainCharacter::InitializeAbilities(TArray<TSubclassOf<UGameplayAbility>> abilitiesToGet, int32 abilityLevel)
{
	for (TSubclassOf<UGameplayAbility> Abilities : abilitiesToGet)
	{
		InitializeAbility(Abilities, abilityLevel);
	}
}

void AMainCharacter::RemoveAbilityWithTags(FGameplayTagContainer tagContainer)
{
	TArray<FGameplayAbilitySpec*> localAbility;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(tagContainer, localAbility);
	for (FGameplayAbilitySpec* Spec : localAbility)
	{
		AbilitySystemComponent->ClearAbility(Spec->Handle);
	}
}

void AMainCharacter::ChangeAbilityLevelWithTags(FGameplayTagContainer tagContainer, int32 newAbilityLevel)
{
	TArray<FGameplayAbilitySpec*> localAbility;
	AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(tagContainer, localAbility);
	for (FGameplayAbilitySpec* Spec : localAbility)
	{
		Spec->Level = newAbilityLevel;
	}
}

void AMainCharacter::CancelAbilityWithTags(FGameplayTagContainer withTags, FGameplayTagContainer withoutTags)
{
	AbilitySystemComponent->CancelAbilities(&withTags, &withoutTags, nullptr);
}

void AMainCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeAbilities(InitialAbilities, 0);
}

void AMainCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AMainCharacter::GetCurrentHealthValues(float& currentHealth, float& MaxHealth)
{
	if (AttributeSet)
	{
		currentHealth = AttributeSet->GetcurrentHealth();
		MaxHealth = AttributeSet->GetmaxHealth();
	}
}

void AMainCharacter::GetCurrentManaValues(float& currentMana, float& MaxMana)
{
	if (AttributeSet)
	{
		currentMana = AttributeSet->GetcurrentMana();
		MaxMana = AttributeSet->GetmaxMana();
	}
}

void AMainCharacter::GetCurrentAttackDamageValues(float& currentAttackDamage)
{
	if (AttributeSet)
	{
		currentAttackDamage = AttributeSet->GetattackDamage();
	}
}

void AMainCharacter::GetCurrentSpeedMultiplierValues(float& currentSpeedMultiplier)
{
	if (AttributeSet)
	{
		currentSpeedMultiplier = AttributeSet->GetspeedMultiplier();
	}
}

void AMainCharacter::AddLoseGameplayTag(FGameplayTag tagToAdd)
{
	AbilitySystemComponent->AddLooseGameplayTag(tagToAdd);
	AbilitySystemComponent->SetTagMapCount(tagToAdd, 1);
}

void AMainCharacter::RemoveLoseGameplayTag(FGameplayTag tagToRemove)
{
	AbilitySystemComponent->RemoveLooseGameplayTag(tagToRemove);

}
