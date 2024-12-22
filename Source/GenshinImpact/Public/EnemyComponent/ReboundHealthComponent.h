#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interface/EnemyHealthInterface.h"
#include "GlobalTypes/GlobalTypes.h"
#include "EnemyComponent/EnemyHealthComponent.h"
#include "ReboundHealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GENSHINIMPACT_API UReboundHealthComponent : public UEnemyHealthComponent 
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UReboundHealthComponent();

protected:

	//反伤比例
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float ReboundRatio;

public:
	virtual void TakeDamageByValue(float DamageAmount, float TimeToBeAttacked = 0.5f) override;
	virtual void TakeDamageByPercent(float DamagePercent, float TimeToBeAttacked = 0.5f) override;
};
