#include "MapChipWall.h"


namespace BestStealReplica {
namespace Map {

MapChipWall::MapChipWall() : MapChip(MapCommon::MapChipType::WALL) {}

void MapChipWall::SetChipNumber() {
	// ���̃p�^�[���ɍ��킹�ă`�b�v�ԍ����w��
	if (!this->needsTopLine && !this->needsRightLine && !this->needsBottomLine && !this->needsLeftLine) {
		// �l�������Ȃ��`�b�v�̓f�t�H���g�̂��̂��g�p
		this->chipNumber = (int)this->chipType;
	} else if (this->needsTopLine && this->needsRightLine && this->needsBottomLine && this->needsLeftLine) {
		this->chipNumber = ChipNumber::WALL_WITH_SURROUNDED_LINE;
	} else {
		if (this->needsTopLine) {
			if (this->needsRightLine) {
				if (this->needsBottomLine) {
					this->chipNumber = ChipNumber::WALL_WITHOUT_LEFT_LINE;
				} else {
					if (this->needsLeftLine) {
						this->chipNumber = ChipNumber::WALL_WITHOUT_BOTTOM_LINE;
					} else {
						this->chipNumber = ChipNumber::WALL_WITH_TOP_RIGHT_LINE;
					}
				}
			} else {
				if (this->needsBottomLine) {
					if (this->needsLeftLine) {
						this->chipNumber = ChipNumber::WALL_WITHOUT_RIGHT_LINE;
					} else {
						this->chipNumber = ChipNumber::WALL_WITH_TOP_BOTTOM_LINE;
					}
				} else {
					if (this->needsLeftLine) {
						this->chipNumber = ChipNumber::WALL_WITH_TOP_LEFT_LINE;
					} else {
						this->chipNumber = ChipNumber::WALL_WITH_TOP_LINE;
					}
				}
			}
		} else {
			if (this->needsRightLine) {
				if (this->needsBottomLine) {
					if (this->needsLeftLine) {
						this->chipNumber = ChipNumber::WALL_WITHOUT_TOP_LINE;
					} else {
						this->chipNumber = ChipNumber::WALL_WITH_BOTTOM_RIGHT_LINE;
					}
				} else {
					if (this->needsLeftLine) {
						this->chipNumber = ChipNumber::WALL_WITH_RIGHT_LEFT_LINE;
					} else {
						this->chipNumber = ChipNumber::WALL_WITH_RIGHT_LINE;
					}
				}
			} else {
				if (this->needsBottomLine) {
					if (this->needsLeftLine) {
						this->chipNumber = ChipNumber::WALL_WITH_BOTTOM_LEFT_LINE;
					} else {
						this->chipNumber = ChipNumber::WALL_WITH_BOTTOM_LINE;
					}
				} else {
					this->chipNumber = ChipNumber::WALL_WITH_LEFT_LINE;
				}
			}
		}
	}
	// �e�N�X�`���[��̃}�b�v�`�b�v�̈ʒu
	SetTuTv();
}

void MapChipWall::SetNeedsTopLine() {
	this->needsTopLine = true;
}

void MapChipWall::SetNeedsRightLine() {
	this->needsRightLine = true;
}

void MapChipWall::SetNeedsBottomLine() {
	this->needsBottomLine = true;
}

void MapChipWall::SetNeedsLeftLine() {
	this->needsLeftLine = true;
}


}
}