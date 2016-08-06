#include "Stage1.h"
#include "Enermy.h"


namespace BestStealReplica {
namespace {

using Map::MapCommon;
using Character::CharacterCommon;
using Character::Enermy;

MapCommon::MapChipType mapChipTypes[Stage1::Y_CHIP_COUNT][Stage1::X_CHIP_COUNT] = {
	// 1									2									3									4									5									6									7									8									9									10									11									12									13									14									15									16									17									18									19									20									21									22									23									24									25									26									27									28									29									30
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD },		// 1
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD },		// 2
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD },		// 3
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD },		// 4
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD },		// 5
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD },		// 6
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD },		// 7
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL },		// 8
	{ MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::DOOR, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE },// 9
	{ MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD },		// 10
	{ MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::DOOR, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL },		// 11
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE },// 12
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::JEWELRY, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD },		// 13
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL },		// 14
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL },		// 15
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::GOLD_DOOR, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL },		// 16
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::DOOR, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::DOOR, MapCommon::MapChipType::WALL_SIDE },// 17
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD },		// 18
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD },		// 19
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD },		// 20
	{ MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::WALL_SIDE, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD, MapCommon::MapChipType::ROAD },		// 21
};

Enermy::EnermyInfo enermiesInfo[Stage1::ENERMY_COUNT] = {
	Enermy::EnermyInfo(6, 4, CharacterCommon::Direction::RIGHT, false),
	Enermy::EnermyInfo(24, 0, CharacterCommon::Direction::LEFT, true),
	Enermy::EnermyInfo(1, 20, CharacterCommon::Direction::RIGHT, true),
	Enermy::EnermyInfo(22, 7, CharacterCommon::Direction::LEFT, false),
	Enermy::EnermyInfo(3, 16, CharacterCommon::Direction::BOTTOM, true),
	Enermy::EnermyInfo(9, 20, CharacterCommon::Direction::RIGHT, true),
	Enermy::EnermyInfo(21, 14, CharacterCommon::Direction::RIGHT, false)
};

}

MapCommon::MapChipType Stage1::GetMapChipType(int y, int x) const {
	return mapChipTypes[y][x];
}

POINT Stage1::GetPlayerFirstChipPos() const {
	POINT ret;
	ret.x = 14;
	ret.y = 20;
	return ret;
}

int Stage1::GetEnermyCount() const {
	return Stage1::ENERMY_COUNT;
}

POINT Stage1::GetEnermyChipPos(int enermyNum) const {
	return enermiesInfo[enermyNum].chipPos;
}

Enermy::EnermyInfo* Stage1::GetEnermiesInfo() const {
	return enermiesInfo;
}

int Stage1::GetEnermySearchableRadius() const {
	return 250;
}

}