#include "DataHandler.h"

DataHandler dataHandler;//全局操作对象
vector<int> winList;//玩家出完牌的序列
string cardList;//玩家的出牌序列
int currentPart = 1;//当前是第几局
Card outCard;//表示还贡的牌
Card inCard;//表示进贡的牌

void dealCards();//发牌阶段
void tributeCard();//进贡阶段
void beforeStart(vector<Card> cardList);//出牌之前的流程，包括同花顺提示，是否展示同花、顺子
void gameStart();//出牌阶段
void gameOver();//一局游戏结束之后牌组的处理

//0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26
int main()
{
	while (true)
	{
		cout << "******************************************************************************************* 第" << currentPart++ << "局 "
			<< "******************************************************************************************" << endl << endl;

		if (dataHandler.currentWin == "A")
		{
			cout << "当前打【玩家1】【玩家3】的" << dataHandler.currentMainCard << endl;
		}
		else if (dataHandler.currentWin == "B")
		{
			cout << "当前打【玩家2】【玩家4】的" << dataHandler.currentMainCard << endl;
		}

		//发牌阶段
		dealCards();

		//为了测试进还贡牌的合法性
		//winList.push_back(1);
		//winList.push_back(3);
		//winList.push_back(2);
		//winList.push_back(4);

		//开始游戏之前进贡
		/*tributeCard();*/
		winList.clear();
		//开始游戏进行出牌
		gameStart();
	}
	return 0;
}

void dealCards()
{
	dataHandler.dealCard();

	dataHandler.sortPlayerCardList(dataHandler.player_1);
	dataHandler.sortPlayerCardList(dataHandler.player_2);
	dataHandler.sortPlayerCardList(dataHandler.player_3);
	dataHandler.sortPlayerCardList(dataHandler.player_4);
}

void tributeCard()
{
	//处于进贡阶段
	//表示3 4名是一组的，要双贡
	if (winList.size() == 4)
	{
		if (dataHandler.isPartner(winList[2], winList[3]))
		{
			//如果3 4名加起来有两张大王，则抗贡
			if (dataHandler.cardExist(winList[2], 200) + dataHandler.cardExist(winList[3], 200) == 2)
			{
				cout << "玩家：" << winList[2] << "与玩家：" << winList[3] << "抗贡！" << endl;
				return;
			}

			//****************************** 第三名向第一名进贡 ******************************
			vector<Card> thirdWin = dataHandler.getPlayerCardList(winList[2]);
			cout << "玩家：" << winList[2] << "的牌组如下：" << endl;
			dataHandler.displayPlayerCardList(thirdWin);

			while (true)
			{
				cout << "请【第三名】玩家：" << winList[2] << "进贡：";
				cin >> cardList;
				outCard = thirdWin[atoi(cardList.c_str())];
				if (dataHandler.tributeValid(winList[2], outCard))
				{
					break;
				}
			}
			dataHandler.handlePlayer(winList[2], cardList);

			cout << "【第一名】玩家：" << winList[0] << "收到进贡牌：" << dataHandler.cardToString(outCard) << endl;
			dataHandler.insertCardList(winList[0], outCard);
			cout << "玩家：" << winList[0] << "的牌组如下：" << endl;
			vector<Card> firstWin = dataHandler.getPlayerCardList(winList[0]);
			dataHandler.displayPlayerCardList(firstWin);

			while (true)
			{
				cout << "请【第一名】玩家：" << winList[0] << "还贡：";
				cin >> cardList;
				inCard = firstWin[atoi(cardList.c_str())];//字符串转化为整形，
				if (dataHandler.returnValid(inCard))
				{
					break;
				}
			}
			dataHandler.handlePlayer(winList[0], cardList);

			cout << "玩家：" << winList[0] << "的牌组如下：" << endl;
			dataHandler.displayPlayerCardList((dataHandler.getPlayerCardList(winList[0])));

			cout << "【第三名】玩家：" << winList[2] << "收到还贡牌：" << dataHandler.cardToString(inCard) << endl;
			dataHandler.insertCardList(winList[2], inCard);
			cout << "玩家：" << winList[2] << "的牌组如下：" << endl;
			dataHandler.displayPlayerCardList((dataHandler.getPlayerCardList(winList[2])));

			//****************************** 第四名向第二名进贡 ******************************
			vector<Card> fourthWin = dataHandler.getPlayerCardList(winList[3]);
			cout << "玩家：" << winList[3] << "的牌组如下：" << endl;
			dataHandler.displayPlayerCardList(fourthWin);

			while (true)
			{
				cout << "请【第四名】玩家：" << winList[3] << "进贡：";
				cin >> cardList;
				outCard = fourthWin[atoi(cardList.c_str())];
				if (dataHandler.tributeValid(winList[3], outCard))
				{
					break;
				}
			}
			dataHandler.handlePlayer(winList[3], cardList);

			cout << "【第二名】玩家：" << winList[1] << "收到进贡牌：" << dataHandler.cardToString(outCard) << endl;
			dataHandler.insertCardList(winList[1], outCard);
			cout << "玩家：" << winList[1] << "的牌组如下：" << endl;
			vector<Card> secondWin = dataHandler.getPlayerCardList(winList[1]);
			dataHandler.displayPlayerCardList(secondWin);

			while (true)
			{
				cout << "请【第二名】玩家：" << winList[1] << "还贡：";
				cin >> cardList;
				inCard = secondWin[atoi(cardList.c_str())];
				if (dataHandler.returnValid(inCard))
				{
					break;
				}
			}
			dataHandler.handlePlayer(winList[1], cardList);

			cout << "玩家：" << winList[1] << "的牌组如下：" << endl;
			dataHandler.displayPlayerCardList((dataHandler.getPlayerCardList(winList[1])));

			cout << "【第四名】玩家：" << winList[3] << "收到还贡牌：" << dataHandler.cardToString(inCard) << endl;
			dataHandler.insertCardList(winList[3], inCard);
			cout << "玩家：" << winList[3] << "的牌组如下：" << endl;
			dataHandler.displayPlayerCardList((dataHandler.getPlayerCardList(winList[3])));

			return;
		}

		//如果第4名有两张大王，则抗贡
		if (dataHandler.cardExist(winList[3], 200) == 2)
		{
			cout << "玩家：" << winList[3] << "抗贡！" << endl;
			return;
		}

		//如果不是双进贡，则只有第四名玩家进贡给第一名玩家
		vector<Card> fourthWin = dataHandler.getPlayerCardList(winList[3]);
		cout << "玩家：" << winList[3] << "的牌组如下：" << endl;
		dataHandler.displayPlayerCardList(fourthWin);

		while (true)
		{
			cout << "请【第四名】玩家：" << winList[3] << "进贡：";
			cin >> cardList;
			outCard = fourthWin[atoi(cardList.c_str())];
			if (dataHandler.tributeValid(winList[3], outCard))
			{
				break;
			}
		}
		dataHandler.handlePlayer(winList[3], cardList);

		cout << "【第一名】玩家：" << winList[0] << "收到进贡牌：" << dataHandler.cardToString(outCard) << endl;
		dataHandler.insertCardList(winList[0], outCard);
		cout << "玩家：" << winList[0] << "的牌组如下：" << endl;
		vector<Card> firstWin = dataHandler.getPlayerCardList(winList[0]);
		dataHandler.displayPlayerCardList(firstWin);

		while (true)
		{
			cout << "请【第一名】玩家：" << winList[0] << "还贡：";
			cin >> cardList;
			inCard = firstWin[atoi(cardList.c_str())];
			if (dataHandler.returnValid(inCard))
			{
				break;
			}
		}
		dataHandler.handlePlayer(winList[0], cardList);

		cout << "玩家：" << winList[0] << "的牌组如下：" << endl;
		dataHandler.displayPlayerCardList((dataHandler.getPlayerCardList(winList[0])));

		cout << "【第四名】玩家：" << winList[3] << "收到进贡牌：" << dataHandler.cardToString(inCard) << endl;
		dataHandler.insertCardList(winList[3], inCard);
		cout << "玩家：" << winList[3] << "的牌组如下：" << endl;
		dataHandler.displayPlayerCardList((dataHandler.getPlayerCardList(winList[3])));
	}
}

void beforeStart(vector<Card> cardList)
{
	string isShowList;
	dataHandler.displayPlayerCardList(cardList);
	dataHandler.calculateStraightFlush(cardList);
	cout << "是否选择展示顺子、同花序列：【Y/N】";
	cin >> isShowList;
	if (isShowList == "Y")
	{
		cout << "同花展示：" << endl;
		dataHandler.sortCardKey(cardList);
		dataHandler.displayPlayerCardList(cardList);
		cout << "顺子展示：" << endl;
		dataHandler.sortPlayerCardList(cardList);
		dataHandler.displayPlayerCardList(cardList);
	}
}

void gameStart()
{
	while (true)
	{
		if (dataHandler.player_1.size())
		{
			beforeStart(dataHandler.player_1);
			cout << "【玩家1】请输入出牌序列：";
			cin >> cardList;
			cout << "玩家出牌：";
			dataHandler.handlePlayer(1, cardList);
			cout << "玩家1的牌组：" << endl;
			dataHandler.displayPlayerCardList(dataHandler.player_1);
			cout << "---------------------------------------------------------------------------------------------------"
				<< "------------------------------------------------------------------------------------------" << endl << endl;
			if (dataHandler.player_1.size() == 0)
			{
				winList.push_back(1);
			}
		}

		if (dataHandler.player_2.size())
		{
			beforeStart(dataHandler.player_2);
			cout << "【玩家2】请输入出牌序列：";
			cin >> cardList;
			cout << "玩家出牌：";
			dataHandler.handlePlayer(2, cardList);
			cout << "玩家2的牌组：" << endl;
			dataHandler.displayPlayerCardList(dataHandler.player_2);
			cout << "---------------------------------------------------------------------------------------------------"
				<< "------------------------------------------------------------------------------------------" << endl << endl;
			if (dataHandler.player_2.size() == 0)
			{
				winList.push_back(2);
			}
		}

		if (dataHandler.player_3.size())
		{
			beforeStart(dataHandler.player_3);
			cout << "【玩家3】请输入出牌序列：";
			cin >> cardList;
			cout << "玩家出牌：";
			dataHandler.handlePlayer(3, cardList);
			cout << "玩家3的牌组：" << endl;
			dataHandler.displayPlayerCardList(dataHandler.player_3);
			cout << "---------------------------------------------------------------------------------------------------"
				<< "------------------------------------------------------------------------------------------" << endl << endl;
			if (dataHandler.player_3.size() == 0)
			{
				winList.push_back(3);
			}
		}

		if (dataHandler.player_4.size())
		{
			beforeStart(dataHandler.player_4);
			cout << "【玩家4】请输入出牌序列：";
			cin >> cardList;
			cout << "玩家出牌：";
			dataHandler.handlePlayer(4, cardList);
			cout << "玩家4的牌组：" << endl;
			dataHandler.displayPlayerCardList(dataHandler.player_4);
			cout << "---------------------------------------------------------------------------------------------------"
				<< "------------------------------------------------------------------------------------------" << endl << endl;
			if (dataHandler.player_4.size() == 0)
			{
				winList.push_back(4);
			}
		}

		if (dataHandler.gameOver())
		{
			cout << "本局游戏结束！" << endl;
			gameOver();
			break;
		}
	}
}

void gameOver()
{
	//处理剩下的没有出完牌的玩家编号
	if (dataHandler.player_1.size())
	{
		winList.push_back(1);
	}
	if (dataHandler.player_2.size())
	{
		winList.push_back(2);
	}
	if (dataHandler.player_3.size())
	{
		winList.push_back(3);
	}
	if (dataHandler.player_4.size())
	{
		winList.push_back(4);
	}
	dataHandler.handleWinner(winList[0], winList[1], winList[2], winList[3]);
	dataHandler.player_1.clear();
	dataHandler.player_2.clear();
	dataHandler.player_3.clear();
	dataHandler.player_4.clear();
}