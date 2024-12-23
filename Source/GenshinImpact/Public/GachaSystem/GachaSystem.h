#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GachaSystem.generated.h"

// ����һ���ṹ������ʾ���Գ�ȡ����Ʒ
USTRUCT(BlueprintType)
struct FGachaItem
{
    GENERATED_BODY()

public:
    // ��Ʒ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
    FString ItemName;

    // ��Ʒ������
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
    FString Description;

    // ��Ʒ��ϡ�жȣ����ڸ��ʼ��㣩
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha")
    int32 Rarity;
};

// ����Gachaϵͳ������
UCLASS(Blueprintable)
class GENSHINIMPACT_API UGachaSystem : public UObject
{
    GENERATED_BODY()

public:
    UGachaSystem();

    // ��ʼ���鿨ϵͳ�����ؿɳ�ȡ����Ʒ
    UFUNCTION(BlueprintCallable, Category = "Gacha")
    void InitializeGacha();

    // ִ��һ�γ鿨
    UFUNCTION(BlueprintCallable, Category = "Gacha")
    FGachaItem DrawGacha();

private:
    // �ɳ�ȡ����Ʒ�б�
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gacha", meta = (AllowPrivateAccess = "true"))
    TArray<FGachaItem> GachaItems;

    int32 TotalWeight;
};
