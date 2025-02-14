#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MagicSystemAttributeSet.generated.h"

struct FGameplayEffectModCallbackData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttrChangeDelegate, float, Attr, int32, stackCount);

UCLASS()
class MAGICSYSTEM_API UMagicSystemAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMagicSystemAttributeSet();

	FAttrChangeDelegate HealthChangeDelegate;
	FAttrChangeDelegate ManaChangeDelegate;
	FAttrChangeDelegate AttackDamageChangeDelegate;
	FAttrChangeDelegate SpeedMultiplierChangeDelegate;
};
