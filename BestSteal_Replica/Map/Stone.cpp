﻿#include <math.h>

#include "Stone.h"
#include "../Drawing/Drawer.h"
#include "../Map/MapChip.h"


namespace BestStealReplica {
namespace Map {


/* Constructor / Destructor ------------------------------------------------------------------------- */
Stone::Stone(const POINT& rTopLeftXY, AppCommon::Direction direction) : direction(direction), thrownElapsedCount(0), state(Stone::State::BEING_THROWN) {
	this->defaultTopLeftXY.x = rTopLeftXY.x;
	this->defaultTopLeftXY.y = rTopLeftXY.y;

	MapChip::ConvertChipNumberToTuTv(Stone::MAP_CHIP_NUMBER, &this->tutv);
	// 枠線をなくすために一回り小さくする
	this->tutv.topLeft.x += 0.01f;
	this->tutv.topLeft.y += 0.01f;
	this->tutv.bottomRight.x -= 0.01f;
	this->tutv.bottomRight.y -= 0.01f;
}


/* Getters / Setters -------------------------------------------------------------------------------- */	
void Stone::SetTopLeftXY(const POINT& rXY) {
	this->topLeftXY.x = rXY.x;
	this->topLeftXY.y = rXY.y;
	switch (this->direction) {
		case AppCommon::Direction::TOP:
		case AppCommon::Direction::BOTTOM:
			this->topLeftXYOnGnd.y = rXY.y;
			break;
		case AppCommon::Direction::RIGHT:
		case AppCommon::Direction::LEFT:
			this->topLeftXYOnGnd.x = rXY.x;
	}
}

Stone::State Stone::GetState() const {
	return this->state;
}


/* Public Functions  -------------------------------------------------------------------------------- */
void Stone::CreateDrawingContexts(std::vector<Drawing::DrawingContext>* pDrawingContexts) const {
	Drawing::DrawingContext context;
	context.textureType = Drawing::TextureType::MAP;
	CreateDrawingVertices(&context.vertices);
	switch (this->state) {
		case Stone::State::BEING_THROWN:
		case Stone::State::DROPPED:
			pDrawingContexts->push_back(context);
			break;
		case Stone::State::DISAPPEARING:
			context.alpha = Drawing::Drawer::GetAlphaOnBlinking(this->restTime);
			pDrawingContexts->push_back(context);
			break;
		default:
			break;
	}
}

void Stone::KeepBeingThrown() {
	/*
	 *  放物線の位置の求め方
	 *
	 *  *** X座標 ***
	 *  Xt = V0 * T ... 速度V0のときのT秒後の移動距離（等速度運動）
	 *
	 *  *** Y座標 ***
	 *  Yt = V0 * T - 1/2 * G * T^2 ... 初速V0のときのT秒後の移動距離
	 */ 

	switch (this->state) {
		case Stone::State::BEING_THROWN:
			if (thrownElapsedCount == 0) {
				this->topLeftXY = this->defaultTopLeftXY;
				this->topLeftXYOnGnd = this->defaultTopLeftXY;
			} else {
				int velocity = Stone::INITIAL_VELOCITY;
				int g = Stone::GRAVITY;
				int distance = Stone::INITIAL_VELOCITY * this->thrownElapsedCount;
				int height = Stone::INITIAL_VELOCITY * this->thrownElapsedCount - (Stone::GRAVITY * (int)pow(double(this->thrownElapsedCount), 2) / 2);

				switch (this->direction) {
					case AppCommon::Direction::TOP:
					{
						this->topLeftXYOnGnd.y = this->defaultTopLeftXY.y - distance;
						float r = 100.0f / distance;	// 100:カメラからスクリーンへの距離
						// 透視図の計算 y’ = d / y * zをアレンジ
						this->topLeftXY.y = this->topLeftXYOnGnd.y - (int)(r * height);
						break;
					}
					case AppCommon::Direction::RIGHT:
						this->topLeftXY.x = this->defaultTopLeftXY.x + distance;
						this->topLeftXY.y = this->defaultTopLeftXY.y - height;
						this->topLeftXYOnGnd.x = this->topLeftXY.x;
						break;
					case AppCommon::Direction::BOTTOM:
					{
						this->topLeftXYOnGnd.y = this->defaultTopLeftXY.y + distance;
						float r = 50.0f / distance;	// 50:カメラからスクリーンへの距離
						// 透視図の計算 y’ = d / y * zをアレンジ
						this->topLeftXY.y = this->topLeftXYOnGnd.y - (int)(r * height);
						break;
					}
					case AppCommon::Direction::LEFT:
						this->topLeftXY.x = this->defaultTopLeftXY.x - distance;
						this->topLeftXY.y = this->defaultTopLeftXY.y - height;
						this->topLeftXYOnGnd.x = this->topLeftXY.x;
						break;
				}

				// 地面に達した場合
				if (height <= 0) {
					SetDropped();
				} 
			}
			++this->thrownElapsedCount;
			break;

		case Stone::State::DROPPED:
			--this->restTime;
			if (this->restTime == 0) {
				this->state = Stone::State::DISAPPEARING;
				this->restTime = Stone::DISAPPEARING_DURATION;
			}
			break;

		case Stone::State::DISAPPEARING:
			--this->restTime;
			if (this->restTime == 0) {
				this->state = Stone::State::DiSAPPEARED;
			}
			break;
	}
}

bool Stone::Exists() const {
	return (this->state != Stone::State::DiSAPPEARED);
}

void Stone::Move(const POINT& rXY) {
	this->topLeftXY.x += rXY.x;
	this->topLeftXY.y += rXY.y;
}

void Stone::CalcXYsOnGround(Vertices<POINT>* pRet) const {
	pRet->topLeft = this->topLeftXYOnGnd;
	pRet->bottomRight.x = pRet->topLeft.x + Stone::WIDTH;
	pRet->bottomRight.y = pRet->topLeft.y + Stone::HEIGHT;
}

void Stone::SetDropped() {
	this->topLeftXY = topLeftXYOnGnd;
	this->state = Stone::State::DROPPED;
	this->restTime = Stone::STAYING_DURATION;
}

void Stone::BackOnePixel() {
	switch (this->direction) {
		case AppCommon::TOP:
			this->topLeftXY.y += 1;
			break;
		case AppCommon::Direction::RIGHT:
			this->topLeftXY.x -= 1;
			break;
		case AppCommon::Direction::BOTTOM:
			this->topLeftXY.y -= 1;
			break;
		case AppCommon::Direction::LEFT:
			this->topLeftXY.x += 1;
			break;
	}
	this->topLeftXYOnGnd = this->topLeftXY;
}


/* Private Functions  ------------------------------------------------------------------------------- */
void Stone::CreateDrawingVertices(Vertices<Drawing::DrawingVertex>* pRet) const {
	Drawing::DrawingVertex* pVerticesArr[] = { &pRet->topLeft, &pRet->bottomRight };
	FloatPoint tutv[] = { this->tutv.topLeft, this->tutv.bottomRight };

	POINT bottomRightXY;
	bottomRightXY.x = this->topLeftXY.x + Stone::WIDTH;
	bottomRightXY.y = this->topLeftXY.y + Stone::HEIGHT;
	POINT xyArr[] = { this->topLeftXY, bottomRightXY };

	for (int i = 0; i < 2; ++i) {
		pVerticesArr[i]->x = xyArr[i].x;
		pVerticesArr[i]->y = xyArr[i].y;
		pVerticesArr[i]->tu = tutv[i].x;
		pVerticesArr[i]->tv = tutv[i].y;
	}
}

}
}