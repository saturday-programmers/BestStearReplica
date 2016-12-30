﻿#include <vector>

#include "StageController.h"
#include "Stage/Stage1.h"
#include "Drawing/Drawer.h"
#include "Map/Map.h"
#include "Character/Player.h"
#include "Character/Enemy.h"

using namespace BestStealReplica::Character;


namespace BestStealReplica {

/* Constructor / Destructor ------------------------------------------------------------------------- */
StageController::StageController() : pStage(nullptr), pMap(nullptr), pPlayer(nullptr), pEnemy(nullptr) {}

StageController::~StageController() {
	delete this->pEnemy;
	delete this->pPlayer;
	delete this->pMap;
}


/* Public Functions  -------------------------------------------------------------------------------- */
void StageController::LoadStage(const Stage::IStage& rStage) {
	// マップ情報
	this->pStage = &rStage;
	this->pMap = new Map::Map();
	Drawing::Drawer::AddDrawable(*this->pMap);
	this->pMap->Load(*this->pStage);

	// プレイヤー情報
	POINT playerChipPos;
	this->pStage->GetPlayerFirstChipPos(&playerChipPos);
	POINT playerTopLeftXY;
	this->pMap->ConvertMapChipPosToTopLeftXY(playerChipPos, &playerTopLeftXY);
	this->pPlayer = new Player(playerTopLeftXY);
	Drawing::Drawer::AddDrawable(*this->pPlayer);

	// 敵情報
	std::vector<Enemy::EnemyInfo> enemiesInfo = this->pStage->GetEnemiesInfo();
	std::vector<POINT> enemiesXY;
	for (auto& enemy : enemiesInfo) {
		POINT enemyTopLeftXY;
		this->pMap->ConvertMapChipPosToTopLeftXY(enemy.chipPos, &enemyTopLeftXY);
		enemiesXY.push_back(enemyTopLeftXY);
	}
	this->pEnemy = new Enemy(enemiesInfo, enemiesXY, this->pStage->GetEnemyScoutableRadius());
	Drawing::Drawer::AddDrawable(*this->pEnemy);
}

void StageController::Control(AppCommon::Key key) {
	StageController::Handling handling = ConvertKeyToHandling(key);

	// プレイヤー死亡
	Vertices<POINT> playerXY;
	this->pPlayer->CalcPlayerXY(&playerXY);
	if (this->pEnemy->CanKillPlayer(playerXY)) {
		RevertStage();
		AppCommon::SetScene(AppCommon::SceneType::BLACKOUT);
		return;
	}

	// プレイヤーアニメーション
	int movingPixel = ControlPlayer(&handling);

	// 敵アニメージョン
	ControlEnemy(movingPixel, handling);

	// マップアニメーション
	ControlMap(movingPixel);

	this->lastTimeHandling = handling;
}


/* Private Functions  ------------------------------------------------------------------------------- */
StageController::Handling StageController::ConvertKeyToHandling(AppCommon::Key key) const {
	StageController::Handling ret;
	if (key.z) {
		ret.handlingType = StageController::Handling::HandlingType::STEAL_OR_OPEN;
	} else if (key.x) {
		ret.handlingType = StageController::Handling::HandlingType::THROW;
	} else {
		if (key.up) {
			ret.handlingType = StageController::Handling::HandlingType::UP;
		} else if (key.right) {
			ret.handlingType = StageController::Handling::HandlingType::RIGHT;
		} else if (key.down) {
			ret.handlingType = StageController::Handling::HandlingType::DOWN;
		} else if (key.left) {
			ret.handlingType = StageController::Handling::HandlingType::LEFT;
		} 
		if (ret.handlingType != StageController::Handling::HandlingType::NONE) {
			if (key.shift) {
				ret.isWalking = true;
			}
		}
	}
	return ret;
}

int StageController::ControlPlayer(Handling* pHandling) {
	int movingPixel;

	if (this->pPlayer->IsStealing()) {
		pHandling->handlingType = Handling::HandlingType::NONE;
	}

	Vertices<POINT> playerXY;
	this->pPlayer->CalcPlayerXY(&playerXY);

	if (pHandling->handlingType == Handling::HandlingType::STEAL_OR_OPEN) {
		// プレイヤーの目の前のマップチップ取得
		POINT frontMapChipPos;
		this->pMap->ConvertToCharacterFrontMapChipPos(playerXY, this->pPlayer->GetHeadingDirection(), &frontMapChipPos);
		bool canStartStealing = true;
		Map::MapChipType mapChipType = this->pMap->GetMapChipType(frontMapChipPos);
		switch (mapChipType) {
			case Map::MapChipType::GATE:
			case Map::MapChipType::GOLD_GATE: {
				if (!this->pMap->IsGateOpened(frontMapChipPos)) {
					AppCommon::GateKeyType gateKeyType = (mapChipType == Map::MapChipType::GATE) ? AppCommon::GateKeyType::Silver : AppCommon::GateKeyType::Gold;
					if (this->pPlayer->HasGateKey(gateKeyType)) {
						// ドアを開ける
						if (this->pMap->StartOpeningGate(frontMapChipPos)) {
							this->pPlayer->LoseGateKey(gateKeyType);
						}
					}
					canStartStealing = false;
				}
				break;
			}
			case Map::MapChipType::JEWELRY:
				// 宝箱を開ける
				this->pMap->OpenJewelryBox();
				canStartStealing = false;
				break;
			default:
				break;
		}

		if (canStartStealing) {
			// 目の前が開いていないドア以外の場合は盗むアクション
			this->pPlayer->StartStealing();
		}
	} else if (pHandling->handlingType == Handling::HandlingType::THROW && pHandling->handlingType != this->lastTimeHandling.handlingType) {
		// 石を投げる
		this->pMap->AddStone(playerXY.topLeft, this->pPlayer->GetHeadingDirection());
	}

	// 盗むアクション継続
	if (this->pPlayer->IsStealing()) {
		this->pPlayer->KeepStealing();
	} else {
		// プレイヤー移動方向
		switch (pHandling->handlingType) {
			case Handling::HandlingType::RIGHT:
				this->pPlayer->SetDirection(AppCommon::Direction::RIGHT);
				break;
			case Handling::HandlingType::LEFT:
				this->pPlayer->SetDirection(AppCommon::Direction::LEFT);
				break;
			case Handling::HandlingType::UP:
				this->pPlayer->SetDirection(AppCommon::Direction::TOP);
				break;
			case Handling::HandlingType::DOWN:
				this->pPlayer->SetDirection(AppCommon::Direction::BOTTOM);
				break;
			default:
				break;
		}
	}

	// プレイヤー移動距離
	if (this->pPlayer->IsStealing()) {
		movingPixel = Player::MOVING_PIXEL_ON_STEALING;
	} else {
		switch (pHandling->handlingType) {
			case Handling::HandlingType::NONE:
			case Handling::HandlingType::STEAL_OR_OPEN:
			case Handling::HandlingType::THROW:
				movingPixel = 0;
				break;
			default:
				movingPixel = pHandling->isWalking ? StageController::MOVING_PIXEL_ON_WALKING : StageController::MOVING_PIXEL_ON_RUNNING;
				break;
		}
	}
	POINT movingPoint;
	movingPoint.x = 0;
	movingPoint.y = 0;
	switch (pPlayer->GetHeadingDirection()) {
		case AppCommon::Direction::RIGHT:
			movingPoint.x = movingPixel;
			break;
		case AppCommon::Direction::LEFT:
			movingPoint.x = movingPixel * -1;
			break;
		case AppCommon::Direction::TOP:
			movingPoint.y = movingPixel * -1;
			break;
		case AppCommon::Direction::BOTTOM:
			movingPoint.y = movingPixel;
			break;
	}

	// プレイヤーアニメーション
	if (!this->pPlayer->IsStealing()) {
		if (movingPixel > 0) {
			this->pPlayer->Walk(movingPoint);
		} else {
			this->pPlayer->Stay();
		}
	}

	// 移動可能範囲確認
	if (movingPixel > 0) {
		POINT reversePoint;
		reversePoint.x = 0;
		reversePoint.y = 0;
		if (movingPoint.x != 0) {
			reversePoint.x = -1 * (movingPoint.x / movingPixel);
		} else if (movingPoint.y != 0) {
			reversePoint.y = -1 * (movingPoint.y / movingPixel);
		}

		this->pPlayer->CalcPlayerXY(&playerXY);
		while (!this->pMap->IsOnRoad(playerXY) && movingPixel > 0) {
			// 移動不可能な場所に移動した場合は元の位置に戻す
			this->pPlayer->Move(reversePoint);
			--movingPixel;
			this->pPlayer->CalcPlayerXY(&playerXY);
		}
	}

	// 歩く/走るの状態設定
	if (this->pPlayer->IsStealing()) {
		// 盗み処理中は歩く状態と同じ扱い
		pHandling->isWalking = true;
	} else if (movingPixel == 0) {
		// プレイヤーが移動していない場合は走る/歩くの状態は前回の状態を引き継ぐ
		pHandling->isWalking = lastTimeHandling.isWalking;
	}

	return movingPixel;
}

void StageController::ControlEnemy(int playerMovingPixel, const Handling& rHandling) {
	this->pEnemy->Stay();

	Vertices<POINT> playerXY;
	this->pPlayer->CalcPlayerXY(&playerXY);

	// 盗まれる処理
	AppCommon::GateKeyType gateKeyType = this->pEnemy->GetStolen(playerXY, this->pPlayer->IsStealing());
	if (gateKeyType != AppCommon::GateKeyType::None) {
		this->pPlayer->GainGateKey(gateKeyType);
	}

	// プレイヤーを発見したか
	POINT centerPlayer;
	pPlayer->CalcCenterXY(&centerPlayer);
	this->pEnemy->ScoutPlayer(centerPlayer, rHandling.isWalking);

	// 突進可能か
	POINT playerPos;
	this->pMap->ConvertToMapChipPos(centerPlayer, &playerPos);
	for (int enemyIdx = 0; enemyIdx < this->pEnemy->GetEnermyCount(); ++enemyIdx) {
		if (this->pEnemy->GetState(enemyIdx) == Enemy::State::GOT_STOLEN) {
			continue;
		}

		// プレイヤーとの距離チェック
		POINT centerEnemy;
		pEnemy->CalcCenterXY(enemyIdx, &centerEnemy);
		POINT enemyPos;
		this->pMap->ConvertToMapChipPos(centerEnemy, &enemyPos);
		bool canSeePlayer = false;
		int distance;
		switch (this->pEnemy->GetHeadingDirection(enemyIdx)) {
			case AppCommon::Direction::TOP:
				canSeePlayer = (enemyPos.x == playerPos.x && enemyPos.y >= playerPos.y);
				distance = centerEnemy.y - centerPlayer.y;
				break;
			case AppCommon::Direction::RIGHT:
				canSeePlayer = (enemyPos.y== playerPos.y && enemyPos.x <= playerPos.x);
				distance = centerPlayer.x - centerEnemy.x;
				break;
			case AppCommon::Direction::BOTTOM:
				canSeePlayer = (enemyPos.x == playerPos.x && enemyPos.y <= playerPos.y);
				distance = centerPlayer.y - centerEnemy.y;
				break;
			case AppCommon::Direction::LEFT:
				canSeePlayer = (enemyPos.y == playerPos.y && enemyPos.x >= playerPos.x);
				distance = centerEnemy.x - centerPlayer.x;
				break;
		}
		canSeePlayer = canSeePlayer && distance <= this->pStage->GetEnemyScoutableRadius();

		// プレイヤーとの間に壁があるか
		canSeePlayer = canSeePlayer && !this->pMap->ExistsWallBetween(centerEnemy, centerPlayer);

		// 突進
		this->pEnemy->Attack(enemyIdx, canSeePlayer);
	}

	// 石を発見したか
	std::vector<Vertices<POINT>> stoneXYs;
	this->pMap->CalcDroppedStoneXYs(&stoneXYs);
	this->pEnemy->ScoutStone(stoneXYs);
}

void StageController::ControlMap(int playerMovingPixel) {
	// ドアを開けるアニメーション
	this->pMap->KeepOpeningGates();

	// 石を投げるアニメーション
	this->pMap->AnimateStones();

	// プレイヤーがウィンドウ外に出る手前の場合はマップを移動させる
	if (playerMovingPixel > 0) {
		MoveMap(playerMovingPixel);
	}
}

void StageController::MoveMap(int playerMovingPixel) {
	POINT mapMovingPoint;
	mapMovingPoint.x = 0;
	mapMovingPoint.y = 0;

	// 一旦移動させてみる
	if (this->pPlayer->IsStayingNearlyWindowTop()) {
		mapMovingPoint.y = playerMovingPixel;
	} else if (this->pPlayer->IsStayingNearlyWindowBottom()) {
		mapMovingPoint.y = playerMovingPixel * -1;
	}
	if (this->pPlayer->IsStayingNearlyWindowRight()) {
		mapMovingPoint.x = playerMovingPixel * -1;
	} else if (this->pPlayer->IsStayingNearlyWindowLeft()) {
		mapMovingPoint.x = playerMovingPixel;
	}

	// マップ外が表示されてしまう場合は元に戻す
	if (!this->pMap->IsMovableX(mapMovingPoint.x)) {
		mapMovingPoint.x = 0;
	}
	if (!this->pMap->IsMovableY(mapMovingPoint.y)) {
		mapMovingPoint.y = 0;
	}

	if (mapMovingPoint.x != 0 || mapMovingPoint.y != 0) {
		this->pMap->Move(mapMovingPoint);
		this->pPlayer->Move(mapMovingPoint);
		this->pEnemy->Move(mapMovingPoint);
	}
}

void StageController::RevertStage() {
	this->pMap->MoveToDefault();
	this->pPlayer->GetKilled();
	this->pEnemy->BackToDefaultPosition();
}

}