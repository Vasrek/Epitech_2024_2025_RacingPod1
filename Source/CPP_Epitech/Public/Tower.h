#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class CPP_EPITECH_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	ATank* PlayerTank;
	
	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRange = 300.f;

	UPROPERTY(EditAnywhere, Category = "Fire")
	float FireRate = 2.f;

	FTimerHandle FireRateTimerHandle;
	
	void CheckFireCondition();
	
};