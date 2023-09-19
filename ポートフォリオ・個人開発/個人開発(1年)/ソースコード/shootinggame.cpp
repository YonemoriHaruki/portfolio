#include "DxLib.h"
#include "variable.h"
#include "math.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//-----------------//
	//基本設定
	//-----------------//

	SetMainWindowText("shootinggame");								//ウィンドウタイトル
	
	if (DxLib_Init() == -1)											// ＤＸライブラリ初期化処理
	{
		return -1;													// エラーが起きたら直ちに終了
	}
	
	//ChangeWindowMode(true);
	SetGraphMode(windowWidth, windowHeight, color);			//ウィンドウサイズとカラー数指定

	//-----------------//
	//画像読み込み
	//-----------------//

	back.img1 = LoadGraph("img/back1.png");
	back.img2 = LoadGraph("img/back2.png");
	back.img3 = LoadGraph("img/back3.png");
	clear.img = LoadGraph("img/clear.png");
	over.img = LoadGraph("img/over.png");

	player.img = LoadGraph("img/player.png");
	int PlayerShotimg = LoadGraph("img/playerBullet.png");
	enemy.img = LoadGraph("img/enemy.png");
	boss.img = LoadGraph("img/boss.png");
	int PlayerItemImg = LoadGraph("img/item.png");	

	title.img = LoadGraph("img/titleimg.png");
	int BossShotimg = LoadGraph("img/bossBullet.png");

	//-----------------//
	//サイズ読み込み
	//-----------------//

	int PlayerShotW,PlayerShotH = 
	GetGraphSize(PlayerShotimg, &PlayerShotW, &PlayerShotH);

	GetGraphSize(player.img,&player.w,&player.h);
	GetGraphSize(enemy.img, &enemy.w, &enemy.h);
	GetGraphSize(boss.img,&boss.w,&boss.h);

	int PlayerItemW, PlayerItemH =
		GetGraphSize(PlayerItemImg, &PlayerItemW, &PlayerItemH);

	int BossShotW, BossShotH =
		GetGraphSize(BossShotimg, &BossShotW, &BossShotW);

	//------------------------// 
	//サウンド読み込み
	//-----------------------//
	titleSound = LoadSoundMem("sound/title.mp3");
	playSound = LoadSoundMem("sound/play.mp3");
	shotSound = LoadSoundMem("sound/shot.mp3");

	while (1)
	{
		startTime = GetNowCount();
		//----------------------// 
		//ゲーム初期化
		//---------------------//
		while (!ProcessMessage() && gameStatus == INIT)
		{
			ClearDrawScreen();
			gameStatus = TITLE;

			mainCount = 0;
			PShotCount = 0;

			bossShotNum = 0;

			player.x = 10;
			player.y = 550;
			player.hp = playerHp;
			player.speed = firstSpeed;

			enemy.x = 2000;
			enemy.y = 450;

			boss.hp = bosshp;
			boss.x = 1950;
			boss.y = 450;
			boss.count = 0;
			boss.count2 = 0;
			boss.angle = 0;

			for (i = 0; i < PShotNum; i++)
			{
				Pshot[i].flag = false;
				Pshot[i].img = PlayerShotimg;
				Pshot[i].w = PlayerShotW;
				Pshot[i].h = PlayerShotH;
			}


			for (i = 0; i < itemNum; i++)
			{
				item[i].flag = false;
				item[i].img = PlayerItemImg;
				item[i].w = PlayerItemW;
				item[i].h = PlayerItemH;
			}

			for (i = 0; i < BShotMax; i++)
			{
				Bshot[i].flag = false;
				Bshot[i].img = BossShotimg;
				Bshot[i].w = BossShotW;
				Bshot[i].h = BossShotH;
			}
			player.life = true;
			enemy.life = true;
			boss.life = true;

			PlaySoundMem(titleSound, true);

			ScreenFlip();
		}
		//----------------------------------// 
		//タイトル画面
		//----------------------------------//
		while (!ProcessMessage() && gameStatus == TITLE) 										//エラーが出ず状態がタイトルだったら
		{
			ClearDrawScreen();																				//描画初期化
			DrawGraph(title.x, title.y, title.img, FALSE);													//背景表示
			
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//エンターキーが押されたら
			{
				StopSoundMem(titleSound); 
				gameStatus = PLAY;																//ゲームをプレイ状態にする
				PlaySoundMem(playSound, true);
			}
			ScreenFlip();																		//画面更新処理
		}
		while (!ProcessMessage() && gameStatus == PLAY)															//エラーが出ず状態がプレイだったら
		{
			PShotCount++;
			mainCount++;
			//----------------------------------//
			//描画初期化
			//----------------------------------//	
			ClearDrawScreen();

			//-----------------//
			//移動処理
			//------------------//

			if (CheckHitKey(KEY_INPUT_W))							//上
			{
				player.y = playerMove(player.y, (player.speed*-1));
			}
			if (CheckHitKey(KEY_INPUT_S))							//下
			{
				player.y = playerMove(player.y, player.speed);
			}


			if (CheckHitKey(KEY_INPUT_D))							//右
			{
				player.x = playerMove(player.x, player.speed);
			}
			if (CheckHitKey(KEY_INPUT_A))							//左
			{
				player.x = playerMove(player.x, (player.speed*-1));
			}

			//----------------//
			//背景処理
			//----------------//

			back.x1 = backMove(back.x1, (back.speed * -1));
			back.x2 = backMove(back.x2, (back.speed * -1));
			back.x3 = backMove(back.x3, (back.speed * -1));
			if (back.x1 <= -3840)
			{
				back.x1 = 1920;
			}
			if (back.x2 <= -3840)
			{
				back.x2 = 1920;
			}
			if (back.x3 <= -3840)
			{
				back.x3 = 1920;
			}

			

			//----------------//
			//ショット処理
			//----------------//
			
			if (CheckHitKey(KEY_INPUT_SPACE) == 1 && PShotCount % 9 == 0)
			{
				PlaySoundMem(shotSound,true);
				for (i = 0; i < PShotNum; i++)
				{
					if (Pshot[i].flag == false)
					{
						Pshot[i].flag = true;
						Pshot[i].x = player.x;
						Pshot[i].y = player.y;

						Pshot[i].x = Pshot[i].x - Pshot[i].w / 2;
						Pshot[i].y = Pshot[i].y - Pshot[i].h / 2;

						Pshot[i].x = (player.w - Pshot[i].w) / 2 + player.x;
						Pshot[i].y = (player.h - Pshot[i].h) / 2.5 + player.y;
						break;
					}
				}
			}

			for (i = 0; i < PShotNum; i++)
			{
				if (Pshot[i].flag)
				{
					Pshot[i].x += PShotSpeed;

					if (Pshot[i].x >= 1920)
					{
						Pshot[i].flag = false;
					}
				}
			}

			//----------------//
			//プレイヤー処理
			//----------------//

			//----------------//
			//エネミー処理
			//----------------//
			enemy.life = true;
			if (enemy.inTime < mainCount && enemy.stopTime>mainCount)
			{
				enemy.x -= 2;
			}
			if (enemy.moveTime < mainCount&& enemy.outTime > mainCount)
			{
				if (enemy.direction)
				{
					enemy.y += enemy.speed;
				}
				if (!enemy.direction)
				{
					enemy.y -= enemy.speed;
				}
			}
			if(enemy.outTime < mainCount)
			{
				enemy.x += 2;
				
				if (enemy.x > 1950)
				{
					enemy.life = false;
				}
			}
			
			if (enemy.y <= -5)
			{
				enemy.y = 0;
				enemy.direction = true;
			}
			if (enemy.y >= 880)
			{
				enemy.y = 880;
				enemy.direction = false;
			}
			//----------------//
			//ボス処理
			//----------------//
			if (boss.inTime < mainCount && boss.stopTime>mainCount)
			{
				boss.x -= 2;

			}
			if (boss.hp <= 0)
			{
				boss.life = true;
			}

			
			for (i = 0; i < BShotMax; i++)
			{
				if (Bshot[i].flag == false && mainCount > boss.stopTime&&mainCount % 5 == 0)
				{
					Bshot[i].flag = true;

					Bshot[i].x = (boss.w - Bshot[i].w) / 2 + boss.x;
					Bshot[i].y = (boss.h - Bshot[i].h) / 2.5 + boss.y;

					{
						double playerXtmp, playerYtmp, shotBossX, shotBossY, shotboss, BshotSx, BshotSy;

						BshotSx = Bshot[i].x + Bshot[i].w / 2;
						BshotSy = Bshot[i].y + Bshot[i].h / 2;

						playerXtmp = player.x + player.w / 2;
						playerYtmp = player.y + player.h / 2;

						shotBossX = playerXtmp - BshotSx;
						shotBossY = playerYtmp - BshotSy;

						shotboss = sqrt(shotBossX * shotBossX + shotBossY * shotBossY);

						Bshot[i].sx = shotBossX / shotboss * BShotSpeed;
						Bshot[i].sy = shotBossY / shotboss * BShotSpeed;

						break;
					}

				}
			}


			for (i = 0; i < BShotMax; i++)
			{
				if (boss.life = true)
				{
					Bshot[i].x += Bshot[i].sx;
					Bshot[i].y += Bshot[i].sy;
				}
			}

			for (i = 0; i < BShotMax; i++)
			{
				if (boss.life = true)
				{
					if (Bshot[i].x <= -10)
					{
						Bshot[i].flag = false;
					}
					
				}
			}

			//----------------//
			//アイテム処理
			//----------------//

		
			if (enemy.hitCount % 5 == 0 && enemy.hitCount != 0 && mainCount > enemyStopTime&&mainCount < enemyOutTime)
			{
				for (i = 0; i < itemNum; i++)
				{
					if (item[i].flag == false)
					{
						item[i].flag = true;
						item[i].x = enemy.x;
						item[i].y = enemy.y;

						item[i].x = item[i].x - item[i].w / 2;
						item[i].y = item[i].y - item[i].h / 2;

						item[i].x = (enemy.w - item[i].w) / 2 + enemy.x;
						item[i].y = (enemy.h - item[i].h) / 2.5 + enemy.y;

						break;
					}
				}

			}

				for (i = 0; i < itemNum; i++)
				{
					if (item[i].flag)
					{
						item[i].x -= 20;
					}
					if (item[i].x <= -10)
					{
						item[i].flag = false;
					}
				}
				
				for (i = 0; i < itemNum; i++)
				{
					if (item[i].getFlag == true)
					{
						player.effect = GetRand(2)+1;
						if (player.effect == 1)
						{
							player.hp++;
							player.effect = 0;
							item[i].getFlag = false;
						}
						if (player.effect == 2)
						{
							player.speed++;
							player.effect = 0;
							item[i].getFlag = false;
						}
					}
				}

			//----------------//
			//衝突処理
			//----------------//
			if (player.x >= 1920 - 95)
			{
				player.x -= pushBack;
			}
			if (player.x <= -5)
			{
				player.x += pushBack;
			}

			if (player.y >= 1080 - 35)
			{
				player.y -= pushBack;
			}
			if (player.y <= -5)
			{
				player.y += pushBack;
			}
			
			for (i = 0; i < PShotNum; i++)
			{
				if (Pshot[i].flag)
				{
					if (((Pshot[i].x > enemy.x && Pshot[i].x < enemy.x + enemy.w) ||
						(enemy.x > Pshot[i].x && enemy.x < Pshot[i].x + Pshot[i].w)) &&
						((Pshot[i].y > enemy.y && Pshot[i].y < enemy.y + enemy.h) ||
						(enemy.y > Pshot[i].y && enemy.y < Pshot[i].y + Pshot[i].h)))

					{
						Pshot[i].flag = false;
						enemy.hitCount++;
					}
				}
			}
			for (i = 0; i < itemNum; i++)
			{
				if (item[i].flag)
				{
					if (((item[i].x> player.x && item[i].x< player.x + player.w) ||
						(player.x > item[i].x&& player.x < item[i].x + item[i].w+10)) &&
						((item[i].y  > player.y && item[i].y < player.y + player.h) ||
							(player.y > item[i].y  && player.y < item[i].y + item[i].h+10)))
					{
						item[i].flag = false;
						item[i].getFlag = true;
						player.itemGet++;
						
					}
				}
			}
			for (i = 0; i < PShotNum; i++)
			{
				if (Pshot[i].flag)
				{
					if (((Pshot[i].x > boss.x && Pshot[i].x < boss.x + boss.w) ||
						(boss.x > Pshot[i].x && boss.x < Pshot[i].x + Pshot[i].w)) &&
						((Pshot[i].y > boss.y && Pshot[i].y < boss.y + boss.h) ||
							(boss.y > Pshot[i].y && boss.y < Pshot[i].y + Pshot[i].h)))

					{
						Pshot[i].flag = false;
						if (mainCount > bossStopTime)
						{
							boss.hp -= 1;
						}
						if (boss.hp <= 0)
						{
							gameStatus = CLEAR;
							StopSoundMem(playSound);
						}
					}
				}
			}


			for (i = 0; i < BShotMax; i++)
			{
				if (Bshot[i].flag)
				{
					if (((Bshot[i].x > player.x && Bshot[i].x < player.x + player.w) ||
						(player.x > Bshot[i].x && player.x < Bshot[i].x + Bshot[i].w)) &&
						((Bshot[i].y > player.y && Bshot[i].y < player.y + player.h) ||
							(player.y > Bshot[i].y && player.y < Bshot[i].y + Bshot[i].h)))
					{
						player.hp--;
						Bshot[i].flag = false;
						if (player.hp <= 0)
						{
							gameStatus = OVER;
							StopSoundMem(playSound);
						}
					}
				}
			}
			
			//----------------//
			//時間処理
			//----------------//
			
			if (startTime + (100 * 1000) <= GetNowCount())
			{
				gameStatus = OVER;
				StopSoundMem(playSound);
			}

			//----------------//
			//画像表示
			//----------------//

			DrawGraph(back.x1, back.y1, back.img1, TRUE);
			DrawGraph(back.x2, back.y2, back.img2, TRUE);
			DrawGraph(back.x3, back.y3, back.img3, TRUE);

			
			
			

			if (enemy.life)
			{
				DrawGraph(enemy.x, enemy.y, enemy.img, TRUE);
			}

			if (boss.life)
			{
				DrawGraph(boss.x, boss.y, boss.img, TRUE);
			}
			for(i=0;i<itemNum;i++)
			{
				if (item[i].flag)
				{
					DrawGraph(item[i].x, item[i].y, item[i].img, TRUE);
				}
			}

			
			

			for (i = 0; i < PShotNum; i++)
			{
				if (Pshot[i].flag)
				{
					DrawGraph(Pshot[i].x,Pshot[i].y, Pshot[i].img, true);
				}

				if (player.life)
				{
					DrawGraph(player.x, player.y, player.img, TRUE);
				}

			}
			
			for (i = 0; i < BShotMax; i++)
			{
				if (Bshot[i].flag)
				{
					DrawGraph(Bshot[i].x, Bshot[i].y, Bshot[i].img, TRUE);
				}
			}

			SetFontSize(25);
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "カウント数:%d", mainCount);
			//DrawFormatString(0, 50, GetColor(255, 255, 255), "秒数:%d", mainCount/60);
			//DrawFormatString(0, 100, GetColor(255, 255, 255), "敵に当たった数:%d", enemy.hitCount);
			//DrawFormatString(0, 150, GetColor(255, 255, 255), "アイテムをとった数:%d",player.itemGet);
			
			DrawFormatString(0, 0, GetColor(255, 255, 255), "残りライフ:%d", player.hp);
			DrawFormatString(0, 50, GetColor(255, 255, 255), "プレイヤー速度:%d", player.speed);
			DrawFormatString(0, 100, GetColor(255, 255, 255), "敵の残りライフ:%d", boss.hp);
			SetFontSize(40);
			DrawFormatString(0, 150, GetColor(255, 255, 255), "残り:%d秒", (100*1000 - (GetNowCount() - startTime)) / 1000);  // 制限時間表示
			//DrawFormatString(0, 400, GetColor(255, 255, 255), "角度:%d", Bshot[i].angle);
			ScreenFlip();					//画面更新処理

			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			
		}
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		//----------------//
	//終了処理
	//----------------//
		while (!ProcessMessage() && gameStatus == OVER)
		{
			ClearDrawScreen();
			DrawGraph(over.x, over.y, over.img, TRUE);
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//エンターキーが押されたら
			{
				gameStatus = INIT;																//ゲームを初期化状態にする
			}
			ScreenFlip();
		}
		while (!ProcessMessage() && gameStatus == CLEAR)
		{
			ClearDrawScreen();
			DrawGraph(clear.x, clear.y, clear.img, TRUE);
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//エンターキーが押されたら
			{
				gameStatus = INIT;																//ゲームを初期化状態にする
			}
			ScreenFlip();
		}
	}
	

	return 0;														// ソフトの終了 

	DxLib_End();													// ＤＸライブラリ使用の終了処理
}

