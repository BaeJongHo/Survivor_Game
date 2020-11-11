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

// Actor Ŭ������ �����ϴ� �𸮾��� �������ִ� ������ �Լ�
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

	// ����� ��������Ʈ���� ��� �ҷ��´�
	OnAttackEnd.Broadcast();

	// ����� ��������Ʈ���� ��� �����Ѵ�
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

// �ڽ� ������Ʈ�� �浹�� �����ϴ� �Լ�
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

// bool ������ �����ϴ� �Լ�
void AAnimal::SetEndOverlapEnable(bool bEndOverlap)
{
	bEndOverlapEnable = bEndOverlap;
}

void AAnimal::AttackBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	
}

// �浹�� �������� ��, ȣ��� ��������Ʈ�� ������ �Լ�
void AAnimal::AttackEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// AttackEndOverlap�� ��� �ߵ��Ǿ� �����س��� bool ����
	if (bEndOverlapEnable)
	{
		// �� ������ false�� �ʱ�ȭ���ְ� Attack�� ������ ��Ƽ���̸� �̿��� �ٽ� true�� �ٲ۴�
		bEndOverlapEnable = false;

		FDamageEvent DamageEvent;

		// ���⼭ OtherActor�� ���Ϳ� �浹�� ��ü, �� �÷��̾� ��ü�̴�
		float fDamage = OtherActor->TakeDamage(AnimalState.fAttack, DamageEvent, GetController(), this);
	}
}

