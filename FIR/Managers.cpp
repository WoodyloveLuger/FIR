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
	Gameinfo = 100; //Ĭ����-�˶�ս �����жϽ���
	for (x = 0; x < 15; x++)
		for (y = 0; y < 15; y++)
		{
			map[x][y]=-1;//��ʼ��������Ϣ
		}
}


Managers::~Managers()
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*�������ƣ�GameType(int t)
*�������ܣ��ı���Ϸ����
*���������t����gameinfo
*���������bool
*����ֵ��true��ʾ�ɹ� false��ʾʧ��
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
*�������ƣ�GameStart()
*�������ܣ���ʼ����Ϸ
*�����������
*�����������
*����ֵ����
*/
void Managers::GameStart()
{
	int x, y;
	for (x = 0; x < 15; x++)
		for (y = 0; y < 15; y++)
			map[x][y] = -1;
	nKeyDown = 0;//��������Ϊ����0����
	PAUSE = false;//��Ϸû����ͣ
	if (Gameinfo % 10 == 0 || Gameinfo % 100 == 10) //��������û��Ǻڣ�������
		Game_State = 1;
	else
		Game_State = 2;
	LastCh.type = -1;//���¿�ʼ����һ�ֵ����һ��������Ϊ-1����ֹ�ػ�

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*�������ƣ�DoMsg(int x, int y, int action)
*�������ܣ���Ϣ��Ӧ
*���������action����0Ϊ��꾭����1Ϊ���������2Ϊ�����Ҽ�
*�����������
*����ֵ����
*/
bool Managers::DoMsg(int x, int y, int action)
{
	if (Game_State > 2 || Game_State < 1)
	{
		return false;
	}
	if (action == 0)//��껬��ĳ������
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
	if (action == 1) //�����Ӧ����
	{
		if (((Gameinfo % 100) / 10 == 0 || Game_State == 1) && AddChess(x, y))//�������������
		{
			LastCh.x = x;
			LastCh.y = y;
			LastCh.type = map[x][y] + 100;
			return true;
		}
	}
	if (action == 2)//�Ҽ���Ӧû���κη�Ӧ
	{
		return false;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*�������ƣ�AddChess(int x, int y)
*�������ܣ����������ӵ�����
*�����������x��y��һ������ type�����Ǻ��廹�ǰ���
*���������bool
*����ֵ��true��ʾ��Ӧ�ɹ���false��ʾʧ��
*/
bool Managers::AddChess(int x, int y)
{
	if (CheckMap(x, y, -1))
	{
		map[x][y] = nChessinfo[nKeyDown].type + 100;//����µ�һ�������ǽ���
		if (nKeyDown > 0)
		{
			//��һ���µ����ӽ�����ʧ
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
*�������ƣ�Updata()
*�������ܣ���Ϸ״̬����
*�����������
*���������bool
*����ֵ��true��ʾ���³ɹ�
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
		//��ɫӮ
		Game_State = 4;
		PAUSE = true;
	}
	else if (k > 0)
	{
		//��ɫӮ
		Game_State = 3;
		PAUSE = true;
	}
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*�������ƣ�CheckState()
*�������ܣ������Ϸ״̬
*�����������
*���������int
*����ֵ��0Ϊ��Ϸ����������Ϊ��ɫӮ������Ϊ��ɫӮ
*/

int Managers::CheckState()
{
	int n;//�ֱ��¼���Ӹ���
	chess k;//��¼���ӱ���
	int i, j;//5��ѭ������
	bool check;
	check = false;
	k = GetLastChe();
	if (k.type == 1) //������������4������
	{
		for (i = -1; i <= 0; i++)
			for (j = -1; j <= 1; j++)
				if ((i != 0 || j != 0) && (i != 0 || j != 1))
				{
					n = GetNum(k, i, j, false) + GetNum(k, -i, -j, false) + 1;//�˷����ϵ�������
					if (n >= 5)
						return -1;//����ʤ��
				}
	}
	else  //���ӵ����
	{
		for (i = -1; i <= 0; i++)
			for (j = -1; j <= 1; j++)
				if ((i != 0 || j != 0) && (i != 0 || j != 1))
				{
					n = GetNum(k, i, j, false) + GetNum(k, -i, -j, false) + 1;//�˷����ϵ�������
					if (n == 5)
						return 1;//����ʤ��������1
				}
		if (Gameinfo / 100 == 0)
			return 0;
// 		if (ForbidLoc(k))//���ֺ�5���γ���ʤ�����������ж��Ƿ�5��
// 			return -1;
	}
	return 0;//ʲô��û�ı䣬����0

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
*�������ƣ�GetNum(chess nCh, int i, int j, bool goon)
*�������ܣ������Ӹ���
*���������nChҪ������ӣ�i��jΪһ�鷽��goon��һ�����أ���ʾ�Ƿ����Ͽ����ӵ�
*���������int
*����ֵ��������
*/
int Managers::GetNum(chess nCh, int i, int j, bool goon)
{
	int t, x, y;
	x = nCh.x + i;
	y = nCh.y + j;
	t = 0;//t��¼���Ӹ���
	if (nCh.type >= 99)
		nCh.type -= 100;
	while (x>0 && y>=0 && x<15 && y<15 && CheckMap(x,y,nCh.type))
	{
		x += i;
		y += j;
		t++;
	}
	//����ϵ����ӵ�����
	if (goon && CheckMap(x,y,-1)&&x>=0 &&y>=0 &&x<15 &&y<15&&CheckMap(x+i,y+j,nCh.type))
	{
		chess nc;
		nc.type = nCh.type;
		nc.x = x;
		nc.y = y;
		x = GetNum(nc, i, j, false);
		if (x != 0)
			t += x + 100; //����100���������Ƿ��м�ϣ������׷���Ƿ�������ʱ�õ�
	}
	return t;
}