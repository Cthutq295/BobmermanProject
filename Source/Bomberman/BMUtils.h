#pragma once
#include "Player/BMBaseCharacter.h"

struct BMUtils
{
	static int32 const MinMapSize = 7;
	static int32 const MaxMapSize = 30;

	bool static AreEnemies(AController* Controller1, AController* Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;
		const auto Character1 = Cast<ABMBaseCharacter>(Controller1->GetPawn());
		const auto Character2 = Cast<ABMBaseCharacter>(Controller2->GetPawn());
		return Character1 && Character2 && Character1->GetCharacterType() != Character2->GetCharacterType();
	}
};
