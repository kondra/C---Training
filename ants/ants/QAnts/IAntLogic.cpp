#include "IAntLogic.hpp"
#include "IAntLogicImpl.hpp"

namespace antlogic
{
	IAntLogic* IAntLogic::GetAntLogic(int teamId)
	{
		switch (teamId)
		{
			case (/*Teams::*/Team01):
				return new AntLogicTeam01();
				break;
			case (/*Teams::*/Team02):
				return new AntLogicTeam01();
				break;
		}
	}

    AntSensor::AntSensor() :
	    smell(-1),
	    smellIntensity(0),
	    isFriend(false),
	    isEnemy(false),
	    isMyHill(false),
	    isEnemyHill(false),
	    isFood(false),
	    isWall(false)
    {
    }
}

