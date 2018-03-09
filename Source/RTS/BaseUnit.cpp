// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseUnit.h"


// Sets default values
ABaseUnit::ABaseUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (ABaseUnit* enemyUnit : overlappingEnemies)
	{
		enemyUnit->takeDamage(damagePerSecond * DeltaTime);
	}
}

void ABaseUnit::takeDamage(float damageAmount)
{
	strength -= damageAmount * (2 - organization);
	if (strength <= 0)
	{
		for (ABaseUnit* enemyUnit : overlappingEnemies)
		{
			enemyUnit->NotifyActorEndOverlap(this);
			// Remove self from any overlapping lists.
		}
		Destroy();
	}
}

/*
void ABaseUnit::ReceiveAnyDamage(float Damage, UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
/* Doesn't work. *
{
	UE_LOG(LogTemp, Warning, TEXT("TAKING damage"));
}
void ABaseUnit::TakeDamage(float DamageAmount, FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
/* Doesn't work. *
{
	UE_LOG(LogTemp, Warning, TEXT("TAKING damage"));
}
*/

void ABaseUnit::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(ABaseUnit::StaticClass()))
	{
		ABaseUnit* otherUnit;
		otherUnit = Cast<ABaseUnit>(OtherActor);
		if (otherUnit->factionNumber != factionNumber)  // is an enemy of this Unit
		{
			overlappingEnemies.Add(otherUnit);
		}
	}
}

void ABaseUnit::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA(ABaseUnit::StaticClass()))
	{
		ABaseUnit* otherUnit;
		otherUnit = Cast<ABaseUnit>(OtherActor);
		overlappingEnemies.RemoveSingle(otherUnit);
	}
}