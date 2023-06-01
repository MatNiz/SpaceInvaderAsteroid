// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProjectile.h"
#include "GameFramework/FloatingPawnMovement.h"

// Sets default values
APlayerProjectile::APlayerProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    RootComponent = StaticMeshComponent;

//    StaticMeshComponent->OnComponentHit.AddDynamic(this, &AMyActor::OnCollisionDetected);
}

// Called when the game starts or when spawned
void APlayerProjectile::BeginPlay()
{
	Super::BeginPlay();

 //   StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnOverlapBegin);

    CurrentTime = 0;
}

void APlayerProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


}

// Called every frame
void APlayerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    Move(DeltaTime);
}

void APlayerProjectile::Move(float DeltaTime)
{
 
    FRotator Rotation = GetActorRotation();
    FVector Location = GetActorLocation();

    const FRotator YawRotation(0, Rotation.Yaw, 0);
    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

    Location += Direction * DeltaTime * ProjectileSpeed;
    SetActorLocation(Location);

    CurrentTime += DeltaTime;

    if (CurrentTime >= ProjectileLifeTime)
    {
        Destroy();
    }


    //    FString FloatString = FString::Printf(TEXT("%.2f, %.2f, %.2f"), Direction.X, Direction.Y, Direction.Z);
//   GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FloatString);

}

/*
void APlayerProjectile::OnCollisionDetected(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Sprawd�, czy zderzaj�cy si� obiekt jest obiektem konkretnej klasy
    if (OtherActor && OtherActor->IsA(AMyOtherActor::StaticClass()))
    {
        Destroy();
    }
}
*/