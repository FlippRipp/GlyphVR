// Fill out your copyright notice in the Description page of Project Settings.

#include "SPellBookDataAsset.h"

TSubclassOf<ASpell> USPellBookDataAsset::GetSpell(TArray<GlyphEnum> Glyphs)
{
	for (USpellDataAsset* Spell : Spells)
	{
		if(Spell->SpellRecipe == Glyphs)
		{
			return Spell->Spell;
		}
	}
	return nullptr;
}
