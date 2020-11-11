// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"
#include "InventoryItemData.h"

AAnimal::AAnimal()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = nullptr;

	iMovePoint = 0;
	iMovePointDir = 1;
}

void AAnimal::AddPatrolPoint(APatrolPoint* point)
{
	PatrolPointArray.Add(point);
}

void AAnimal::BeginPlay()
{
	Super::BeginPlay();

	AnimalAnim = Cast<UAnimalAnim>(GetMesh()->GetAnimInstance());

	UMainGameInstance* GameInst = GetGameInstance<UMainGameInstance>();

	const FAnimalInfo* pAnimalInfo = GameInst->FindAnimalInfo(AnimalName);

	if (pAnimalInfo)
	{
		AnimalState.fAttack = pAnimalInfo->Attack;
		AnimalState.fArmor = pAnimalInfo->Armor;
		AnimalState.iHP = pAnimalInfo->HP;
		AnimalState.iHPMax = pAnimalInfo->HPMax;
		AnimalState.iMP = pAnimalInfo->MP;
		AnimalState.iMPMax = pAnimalInfo->MPMax;
		fTraceRange = pAnimalInfo->TraceRange;
		fAttackRange = pAnimalInfo->AttackRange;
	}

	const FAnimalItemInfo* pAnimalItemInfo = GameInst->FindAnimalItemInfo(AnimalName);

	if (pAnimalItemInfo)
	{
		AnimalItem.sItemName = pAnimalItemInfo->ItemName;
	}
}

void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Actor 클래스에 존재하는 언리얼이 제공해주는 데미지 함수
float AAnimal::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	return fDamage;
}

void AAnimal::SetAnimType(EAnimalAnim eAnimType)
{
	if (IsValid(AnimalAnim))
		AnimalAnim->SetAnimType(eAnimType);
}

void AAnimal::AttackEnd()
{
	bAttack = false;

	// 저장된 델리게이트들을 모두 불러온다
	OnAttackEnd.Broadcast();

	// 저장된 델리게이트들을 모두 제거한다
	for (FDelegateHandle& handle : AttackEndHandle)
	{
		OnAttackEnd.Remove(handle);
	}
}

void AAnimal::Death()
{
	if (SpawnPoint)
		SpawnPoint->Respawn();

	Destroy();
}

// 박스 컴포넌트의 충돌을 설정하는 함수
void AAnimal::EnableAttackCollision(bool bEnable)
{
	if (bEnable)
	{
		AttackBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		AttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

// bool 변수를 조작하는 함수
void AAnimal::SetEndOverlapEnable(bool bEndOverlap)
{
	bEndOverlapEnable = bEndOverlap;
}

void AAnimal::AttackBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// 충돌을 빠져나갈 때, 호출될 델리게이트에 적용할 함수
void AAnimal::AttackEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// AttackEndOverlap이 계속 발동되어 설정해놓은 bool 변수
	if (bEndOverlapEnable)
	{
		// 이 변수를 false로 초기화해주고 Attack이 끝나면 노티파이를 이용해 다시 true로 바꾼다
		bEndOverlapEnable = false;

		FDamageEvent DamageEvent;

		// 여기서 OtherActor는 몬스터와 충돌한 객체, 즉 플레이어 객체이다
		float fDamage = OtherActor->TakeDamage(AnimalState.fAttack, DamageEvent, GetController(), this);
	}
}

