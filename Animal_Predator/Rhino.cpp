// Fill out your copyright notice in the Description page of Project Settings.


#include "Rhino.h"
#include "RhinoAnim.h"

ARhino::ARhino()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AfricanAnimalsPack/Rhinoceros/Meshes/SK_Rhinoceros.SK_Rhinoceros'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<URhinoAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Animal/BPRhinoAnim.BPRhinoAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetMesh(), TEXT("RHINOCEROS_-Spine_Socket"));
	CollisionBox->SetCollisionProfileName(TEXT("Animal"));
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AnimalName = TEXT("Rhino");
}

void ARhino::BeginPlay()
{
	Super::BeginPlay();

	RhinoAnim = Cast<URhinoAnim>(GetMesh()->GetAnimInstance());
}

void ARhino::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ARhino::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return fDamage;
}

