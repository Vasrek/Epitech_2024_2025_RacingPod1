#include "BasePawn.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

ABasePawn::ABasePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Construct box component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	RootComponent = BoxComp;

	// construct base mesh
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base mesh"));
	BaseMesh->SetupAttachment(BoxComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		LookAtRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this),
		InterpSpeed));
}

void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();
	FVector Scale = ProjectileScale;
	FTransform SpawnProjectileTransform(ProjectileSpawnPointRotation, ProjectileSpawnPointLocation, Scale);

	if (ProjectileClass != nullptr)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnProjectileTransform);
		Projectile->SetOwner(this);
		
	}
	

	// DrawDebugSphere(
	// 	GetWorld(),
	// 	ProjectileSpawnPointLocation,
	// 	25.f,
	// 	12,
	// 	FColor::Red,
	// 	false,
	// 	3.f
	// );

	
}

void ABasePawn::HandleDestruction()
{
	UE_LOG(LogTemp, Warning, TEXT("HandleDestruction"));
	// VFX SFX
	Destroy();
	
}

