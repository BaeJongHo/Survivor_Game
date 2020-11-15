// Fill out your copyright notice in the Description page of Project Settings.


#include "Deer.h"
#include "DeerAnim.h"

ADeer::ADeer()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AnimalVarietyPack/DeerStagAndDoe/Meshes/SK_DeerDoe.SK_DeerDoe'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UDeerAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Animal/BPDeerAnim.BPDeerAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetMesh(), TEXT("DeerDoe_-Spine_Socket"));
	CollisionBox->SetCollisionProfileName(TEXT("Animal"));
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AnimalName = TEXT("Deer");
}

void ADeer::BeginPlay()
{
	Super::BeginPlay();

	DeerAnim = Cast<UDeerAnim>(GetMesh()->GetAnimInstance());
}

void ADeer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ADeer::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return fDamage;
}