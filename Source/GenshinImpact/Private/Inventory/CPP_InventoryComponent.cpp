#include "Inventory/CPP_InventoryComponent.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"

UCPP_InventoryComponent::UCPP_InventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false; // Disable ticking
    CPP_NumberOfSlots = 20; // Default slot count
}

void UCPP_InventoryComponent::BeginPlay()
{
   UActorComponent::BeginPlay();
}

// Show or hide inventory UI
void UCPP_InventoryComponent::CPP_ToggleInventoryWidget()
{
    if (CPP_WBP_Inventory && CPP_WBP_Inventory->IsInViewport())
    {
        CPP_WBP_Inventory->RemoveFromParent(); // Hide UI
    }
    else
    {
        if (!CPP_WBP_Inventory)
        {
            CPP_WBP_Inventory = CreateWidget<UUserWidget>(GetWorld());
        }

        if (CPP_WBP_Inventory)
        {
            CPP_WBP_Inventory->AddToViewport(); // Show UI

            APlayerController* PC = GetWorld()->GetFirstPlayerController();
            if (PC)
            {
                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(CPP_WBP_Inventory->TakeWidget());
                PC->SetInputMode(InputMode);
                PC->bShowMouseCursor = true;
            }
        }
    }
}

// Add a new item slot to the inventory
bool UCPP_InventoryComponent::CPP_AddSlotToInventory(const FItemStruct& SlotStruct)
{
    int32 PartialStackIndex = -1;

    for (int32 i = 0; i < CPP_Inventory.Num(); ++i)
    {
        if (CPP_Inventory[i].Name == SlotStruct.Name && CPP_Inventory[i].isStackable && CPP_Inventory[i].MaxStackSize > CPP_Inventory[i].Quantity)
        {
            PartialStackIndex = i;
            break;
        }
    }

    if (PartialStackIndex != -1)
    {
        CPP_AddToStack(SlotStruct, PartialStackIndex); 
        return true;
    }
    else
    {
        CPP_CreateStack(SlotStruct);
        return true;
    }
}

// Create a new item stack
void UCPP_InventoryComponent::CPP_CreateStack(const FItemStruct& AddSlot)
{
    CPP_Inventory.Add(AddSlot); 
    CPP_UpdateInventory(); 
}

// Add items to an existing stack
void UCPP_InventoryComponent::CPP_AddToStack(const FItemStruct& SlotStruct, int32 SlotIndex)
{
    CPP_Inventory[SlotIndex].Quantity += SlotStruct.Quantity; 

    if (CPP_Inventory[SlotIndex].Quantity > CPP_Inventory[SlotIndex].MaxStackSize)
    {
        CPP_Inventory[SlotIndex].Quantity = CPP_Inventory[SlotIndex].MaxStackSize;
    }

    CPP_UpdateInventory(); 
}

// Update the inventory UI
void UCPP_InventoryComponent::CPP_UpdateInventory()
{
    if (CPP_WBP_Inventory)
    {
        // In Blueprint function to update UI
    }
}
