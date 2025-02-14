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

