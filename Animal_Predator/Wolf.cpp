// Fill out your copyright notice in the Description page of Project Settings.


#include "Wolf.h"
#include "WolfAnim.h"

AWolf::AWolf()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/Wolf/Meshes/SK_Wolf.SK_Wolf'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UWolfAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Animal/BPWolfAnim.BPWolfAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetMesh(), TEXT("Wolf_-Spine_Socket"));
	CollisionBox->SetCollisionProfileName(TEXT("Animal"));
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AnimalName = TEXT("Wolf");
}

void AWolf::BeginPlay()
{
	Super::BeginPlay();

	WolfAnim = Cast<UWolfAnim>(GetMesh()->GetAnimInstance());
}

void AWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AWolf::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return fDamage;
}


