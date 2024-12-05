#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerTank)
	{
		float Distance = FVector::Dist(GetActorLocation(), PlayerTank->GetActorLocation());
		if (Distance <= FireRange)
		{
			RotateTurret(PlayerTank->GetActorLocation());
			Fire();
		}
	}
}

