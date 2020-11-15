// Fill out your copyright notice in the Description page of Project Settings.


#include "Zebra.h"
#include "ZebraAnim.h"

AZebra::AZebra()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AfricanAnimalsPack/Zebra/Meshes/SK_Zebra.SK_Zebra'"));

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UZebraAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Animal/BPZebraAnim.BPZebraAnim_C'"));

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetMesh(), TEXT("ZEBRA_-Spine_Socket"));
	CollisionBox->SetCollisionProfileName(TEXT("Animal"));
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AnimalName = TEXT("Zebra");
}

void AZebra::BeginPlay()
{
	Super::BeginPlay();

	ZebraAnim = Cast<UZebraAnim>(GetMesh()->GetAnimInstance());
}

void AZebra::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AZebra::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return fDamage;
}