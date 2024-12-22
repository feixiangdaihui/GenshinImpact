#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "CPP_InventoryComponent.generated.h"

// Struct to represent items in the inventory (based on your ItemStruct)
USTRUCT(BlueprintType)
struct FItemStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FName Name; // Item name

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool isStackable; // Can the item stack?

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UTexture2D* Image; // Item image

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int32 MaxStackSize; // Maximum stack size

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool isConsumable; // Can the item be consumed?

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    float ChangeData; // Effect when used (e.g., health restored)

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Description; // Description text

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    UObject* Class; // Blueprint class reference

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Attribute; // Item attribute

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    FString Category; // Item category

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool HasEntity; // have a physical entity?

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    bool NeedToPick; // need to pick it up?

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    float BlueOrHealth; //  add health or blue

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int Quantity;  // Number of Items
};

// Inventory component class
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GENSHINIMPACT_API UCPP_InventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCPP_InventoryComponent();

protected:
    virtual void BeginPlay() override;

public:
    // Variables (based on your blueprint variables, with a prefix added)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    int32 CPP_NumberOfSlots; // Total slots in the inventory

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    TArray<FItemStruct> CPP_Inventory; // Array of item slots

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
    UUserWidget* CPP_WBP_Inventory; // Inventory UI widget reference

    // Functions (based on your blueprint functions, with a prefix added)
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_ToggleInventoryWidget();

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    bool CPP_AddSlotToInventory(const FItemStruct& SlotStruct);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_CreateStack(const FItemStruct& AddSlot);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_AddToStack(const FItemStruct& SlotStruct, int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void CPP_UpdateInventory();
};
