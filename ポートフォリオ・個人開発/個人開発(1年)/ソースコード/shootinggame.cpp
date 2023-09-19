#include "DxLib.h"
#include "variable.h"
#include "math.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//-----------------//
	//��{�ݒ�
	//-----------------//

	SetMainWindowText("shootinggame");								//�E�B���h�E�^�C�g��
	
	if (DxLib_Init() == -1)											// �c�w���C�u��������������
	{
		return -1;													// �G���[���N�����璼���ɏI��
	}
	
	//ChangeWindowMode(true);
	SetGraphMode(windowWidth, windowHeight, color);			//�E�B���h�E�T�C�Y�ƃJ���[���w��

	//-----------------//
	//�摜�ǂݍ���
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
	//�T�C�Y�ǂݍ���
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
	//�T�E���h�ǂݍ���
	//-----------------------//
	titleSound = LoadSoundMem("sound/title.mp3");
	playSound = LoadSoundMem("sound/play.mp3");
	shotSound = LoadSoundMem("sound/shot.mp3");

	while (1)
	{
		startTime = GetNowCount();
		//----------------------// 
		//�Q�[��������
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
		//�^�C�g�����
		//----------------------------------//
		while (!ProcessMessage() && gameStatus == TITLE) 										//�G���[���o����Ԃ��^�C�g����������
		{
			ClearDrawScreen();																				//�`�揉����
			DrawGraph(title.x, title.y, title.img, FALSE);													//�w�i�\��
			
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//�G���^�[�L�[�������ꂽ��
			{
				StopSoundMem(titleSound); 
				gameStatus = PLAY;																//�Q�[�����v���C��Ԃɂ���
				PlaySoundMem(playSound, true);
			}
			ScreenFlip();																		//��ʍX�V����
		}
		while (!ProcessMessage() && gameStatus == PLAY)															//�G���[���o����Ԃ��v���C��������
		{
			PShotCount++;
			mainCount++;
			//----------------------------------//
			//�`�揉����
			//----------------------------------//	
			ClearDrawScreen();

			//-----------------//
			//�ړ�����
			//------------------//

			if (CheckHitKey(KEY_INPUT_W))							//��
			{
				player.y = playerMove(player.y, (player.speed*-1));
			}
			if (CheckHitKey(KEY_INPUT_S))							//��
			{
				player.y = playerMove(player.y, player.speed);
			}


			if (CheckHitKey(KEY_INPUT_D))							//�E
			{
				player.x = playerMove(player.x, player.speed);
			}
			if (CheckHitKey(KEY_INPUT_A))							//��
			{
				player.x = playerMove(player.x, (player.speed*-1));
			}

			//----------------//
			//�w�i����
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
			//�V���b�g����
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
			//�v���C���[����
			//----------------//

			//----------------//
			//�G�l�~�[����
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
			//�{�X����
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
			//�A�C�e������
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
			//�Փˏ���
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
			//���ԏ���
			//----------------//
			
			if (startTime + (100 * 1000) <= GetNowCount())
			{
				gameStatus = OVER;
				StopSoundMem(playSound);
			}

			//----------------//
			//�摜�\��
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
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "�J�E���g��:%d", mainCount);
			//DrawFormatString(0, 50, GetColor(255, 255, 255), "�b��:%d", mainCount/60);
			//DrawFormatString(0, 100, GetColor(255, 255, 255), "�G�ɓ���������:%d", enemy.hitCount);
			//DrawFormatString(0, 150, GetColor(255, 255, 255), "�A�C�e�����Ƃ�����:%d",player.itemGet);
			
			DrawFormatString(0, 0, GetColor(255, 255, 255), "�c�胉�C�t:%d", player.hp);
			DrawFormatString(0, 50, GetColor(255, 255, 255), "�v���C���[���x:%d", player.speed);
			DrawFormatString(0, 100, GetColor(255, 255, 255), "�G�̎c�胉�C�t:%d", boss.hp);
			SetFontSize(40);
			DrawFormatString(0, 150, GetColor(255, 255, 255), "�c��:%d�b", (100*1000 - (GetNowCount() - startTime)) / 1000);  // �������ԕ\��
			//DrawFormatString(0, 400, GetColor(255, 255, 255), "�p�x:%d", Bshot[i].angle);
			ScreenFlip();					//��ʍX�V����

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
	//�I������
	//----------------//
		while (!ProcessMessage() && gameStatus == OVER)
		{
			ClearDrawScreen();
			DrawGraph(over.x, over.y, over.img, TRUE);
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//�G���^�[�L�[�������ꂽ��
			{
				gameStatus = INIT;																//�Q�[������������Ԃɂ���
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
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//�G���^�[�L�[�������ꂽ��
			{
				gameStatus = INIT;																//�Q�[������������Ԃɂ���
			}
			ScreenFlip();
		}
	}
	

	return 0;														// �\�t�g�̏I�� 

	DxLib_End();													// �c�w���C�u�����g�p�̏I������
}

