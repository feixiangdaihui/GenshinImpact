// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenshinImpact/GenshinImpactCharacter.h"
#include "Interface/HealthInterface.h"
#include "GlobalTypes/GlobalTypes.h"
#include "PlayerComponent/EquipmentBarComponent.h"
#include "PlayCharacter.generated.h"

class UHealthComponent;
class UProjectileComponent;
class UBlueComponent;
class UElementComponent;
class UEquipmentBarComponent;
class UAttackPowerComponent;
class ULevelComponent;
struct FCharacterData;
/**
 *
 */
UCLASS()
class GENSHINIMPACT_API APlayCharacter : public AGenshinImpactCharacter, public IHealthInterface
{
    GENERATED_BODY()
	friend class UPlayCharacterAnimation;
public:

    APlayCharacter();
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;
protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	int CharacterIndex;
	//处理输入
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* CastSpellAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* NormalAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeCharacterAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* WearEquipmentAction;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    bool IsAnimForbidden;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
    float Speed;
	virtual void Move(const FInputActionValue& Value);
public:
	//组件
    //血量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHealthComponent> HealthComponent;
	virtual void TakeDamageByValue_Implementation() override;
	virtual void Die_Implementation() override;

	//蓝量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlueComponent> BlueComponent;

	void RecoverBlueByTick();
	
	//攻击力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	TObjectPtr<UAttackPowerComponent> AttackPowerComponent;


	//元素
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Element")
	TObjectPtr<UElementComponent> ElementComponent;
	inline GElement GetElementType();

	//装备栏
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	TObjectPtr<UEquipmentBarComponent> EquipmentBarComponent;
	UFUNCTION(BlueprintCallable)
	void WearEquipment(AEquipment* Equipment);
	UFUNCTION(BlueprintCallable)
	void TakeOffEquipment(EEquipmentType EquipmentType);

	//等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TObjectPtr<ULevelComponent> LevelComponent;
	inline int GetLevel() const;

	UFUNCTION(BlueprintCallable)
	int GetCharacterIndex() const { return CharacterIndex; }
	UFUNCTION(BlueprintCallable)
	void SetCharacterIndex(int Index) { CharacterIndex = Index; }
protected:
	//攻击与技能的输入处理
	virtual void CastSpell();
	virtual void CastSpellEnd();
	virtual void NormalAttack();
	virtual void NormalAttackEnd();
	//捡起装备
	virtual void WearEquipment();

	//普通攻击倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackMode")
	float NormalAttackRate;
	//技能倍率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackMode")
	float CastSpellRate;
	UFUNCTION(BlueprintCallable, Category = "AttackMode")
	virtual void SpawnCastSpell() {}
	UFUNCTION(BlueprintCallable, Category = "AttackMode")
	virtual void SpawnNormalAttack(){}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blue")
	float CastSpellBlueCost;


	//动作处理
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool IsCastingSpell;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	bool IsNormalAttack;

	//攻击判定,是否是计算伤害
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttackMode")
	bool IsJudgeNormalAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp")
	float PickUpDistance;
public:
	//保存游戏相关
	void LoadCharacterData(FCharacterData& );
	FCharacterData SaveCharacterData();
private:
	//切换角色
	void SeqChangeCharacter();
};
