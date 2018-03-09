// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseUnit.generated.h"

UCLASS()
class RTS_API ABaseUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseUnit();

protected:
	virtual void BeginPlay() override;

	float damagePerSecond = 10.;
	TArray<ABaseUnit*> overlappingEnemies;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int factionNumber;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float strength = 200.;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float organization = 1.0;

	void takeDamage(float damageAmount);
	//void ReceiveAnyDamage(float Damage, UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	//void TakeDamage(float DamageAmount, FDamageEvent & DamageEvent, AController * EventInstigator, AActor * DamageCauser);
	void NotifyActorBeginOverlap(AActor* OtherActor);
	void NotifyActorEndOverlap(AActor* OtherActor);

public:	
	virtual void Tick(float DeltaTime) override;

};
