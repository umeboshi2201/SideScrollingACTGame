#include <iostream>
#include "DxLib.h"
#include "GameCamera.h"
#include "GameEntityCamera.h"
#include "Input.h"
#include "DxlibInput.h"
#include "ImageMaker.h"
#include "DxlibImageMaker.h"
#include "MoveAndFloorCObjMgr.h"
#include "BFMoveAndFloorCObjMgr.h"
#include "GameEntityBrainMaker.h"
#include "TestGEBMaker.h"
#include "StageMgr.h"
#include "TestStageMgr.h"
#include "GameEntity.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try{
		// ウィンドウモードに設定
		ChangeWindowMode(TRUE);
		
		// ＤＸライブラリ初期化処理
		if(DxLib_Init() == -1){
			// エラーが起きたら直ちに終了
			return -1;
		}
		
		//描画先を裏画面に設定
		SetDrawScreen(DX_SCREEN_BACK);

		const int GAME_ENTITY_MAX = 5;

		GameEntity *ents = new GameEntity[GAME_ENTITY_MAX];
		Input *input = new DxlibInput();
		GameCamera *camera = new GameEntityCamera(640, 480, 1, 10);
		ImageMaker *imgMaker = new DxlibImageMaker();
		MoveAndFloorCObjMgr *mAFCOMgr = new BFMoveAndFloorCObjMgr();
		GameEntityBrainMaker *brainMaker = new TestGEBMaker(camera, imgMaker, mAFCOMgr, input);
		StageMgr *stageMgr = new TestStageMgr(camera, brainMaker, imgMaker);

		// ステージの床初期化
		mAFCOMgr->initFloors(stageMgr->getFloorCObjInitializer());
		// ステージの初期化
		stageMgr->gameEntInit(ents, GAME_ENTITY_MAX);

		while(true){
			// メッセージ処理
			if(ProcessMessage() != 0){
				//ウィンドウの×ボタンが押されたらループを抜ける
				break;
			}

			// 画面を消す
			ClearDrawScreen();

			for(int i = 0; i < GAME_ENTITY_MAX; i++){
				if(ents[i].getActive()){
					ents[i].update();
				}
			}

			std::cout << "error" << std::endl;

			mAFCOMgr->collisionCalc();

			//camera->setLeftX(ents[0].getLeftX() - 300);
			//camera->setTopY(ents[0].getTopY() - 240);

			stageMgr->drawFloor();

			camera->draw();

			//裏画面を表画面に反映
			ScreenFlip();
		}

		delete stageMgr;
		delete brainMaker;
		delete mAFCOMgr;
		delete imgMaker;
		delete camera;
		delete input;
		delete[] ents;

		// ＤＸライブラリ使用の終了処理
		DxLib_End();
	}
	catch(...){
		std::cout << "error!!!" << std::endl;
	}

	// ソフトの終了 
	return 0;
}
