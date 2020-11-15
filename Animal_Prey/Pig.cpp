// Fill out your copyright notice in the Description page of Project Settings.


#include "Pig.h"
#include "PigAnim.h"

APig::APig()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/Pig/Meshes/SK_Pig.SK_Pig'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UPigAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Animal/BPPigAnim.BPPigAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetMesh(), TEXT("PIG_-Spine_Socket"));
	CollisionBox->SetCollisionProfileName(TEXT("Animal"));
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AnimalName = TEXT("Pig");
}

void APig::BeginPlay()
{
	Super::BeginPlay();

	PigAnim = Cast<UPigAnim>(GetMesh()->GetAnimInstance());
}

void APig::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float APig::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return fDamage;
}

