#include "stdafx.h"
#include "Managers.h"

chess::chess()
{
	x = 0;
	y = 0;
	type = -1;
}
Managers::Managers()
{
	Game_State = -1;
	int k, x, y;
	for (k = 0; k < 226;k++)
	{
		nChessinfo[k].type = k % 2;
	}
	Gameinfo = 100; //默认人-人对战 并且判断禁手
	for (x = 0; x < 15; x++)
		for (y = 0; y < 15; y++)
		{
			map[x][y]=-1;//初始化棋盘信息
		}
}


Managers::~Managers()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*函数名称：GameType(int t)
*函数介绍：改变游戏设置
*输入参数：t就是gameinfo
*输出参数：bool
*返回值：true表示成功 false表示失败
*/
bool Managers::GameType(int t)
{
	if (t % 10 > 1)
		return false;
	if (t % 100 > 11)
		return false;
	if (t > 111)
		return false;
	int Gameinfo = t;
	return true;

}
chess Managers::GetLastChe()
{
	return nChessinfo[nKeyDown - 1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*函数名称：GameStart()
*函数介绍：初始化游戏
*输入参数：无
*输出参数：无
*返回值：无
*/
void Managers::GameStart()
{
	int x, y;
	for (x = 0; x < 15; x++)
		for (y = 0; y < 15; y++)
			map[x][y] = -1;
	nKeyDown = 0;//设置下子为下了0颗子
	PAUSE = false;//游戏没有暂停
	if (Gameinfo % 10 == 0 || Gameinfo % 100 == 10) //如果本地用户是黑，则先走
		Game_State = 1;
	else
		Game_State = 2;
	LastCh.type = -1;//重新开始后将上一局的最后一个棋子置为-1，防止重画

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*函数名称：DoMsg(int x, int y, int action)
*函数介绍：消息响应
*输入参数：action含义0为鼠标经过，1为按下左键，2为按下右键
*输出参数：无
*返回值：无
*/
bool Managers::DoMsg(int x, int y, int action)
{
	if (Game_State > 2 || Game_State < 1)
	{
		return false;
	}
	if (action == 0)//鼠标滑过某个区域
	{
		if (x == LastCh.x&&y == LastCh.y)
			return false;
		if (LastCh.type >= 99)
		{
			map[LastCh.x][LastCh.y] = LastCh.type - 100;
		}
		map[x][y] += 100;
		LastCh.x = x;
		LastCh.y = y;
		LastCh.type = map[x][y];
		return true;
	}
	if (action == 1) //左键响应落子
	{
		if (((Gameinfo % 100) / 10 == 0 || Game_State == 1) && AddChess(x, y))//按左键走下棋子
		{
			LastCh.x = x;
			LastCh.y = y;
			LastCh.type = map[x][y] + 100;
			return true;
		}
	}
	if (action == 2)//右键响应没有任何反应
	{
		return false;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*函数名称：AddChess(int x, int y)
*函数介绍：增加新棋子到棋盘
*输入参数：（x，y）一组坐标 type表明是黑棋还是白棋
*输出参数：bool
*返回值：true表示响应成功，false表示失败
*/
bool Managers::AddChess(int x, int y)
{
	if (CheckMap(x, y, -1))
	{
		map[x][y] = nChessinfo[nKeyDown].type + 100;//最后下的一个棋子是焦点
		if (nKeyDown > 0)
		{
			//上一次下的棋子焦点消失
			map[nChessinfo[nKeyDown - 1].x][nChessinfo[nKeyDown - 1].y] -= 100;
		}
		nChessinfo[nKeyDown].x = x;
		nChessinfo[nKeyDown].y = y;
		nKeyDown++;
		Updata();
	}
	else
		return false;
	return true;

}

bool Managers::CheckMap(int x, int y, int pow)
{
	if (map[x][y] == pow || map[x][y] == pow + 100 || map[x][y] == pow - 100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*函数名称：Updata()
*函数介绍：游戏状态更新
*输入参数：无
*输出参数：bool
*返回值：true表示更新成功
*/
bool Managers::Updata()
{
	int k;
	k = CheckState();
	if (k == 0)
	{
		Game_State = Game_State % 2 + 1;
		if (nKeyDown >= 225)
		{
			Game_State = 5;
			PAUSE = true;
		}
	}
	else if (k < 0)
	{
		//白色赢
		Game_State = 4;
		PAUSE = true;
	}
	else if (k > 0)
	{
		//黑色赢
		Game_State = 3;
		PAUSE = true;
	}
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*函数名称：CheckState()
*函数介绍：检查游戏状态
*输入参数：无
*输出参数：int
*返回值：0为游戏继续，负数为白色赢，正数为黑色赢
*/

int Managers::CheckState()
{
	int n;//分别记录连子个数
	chess k;//记录棋子变量
	int i, j;//5个循环变量
	bool check;
	check = false;
	k = GetLastChe();
	if (k.type == 1) //白子情况，检查4个方向
	{
		for (i = -1; i <= 0; i++)
			for (j = -1; j <= 1; j++)
				if ((i != 0 || j != 0) && (i != 0 || j != 1))
				{
					n = GetNum(k, i, j, false) + GetNum(k, -i, -j, false) + 1;//此方向上的连子数
					if (n >= 5)
						return -1;//白棋胜利
				}
	}
	else  //黑子的情况
	{
		for (i = -1; i <= 0; i++)
			for (j = -1; j <= 1; j++)
				if ((i != 0 || j != 0) && (i != 0 || j != 1))
				{
					n = GetNum(k, i, j, false) + GetNum(k, -i, -j, false) + 1;//此方向上的连子数
					if (n == 5)
						return 1;//黑棋胜利，返回1
				}
		if (Gameinfo / 100 == 0)
			return 0;
// 		if (ForbidLoc(k))//禁手和5连形成判胜利，所以先判断是否5连
// 			return -1;
	}
	return 0;//什么都没改变，返回0

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*函数名称：GetNum(chess nCh, int i, int j, bool goon)
*函数介绍：求连子个数
*输入参数：nCh要求的棋子，i，j为一组方向，goon是一个开关，表示是否计算断开连接点
*输出参数：int
*返回值：连子数
*/
int Managers::GetNum(chess nCh, int i, int j, bool goon)
{
	int t, x, y;
	x = nCh.x + i;
	y = nCh.y + j;
	t = 0;//t记录连子个数
	if (nCh.type >= 99)
		nCh.type -= 100;
	while (x>0 && y>=0 && x<15 && y<15 && CheckMap(x,y,nCh.type))
	{
		x += i;
		y += j;
		t++;
	}
	//计算断点连接的问题
	if (goon && CheckMap(x,y,-1)&&x>=0 &&y>=0 &&x<15 &&y<15&&CheckMap(x+i,y+j,nCh.type))
	{
		chess nc;
		nc.type = nCh.type;
		nc.x = x;
		nc.y = y;
		x = GetNum(nc, i, j, false);
		if (x != 0)
			t += x + 100; //加上100用于区别是否有间断，这个在追踪是否有阻拦时用到
	}
	return t;
}