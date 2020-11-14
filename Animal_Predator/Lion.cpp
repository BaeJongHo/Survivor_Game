// Fill out your copyright notice in the Description page of Project Settings.

#include "Lion.h"
#include "LionAnim.h"

ALion::ALion()
{
	PrimaryActorTick.bCanEverTick = true;

	// ���̷�Ż �޽ø� ���´�
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AfricanAnimalsPack/LionAndLioness/Meshes/SK_Lion_LOD0.SK_Lion_LOD0'"));

	// ���̷�Ż �޽ð� ��ȿ�� ��� �޽� ����
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	// �ִϸ��̼� �������Ʈ Ŭ������ ���´�
	static ConstructorHelpers::FClassFinder<ULionAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Animal/BPLionAnim.BPLionAnim_C'"));

	// �������Ʈ Ŭ������ ��ȿ�� ��� ����
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	// �ڽ� ������Ʈ ����
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	
	// �ڽ� ������Ʈ�� �޽��� ���Ͽ� �޾��ش�
	CollisionBox->SetupAttachment(GetMesh(), TEXT("LION_-Spine_Socket"));
	
	// �ڽ� ������Ʈ�� ���������� ������ �������Ϸ� �����Ѵ�
	CollisionBox->SetCollisionProfileName(TEXT("Animal"));

	// �ϴ� ���Ƿ� ũ�⸦ ����� ��, ũ��� �������Ʈ�� ������ ����
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	AnimalName = TEXT("Lion");
}

void ALion::BeginPlay()
{
	Super::BeginPlay();

	LionAnim = Cast<ULionAnim>(GetMesh()->GetAnimInstance());
}

void ALion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ALion::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return fDamage;
}

