// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnPoint.h"
#include "AnimalAnim.h"
#include "MainGameInstance.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameFramework/Character.h"
#include "Animal.generated.h"

// ������ ����Ǿ��� �� ȣ��� �Լ��� ����� ��������Ʈ�� �����
DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate)

USTRUCT(Atomic, BlueprintType)
struct FAnimalState
{
	GENERATED_USTRUCT_BODY()

public:
	FAnimalState()
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	fAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float	fArmor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	iHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	iHPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	iMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32	iMPMax;
};

USTRUCT(Atomic, BlueprintType)
struct FAnimalItem
{
	GENERATED_USTRUCT_BODY()

public:
	FAnimalItem()
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FString sItemName;
};

UCLASS()
class SURVIVAL_IN_AFRICA_API AAnimal : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimal();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	ASpawnPoint* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float fTraceRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float fAttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<APatrolPoint*> PatrolPointArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FAnimalState AnimalState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FAnimalItem AnimalItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName AnimalName;

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* AttackBox;

	bool bEndOverlapEnable;

	int32 iMovePoint;
	int32 iMovePointDir;

	bool bAttack;

	FOnAttackEndDelegate OnAttackEnd;
	TArray<FDelegateHandle> AttackEndHandle;

	class UAnimalAnim* AnimalAnim;

public:
	void AddPatrolPoint(APatrolPoint* point);

	int32 GetPatrolPointCount() const
	{
		return PatrolPointArray.Num();
	}

	APatrolPoint* GetPatrolPoint()
	{
		return PatrolPointArray[iMovePoint];
	}

	void NextPatrolPoint()
	{
		iMovePoint += iMovePointDir;

		if (iMovePoint == PatrolPointArray.Num())
		{
			iMovePointDir = -1;
			iMovePoint = PatrolPointArray.Num() - 2;
		}
		else if (iMovePoint == -1)
		{
			iMovePointDir = 1;
			iMovePoint = 0;
		}
	}

public:
	void EnableAttackCollision(bool bEnable);
	void SetEndOverlapEnable(bool bEndOverlap);

public:
	// �浹�� �����ҽÿ� ȣ��Ǵ� ��������Ʈ�� ����ϴ� �Լ�
	UFUNCTION()
	void AttackBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	// �浹�� ����ɽÿ� ȣ��Ǵ� ��������Ʈ�� ����ϴ� �Լ�
	UFUNCTION()
	void AttackEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	template <typename T>
	void AddAttackEndDelegate(T* pObj, void(T::* pFunc)())
	{
		// �ڵ��� �����Ѵ�
		FDelegateHandle handle = OnAttackEnd.AddUObject(pObj, pFunc);

		AttackEndHandle.Add(handle); // �ڵ� �߰�
	}

public:
	float GetTraceRange() const
	{
		return fTraceRange;
	}

	float GetAttackRange() const
	{
		return fAttackRange;
	}

	void Attack()
	{
		bAttack = true;
	}

	bool GetAttack() const
	{
		return bAttack;
	}

public:
	void SetSpawnPoint(ASpawnPoint* Point)
	{
		SpawnPoint = Point;
	}

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	void SetAnimType(EAnimalAnim eAnimType);

public:
	void AttackEnd();
	void Death();
};
