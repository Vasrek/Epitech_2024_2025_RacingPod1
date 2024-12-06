#include "TankGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATankGameMode::ActorDied(AActor* DeadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ActorDied"));
	if (DeadActor == Tank)
	{
		if (Tank->GetTankPlayerController())
		{
			Tank->DisableInput(Tank->GetTankPlayerController());
			Tank->GetTankPlayerController()->bShowMouseCursor = false;
		}
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}
