#pragma once
class chess
{
public:
	chess();
	virtual ~chess(){};
	int x, y;//�����������е�����
	int type;//0Ϊ���壬1Ϊ����
};
class Managers
{
public:
	Managers();
	~Managers();
public:
	bool GameType(int t); //�ı���Ϸ��GameInfo
	chess GetLastChe();//�������һ���µ����ӵ���Ϣ
	int CheckState();//����Ƿ���ʤ������ʧ�ܣ�Ϊ0ʲô����������Ϊ������ʾʤ����Ϊ������ʾʧ��
	//bool GameBack(int step = 2);//����steps�Ƕ��٣�����һ������û����
	void GameStart();//��ʼ����ʼ
	bool AddChess(int x, int y);//��map�����������ӣ����ɹ� ����true�����ɹ�����false
	bool DoMsg(int x, int y, int action);//��Ϣ��Ӧ
	//friend class Computer;//����һ������AI����Ԫ����������AI���Ժ���������AI����

public:
	chess LastCh; //��һ����껮����������Ϣ
	int map[15][15];//��Ϸ��ͼ��-1Ϊû�����ӣ�0�Ǻ��壬1�ǰ���
							//������ʾ����Ҫ������Ҫ��ѡ�еĵط����и����ԣ����Թ涨
							//99����ѡ��ĳ�հ�����ͬ��100��101��ѡ�кڻ����
	int nKeyDown; //�Ѿ����˶��ٲ����ߵĲ���ΪnKeyDown-1
	int Game_State; //��Ϸ״̬
							//1����Ϸ��Player1���� Player1һ������
							//2����Ϸ��Player2���� �����ʾ�����ǵ��� ��������
							//3����Ϸ��������ɫӮ
							//4����Ϸ��������ɫӮ
							//5����Ϸ������ƽ��
							//other number ����û��ʼ
	bool PAUSE; //��Ϸ�Ƿ���ͣ

private:
	bool Updata(); //��Ϸ����
	bool CheckMap(int x, int y, int pow); //�����鿴��Ϸ��ͼmap[x][y]�Ƿ��pow���
	int Gameinfo;//�����Ϣ ��һ����λ��������
						//��λ��0��ʾPlayer1���Ǻ�ɫ��1��ʾPlayer2���ǰ�ɫ
						//ʮλ1��ʾ��һ������Ǽ������0��ʾ��һ��������û�
						//�����Ϣ��Ӱ����Ϸ����Updata����
	chess nChessinfo[226]; //ÿ�����ÿ���ߵ��壬���ڼ�¼Ҳ������ʾ
protected:
	//bool ForbidLoc(chess k); //�ж�K��������Ƿ���ɽ���
	int GetNum(chess nCh, int i, int j, bool goon);//��������������ã����ڼ��nChzai��i��j�������������
};

