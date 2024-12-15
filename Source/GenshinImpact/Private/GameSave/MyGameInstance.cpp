
#include "GameSave/MyGameInstance.h"
#include "Misc/FileHelper.h"           // 提供文件操作的实用程序
#include "Misc/Paths.h"                // 用于获取项目路径等
#include "Serialization/JsonSerializer.h" // 用于JSON序列化和反序列化
#include "PlayerController/SumPlayerController.h"

// 获取保存文件路径的方法，统一管理文件路径
FString UMyGameInstance::GetSaveFilePath() const
{
    return FPaths::ProjectSavedDir() + TEXT("CharacterData.json");
}

// 保存角色数据到文件的方法
void UMyGameInstance::SaveDataToFile()
{
    // 获取保存路径
    FString SavePath = GetSaveFilePath();

    // 创建一个 JSON 对象，用于存储所有角色数据
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

    // 遍历存储角色数据的 TMap
	if (CharacterDataMap.Num() == 0)
		UE_LOG(LogTemp, Warning, TEXT("CharacterDataMap is empty"));
    for (auto& Pair : CharacterDataMap)
    {
        // 为每个角色创建一个单独的 JSON 对象
        TSharedPtr<FJsonObject> CharacterJson = MakeShareable(new FJsonObject);
        // 将角色数据存储到 JSON 对象中
		CharacterJson->SetNumberField(TEXT("CurrentHealth"), Pair.Value.CurrentHealth);     // 当前血量
		CharacterJson->SetNumberField(TEXT("CurrentBlue"), Pair.Value.CurrentBlue);     // 当前蓝量
		CharacterJson->SetNumberField(TEXT("CurrentExperience"), Pair.Value.CurrentExperience);     // 当前经验
		CharacterJson->SetNumberField(TEXT("CurrentLevel"), Pair.Value.CurrentLevel);     // 当前等级
		// 装备
        TArray<TSharedPtr<FJsonValue>> EquipmentArray;
        for (const FString& EquipmentClass : Pair.Value.EquipmentBarClass)
        {
            EquipmentArray.Add(MakeShareable(new FJsonValueString(EquipmentClass)));
        }
        CharacterJson->SetArrayField(TEXT("EquipmentClass"), EquipmentArray);
        // 将角色 JSON 对象加入到主 JSON 对象中，键为角色名称
        JsonObject->SetObjectField(Pair.Key, CharacterJson);
    }

    // 将 JSON 对象序列化为字符串
    FString JsonString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
    if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
    {
        // 将 JSON 字符串保存到指定文件中
        FFileHelper::SaveStringToFile(JsonString, *SavePath);
    }
}

// 从文件加载角色数据的方法
void UMyGameInstance::LoadDataFromFile()
{
    // 获取保存路径
    FString SavePath = GetSaveFilePath();
    FString JsonString;

    // 检查文件是否存在并加载内容到字符串中
    if (FFileHelper::LoadFileToString(JsonString, *SavePath))
    {
        // 定义一个 JSON 对象用于解析文件内容
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
        // 反序列化 JSON 字符串到 JSON 对象
        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            // 清空之前的角色数据（防止数据叠加）
            CharacterDataMap.Empty();
            // 遍历 JSON 对象中的键值对
            for (auto& Pair : JsonObject->Values)
            {
                // 将值解析为单个角色的 JSON 对象
                TSharedPtr<FJsonObject> CharacterJson = Pair.Value->AsObject();
                if (CharacterJson.IsValid())
                {
                    FCharacterData Data;
                    // 检查字段并填充到 FCharacterData 结构体中
                    if (CharacterJson->TryGetNumberField(TEXT("CurrentHealth"), Data.CurrentHealth) &&
                        CharacterJson->TryGetNumberField(TEXT("CurrentBlue"), Data.CurrentBlue) &&
                        CharacterJson->TryGetNumberField(TEXT("CurrentExperience"), Data.CurrentExperience) &&
                        CharacterJson->TryGetNumberField(TEXT("CurrentLevel"), Data.CurrentLevel))
					{   
						// 装备
                        const TArray<TSharedPtr<FJsonValue>>* EquipmentArray;
                        if (CharacterJson->TryGetArrayField(TEXT("EquipmentClass"), EquipmentArray))
                        {
                            for (const TSharedPtr<FJsonValue>& EquipmentValue : *EquipmentArray)
                            {
                                FString EquipmentClass;
                                if (EquipmentValue->TryGetString(EquipmentClass))
                                {
                                    Data.EquipmentBarClass.Add(EquipmentClass);
                                }
                            }
                        }
                        // 将角色数据加入到 TMap 中
                        CharacterDataMap.Add(Pair.Key, Data);
                    }
                }

            }

        }
    }
}

// 保存单个角色数据的方法
void UMyGameInstance::SaveCharacterData(const FString& CharacterKey, const FCharacterData& Data)
{
    // 添加或更新角色数据
    CharacterDataMap.Add(CharacterKey, Data);

}

// 获取单个角色数据的方法
bool UMyGameInstance::GetCharacterData(const FString& CharacterKey, FCharacterData& OutData) const
{
    // 检查 TMap 中是否存在对应的键
    if (const FCharacterData* FoundData = CharacterDataMap.Find(CharacterKey))
    {
        OutData = *FoundData;
        return true;
    }
    return false;
}

// 初始化方法，游戏启动时调用
void UMyGameInstance::Init()
{
    Super::Init();

    // 游戏启动时加载保存的数据
    LoadDataFromFile();
}

// 游戏关闭时的清理方法
void UMyGameInstance::Shutdown()
{

    Super::Shutdown();
    SaveDataToFile();
}
