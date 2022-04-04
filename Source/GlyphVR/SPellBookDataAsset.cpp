// Fill out your copyright notice in the Description page of Project Settings.


#include "SPellBookDataAsset.h"

TSubclassOf<ASpell> USPellBookDataAsset::GetSpell(TArray<GlyphEnum> Glyphs)
{
	for (USpellDataAsset spell : Spells)
	{
		if(spell.SpellRecipe == Glyphs)
		{
			return spell.Spell;
		}
	}
	return nullptr;
}