// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 角色数据结构
 */
USTRUCT(BlueprintType)
struct FCharacterData
{
    GENERATED_BODY()
public:



    // 当前血量
    float CurrentHealth;
    //当前蓝量
	float CurrentBlue;
	//当前经验
	float CurrentExperience;
	//当前等级
	int CurrentLevel;
	
    //装备
    TArray<FString> EquipmentBarClass;








};

/**
 * 自定义游戏实例类
 * 用于管理游戏生命周期内的角色数据，包括保存、加载和动态更新
 */
UCLASS()
class GENSHINIMPACT_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:
    // 用于存储所有角色数据的 TMap，键为角色名称
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TMap<FString, FCharacterData> CharacterDataMap;

    /**
     * 保存所有角色数据到文件
     */
    void SaveDataToFile();

    /**
     * 从文件加载所有角色数据
     */
    void LoadDataFromFile();

    /**
     * 保存单个角色数据
     * @param CharacterKey - 角色标识
     * @param Data - 要保存的角色数据
     */
    void SaveCharacterData(const FString& CharacterKey, const FCharacterData& Data);

    /**
     * 获取单个角色数据
     * @param CharacterKey - 角色标识
     * @param OutData - 输出的角色数据
     * @return 是否成功获取
     */
    bool GetCharacterData(const FString& CharacterKey, FCharacterData& OutData) const;

    /**
     * 获取保存文件路径
     * @return 保存文件的完整路径
     */
    FString GetSaveFilePath() const;

    /**
     * 游戏实例初始化方法
     * 在游戏启动时调用，用于加载角色数据
     */
    virtual void Init() override;

    /**
     * 游戏实例销毁方法
     * 在游戏关闭时调用，用于保存角色数据
     */
    virtual void Shutdown() override;
};
