// Copyright 2018-2020 - Roberto De Ioris

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LuaState.h"
#include "LuaUserDataObject.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, HideDropdown)
class LUAMACHINE_API ULuaUserDataObject : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lua")
	TSubclassOf<ULuaState> GetLuaState() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lua")
	ULuaState* GetLuaStateInstance() const;

	virtual UWorld* GetWorld() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lua")
	TMap<FString, FLuaValue> Table;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lua")
	TMap<FString, FLuaValue> Metatable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lua")
	bool bImplicitSelf;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lua")
	FLuaValue LuaGetField(FString Name);

	UFUNCTION(BlueprintCallable, Category = "Lua")
	void LuaSetField(FString Name, FLuaValue Value);

	UFUNCTION(BlueprintNativeEvent, Category = "Lua", meta = (DisplayName = "Lua Metatable __gc"))
	void ReceiveLuaGC();

	UFUNCTION(BlueprintNativeEvent, Category = "Lua", meta = (DisplayName = "Lua Metatable __index"))
	FLuaValue ReceiveLuaMetaIndex(FLuaValue Key);

	UFUNCTION(BlueprintCallable, Category = "Lua", meta = (AutoCreateRefTerm = "Args"))
	FLuaValue LuaCallFunction(FString Name, TArray<FLuaValue> Args, bool bGlobal);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Lua")
	FLuaValue UFunctionToLuaValue(FString FunctionName);

protected:
	TSharedPtr<FLuaSmartReference> AddLuaSmartReference(FLuaValue Value);
	void RemoveLuaSmartReference(TSharedPtr<FLuaSmartReference> Ref);
};
