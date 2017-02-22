#pragma once
class chess
{
public:
	chess();
	virtual ~chess(){};
	int x, y;//棋子在棋盘中的坐标
	int type;//0为白棋，1为黑棋
};
class Managers
{
public:
	Managers();
	~Managers();
public:
	bool GameType(int t); //改变游戏的GameInfo
	chess GetLastChe();//返回最后一个下的棋子的信息
	int CheckState();//检查是否有胜利或者失败，为0什么都不发生，为正数表示胜利，为负数表示失败
	//bool GameBack(int step = 2);//悔棋steps是多少，悔棋一步基本没意义
	void GameStart();//初始化开始
	bool AddChess(int x, int y);//在map上增加新棋子，若成功 返回true，不成功返回false
	bool DoMsg(int x, int y, int action);//消息响应
	//friend class Computer;//申请一个电脑AI的友元，方便制作AI。以后这个类就是AI类了

public:
	chess LastCh; //上一次鼠标划过的棋子信息
	int map[15][15];//游戏地图，-1为没有棋子，0是黑棋，1是白棋
							//由于显示的需要，程序要对选中的地方进行高亮显，所以规定
							//99就是选中某空白区域，同样100和101是选中黑或白棋
	int nKeyDown; //已经走了多少步，走的步数为nKeyDown-1
	int Game_State; //游戏状态
							//1、游戏中Player1走棋 Player1一定是人
							//2、游戏中Player2走棋 这个表示可能是电脑 可能是人
							//3、游戏结束，黑色赢
							//4、游戏结束，白色赢
							//5、游戏结束，平手
							//other number 、还没开始
	bool PAUSE; //游戏是否暂停

private:
	bool Updata(); //游戏更新
	bool CheckMap(int x, int y, int pow); //用来查看游戏地图map[x][y]是否和pow相等
	int Gameinfo;//玩家信息 是一个两位的正整数
						//个位数0表示Player1，是黑色。1表示Player2，是白色
						//十位1表示另一个玩家是计算机，0表示另一个玩家是用户
						//这个信息将影响游戏更新Updata函数
	chess nChessinfo[226]; //每个玩家每步走的棋，用于记录也用于显示
protected:
	//bool ForbidLoc(chess k); //判断K棋子落地是否造成禁手
	int GetNum(chess nCh, int i, int j, bool goon);//这个函数起辅助作用，用于检测nChzai（i，j）方向的连子数
};

