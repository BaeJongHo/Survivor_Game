// Fill out your copyright notice in the Description page of Project Settings.

#include "Lion.h"
#include "LionAnim.h"

ALion::ALion()
{
	PrimaryActorTick.bCanEverTick = true;

	// 스켈레탈 메시를 얻어온다
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/AfricanAnimalsPack/LionAndLioness/Meshes/SK_Lion_LOD0.SK_Lion_LOD0'"));

	// 스켈레탈 메시가 유효할 경우 메시 적용
	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	// 애니메이션 블루프린트 클래스를 얻어온다
	static ConstructorHelpers::FClassFinder<ULionAnim> AnimAsset(TEXT("AnimBlueprint'/Game/Animal/BPLionAnim.BPLionAnim_C'"));

	// 블루프린트 클래스가 유효할 경우 적용
	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	// 박스 컴포넌트 생성
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	
	// 박스 컴포넌트를 메시의 소켓에 달아준다
	CollisionBox->SetupAttachment(GetMesh(), TEXT("LION_-Spine_Socket"));
	
	// 박스 컴포넌트의 프로파일을 몬스터의 프로파일로 설정한다
	CollisionBox->SetCollisionProfileName(TEXT("Animal"));

	// 일단 임의로 크기를 잡아준 것, 크기는 블루프린트로 수정할 것임
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

