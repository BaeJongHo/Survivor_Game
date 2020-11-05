// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSurvivor.h"
#include "SurvivorAnim.h"
#include "Components/WidgetComponent.h"
#include "UISurvivorState.h"
#include "SurvivorController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

APlayerSurvivor::APlayerSurvivor()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	
	//Character1_Head_Socket
	Arm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(Arm);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponBox"));
	WeaponBox->SetupAttachment(GetMesh(), TEXT("Sword_Socket"));
	WeaponBox->SetCollisionProfileName(TEXT("PlayerAttack"));
	WeaponBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));

	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bBeginOverlapEnable = true;

	SurvivorStateComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("SurvivorState"));

	static ConstructorHelpers::FClassFinder<UUserWidget> SurvivorStateClass(TEXT("WidgetBlueprint'/Game/UI/UI_SurvivorState.UI_SurvivorState_C'"));

	if (SurvivorStateClass.Succeeded())
		SurvivorStateComponent->SetWidgetClass(SurvivorStateClass.Class);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetMesh(), TEXT("Character_Spine_Socket"));
	CollisionBox->SetCollisionProfileName(TEXT("Player"));
	CollisionBox->SetBoxExtent(FVector(20.f, 20.f, 20.f));

	MoistureDuration = 0.f;
}

void APlayerSurvivor::BeginPlay()
{
	Super::BeginPlay();
	
	SurvivorAnim = Cast<USurvivorAnim>(GetMesh()->GetAnimInstance());

	// 델리게이트에 생성한 함수 등록
	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &APlayerSurvivor::WeaponBeginOverlap);
	WeaponBox->OnComponentEndOverlap.AddDynamic(this, &APlayerSurvivor::WeaponEndOverlap);

	UMainGameInstance* GameInst = GetGameInstance<UMainGameInstance>();

	const FSurvivorInfo* pSurvivorInfo = GameInst->FindSurvivorInfo(TEXT("Survivor"));

	if (pSurvivorInfo)
	{
		SurvivorState.fAttack = pSurvivorInfo->Attack;
		SurvivorState.fArmor = pSurvivorInfo->Armor;
		SurvivorState.iHP = pSurvivorInfo->HP;
		SurvivorState.iHPMax = pSurvivorInfo->HPMax;
		SurvivorState.iMoisture = pSurvivorInfo->Moisture;
		SurvivorState.iMoistureMax = pSurvivorInfo->MoistureMax;
		SurvivorState.iArrowNum = pSurvivorInfo->ArrowNum;
		SurvivorState.iArrowNumMax = pSurvivorInfo->ArrowNumMax;
	}

	SurvivorStateWidget = Cast<UUISurvivorState>(SurvivorStateComponent->GetUserWidgetObject());

	if (IsValid(SurvivorStateWidget))
	{
		SurvivorStateWidget->SetHP(SurvivorState.iHP / (float)SurvivorState.iHPMax);
		SurvivorStateWidget->SetMoisture(SurvivorState.iMoisture / (float)SurvivorState.iMoistureMax);

		// 위젯을 뷰포트에 띄우는 함수
		SurvivorStateWidget->AddToViewport();
	}
}

void APlayerSurvivor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoistureDuration += DeltaTime;

	// 시간이 지남에 따라 수분 게이지를 낮춰준다
	if (MoistureDuration >= 10.f)
	{
		MoistureDuration = 0;

		SurvivorState.iMoisture -= 10;
		SurvivorStateWidget->SetMoisture(SurvivorState.iMoisture / (float)SurvivorState.iMoistureMax);
		
		SurvivorStateWidget->AddToViewport();
	}
}

void APlayerSurvivor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &APlayerSurvivor::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &APlayerSurvivor::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("RotationZ"), this, &APlayerSurvivor::RotationZ);
	PlayerInputComponent->BindAxis(TEXT("RotationY"), this, &APlayerSurvivor::RotationY);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &APlayerSurvivor::JumpKey);
	PlayerInputComponent->BindAction(TEXT("Normal"), EInputEvent::IE_Pressed, this, &APlayerSurvivor::NormalSwitch);
	PlayerInputComponent->BindAction(TEXT("Sword"), EInputEvent::IE_Pressed, this, &APlayerSurvivor::SwordSwitch);
	PlayerInputComponent->BindAction(TEXT("Bow"), EInputEvent::IE_Pressed, this, &APlayerSurvivor::BowSwitch);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerSurvivor::Attack);

}

float APlayerSurvivor::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float fDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 현재 체력에서 fDamage의 크기만큼 감소시킨다
	SurvivorState.iHP -= (int32)fDamage;

	// 만약 HP가 0보다 작아진다면 Death 모션 적용
	if (SurvivorState.iHP <= 0)
	{
		SurvivorState.iHP = 0;

		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (IsValid(SurvivorAnim))
			SurvivorAnim->SetAnimType(ESurvivorAnim::Death);

		ASurvivorController* pSurvivorController = GetController<ASurvivorController>();

		if (IsValid(pSurvivorController))
		{
			// 플레이어 사망시 게임 종료
			UKismetSystemLibrary::QuitGame(GetWorld(), pSurvivorController, EQuitPreference::Quit, true);
		}
	}

	// 플레이어 HP 게이지 세팅
	if (IsValid(SurvivorStateWidget))
		SurvivorStateWidget->SetHP(SurvivorState.iHP / (float)SurvivorState.iHPMax);

	SurvivorStateWidget->AddToViewport();

	return fDamage;
}

void APlayerSurvivor::MoveFront(float fScale)
{
	// 포워드 벡터를 이용해 앞, 뒤로 이동
	AddMovementInput(GetActorForwardVector(), fScale);

	if (IsValid(SurvivorAnim))
	{
		if (fScale > 0.f)
			SurvivorAnim->SetMoveDir(EDir::Front); // 플레이어의 움직임에 따라 Dir 변수에 값을 적용하는 함수
		else if (fScale < 0.f)
			SurvivorAnim->SetMoveDir(EDir::Back);
	}
}

void APlayerSurvivor::MoveSide(float fScale)
{
	// 라이트 벡터를 이용해 오른쪽, 왼쪽으로 이동
	AddMovementInput(GetActorRightVector(), fScale);

	if (IsValid(SurvivorAnim))
	{
		if (fScale > 0.f)
			SurvivorAnim->SetMoveDir(EDir::Right);
		else if (fScale < 0.f)
			SurvivorAnim->SetMoveDir(EDir::Left);
	}
}

void APlayerSurvivor::RotationZ(float fScale)
{
	AddControllerYawInput(fScale);
}

void APlayerSurvivor::RotationY(float fScale)
{
	AddControllerPitchInput(fScale);
}

void APlayerSurvivor::JumpKey()
{
	if (IsValid(SurvivorAnim))
	{
		SurvivorAnim->Jump();
	}

	Jump();
}

void APlayerSurvivor::Attack()
{
	if (IsValid(SurvivorAnim))
	{
		SurvivorAnim->Attack();
	}
}

void APlayerSurvivor::NormalSwitch()
{
	if (IsValid(SurvivorAnim))
	{
		SurvivorAnim->SetState(EState::Normal);
	}
}

void APlayerSurvivor::SwordSwitch()
{
	if (IsValid(SurvivorAnim))
	{
		SurvivorAnim->SetState(EState::Sword);
	}
}

void APlayerSurvivor::BowSwitch()
{
	if (IsValid(SurvivorAnim))
	{
		SurvivorAnim->SetState(EState::Bow);
	}
}

void APlayerSurvivor::EnableWeaponCollision(bool bEnable)
{
	if (bEnable)
	{
		WeaponBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APlayerSurvivor::SetBeginOverlapEnable(bool bBeginOverlap)
{
	bBeginOverlapEnable = bBeginOverlap;
}

void APlayerSurvivor::WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// WeaponBeginOverlap이 계속 발동되어 설정해놓은 bool 변수
	if (bBeginOverlapEnable)
	{
		// 이 변수를 false로 초기화해주고 Attack이 끝나면 노티파이를 이용해 다시 true로 바꾼다
		bBeginOverlapEnable = false;
		
		FDamageEvent DamageEvent;

		// 여기서 OtherActor는 플레이어와 충돌한 객체, 즉 몬스터 객체이다
		float fDamage = OtherActor->TakeDamage(SurvivorState.fAttack, DamageEvent, GetController(), this);
	}
}

void APlayerSurvivor::WeaponEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}