// Fill out your copyright notice in the Description page of Project Settings.

#include "SPellBookDataAsset.h"

TSubclassOf<ASpell> USPellBookDataAsset::GetSpell(TArray<GlyphEnum> Glyphs)
{
	if(Glyphs.Num() <= 2) return nullptr;
	
	TArray<GlyphEnum> ShapeGlyphs = {Glyphs[0], Glyphs[1]};
	
	for (USpellDataAsset* Spell : Spells)
	{
		if(Spell->SpellRecipe == ShapeGlyphs)
		{
			return Spell->Spell;
		}
	}

	for (USpellDataAsset* ComplexSpell : ComplexSpells)
	{
		if(ComplexSpell->SpellRecipe == Glyphs)
		{
			return ComplexSpell->Spell;
		}
	}
	
	return nullptr;
}
