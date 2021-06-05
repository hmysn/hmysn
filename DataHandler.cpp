#include "DataHandler.h"

DataHandler::DataHandler()
{
	//初始化牌组为顺序的108张牌
	for (int i = 1; i <= 13; i++)
	{
		originalList.push_back(i);
		originalList.push_back(i);
	}
	for (int i = 21; i <= 33; i++)
	{
		originalList.push_back(i);
		originalList.push_back(i);
	}
	for (int i = 41; i <= 53; i++)
	{
		originalList.push_back(i);
		originalList.push_back(i);
	}
	for (int i = 61; i <= 73; i++)
	{
		originalList.push_back(i);
		originalList.push_back(i);
	}
	originalList.push_back(100);
	originalList.push_back(100);
	originalList.push_back(200);
	originalList.push_back(200);

	//初始化两方的主牌
	mainFirst = "2";
	mainSecond = "2";
	currentMainCard = "2";
	currentWin = "NULL";
	lastWin = "NULL";
	firstPlayTime = 0;
	secondPlayTime = 0;
}

DataHandler::~DataHandler()
{
}

string DataHandler::getCardType(int cardType)
{
	if (cardType == 0)
	{
		return "黑桃";
	}
	if (cardType == 20)
	{
		return "红桃";
	}
	if (cardType == 40)
	{
		return "梅花";
	}
	if (cardType == 60)
	{
		return "方片";
	}
	if (cardType == 100)
	{
		return "小王";
	}
	if (cardType == 200)
	{
		return "大王";
	}
	return string();
}

string DataHandler::getCardNumber(int cardNumber)
{
	if (cardNumber == 1)
	{
		return "A";
	}
	if (cardNumber == 11)
	{
		return "J";
	}
	if (cardNumber == 12)
	{
		return "Q";
	}
	if (cardNumber == 13)
	{
		return "K";
	}
	if (cardNumber == 0)
	{
		return "";
	}
	return IntToString(cardNumber);
}

int DataHandler::getCardType(string cardType)
{
	if (cardType == "黑桃")
	{
		return 0;
	}
	if (cardType == "红桃")
	{
		return 20;
	}
	if (cardType == "梅花")
	{
		return 40;
	}
	if (cardType == "方片")
	{
		return 60;
	}
	if (cardType == "小王")
	{
		return 100;
	}
	if (cardType == "大王")
	{
		return 200;
	}
	return -1;
}

int DataHandler::getCardNumber(string cardNumber)
{
	if (cardNumber == "A")
	{
		return 1;
	}
	if (cardNumber == "J")
	{
		return 11;
	}
	if (cardNumber == "Q")
	{
		return 12;
	}
	if (cardNumber == "K")
	{
		return 13;
	}
	if (cardNumber == "")
	{
		return 0;
	}
	return atoi(cardNumber.c_str());
}

string DataHandler::IntToString(int number)
{
	string str;
	stringstream ss;
	ss << number;
	ss >> str;
	return str;
}

Card DataHandler::keyToCard(int key)
{
	Card card;
	card.cardType = getCardType(key / 20 * 20);
	card.cardNumber = getCardNumber(key % 20);
	card.cardKey = key;
	return card;
}

string DataHandler::keyToString(int key)
{
	return getCardType(key / 20 * 20) + getCardNumber(key % 20);
}

int DataHandler::cardToKey(Card card)
{
	return getCardType(card.cardType) + getCardNumber(card.cardNumber);
}

string DataHandler::cardToString(Card card)
{
	return card.cardType + card.cardNumber;
}

int DataHandler::stringToKey(string str)
{
	string cardType = str.substr(0, 4);
	string cardNumber = str.substr(4, 1);
	return getCardType(cardType) + getCardNumber(cardNumber);
}

Card DataHandler::stringToCard(string str)
{
	string cardType = str.substr(0, 4);
	string cardNumber = str.substr(4, 1);
	Card card;
	card.cardType = cardType;
	card.cardNumber = cardNumber;
	card.cardKey = getCardType(cardType) + getCardNumber(cardNumber);
	return card;
}

void DataHandler::outOrderOriginalList()//乱序
{
	srand((unsigned int)time(0));
	random_shuffle(originalList.begin(), originalList.end()); // STL中的函数random_shuffle()用来对一个元素序列进行重新排序（随机的）
}

void DataHandler::displayOriginalList()//乱序后的108张牌
{
	for (int i = 0; i < originalList.size(); i++)
	{
		cout << keyToString(originalList[i]) << "  ";
		if (i % 10 == 0 && i)
		{
			cout << endl;
		}
	}
}

void DataHandler::displayPlayerCardList(const vector<Card> list)//输出最终版
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << "【" << i << "】" << cardToString(list[i]) << "  ";
	}
	cout << endl << endl << endl;
}

bool DataHandler::compareNumber(Card a, Card b)//大小排序
{
	int numberA = getCardNumber(a.cardNumber);
	int numberB = getCardNumber(b.cardNumber);
	if (numberA == 0 && numberB == 0)
	{
		return a.cardKey < b.cardKey;
	}
	return numberA < numberB;
}

bool DataHandler::compareKey(Card a, Card b)//花色排序
{
	return a.cardKey < b.cardKey;
}

void DataHandler::sortPlayerCardList(vector<Card>& list)//大小排序
{
	sort(list.begin(), list.end(), compareNumber);
}

void DataHandler::sortCardKey(vector<Card>& list)//花色排序
{
	sort(list.begin(), list.end(), compareKey);
}

void DataHandler::dealCard()//分配给四个玩家
{
	outOrderOriginalList();
	for (int i = 0; i < 27; i++)
	{
		player_1.push_back(keyToCard(originalList[i]));
	}
	for (int i = 27; i < 54; i++)
	{
		player_2.push_back(keyToCard(originalList[i]));
	}
	for (int i = 54; i < 81; i++)
	{
		player_3.push_back(keyToCard(originalList[i]));
	}
	for (int i = 81; i < 108; i++)
	{
		player_4.push_back(keyToCard(originalList[i]));
	}
}

void DataHandler::splitString(string srcString, char splitFlag, vector<string>& stringVector)
{
	stringstream ss(srcString);
	string splitString;
	while (getline(ss, splitString, splitFlag))
	{
		stringVector.push_back(splitString);
	}
}

void DataHandler::handlePlayer(int playerNumber, string cardList)
{
	vector<string> putList;
	splitString(cardList, ',', putList);
	if (find(putList.begin(), putList.end(), "-1") != putList.end())
	{
		cout << "过牌！" << endl;
		return;
	}
	vector<int> intList;
	for (int i = 0; i < putList.size(); i++)
	{
		intList.push_back(atoi(putList[i].c_str()));
	}
	if (playerNumber == 1)
	{
		for (auto& i : intList)//遍历循环
		{
			cout << cardToString(player_1[i]) << "  ";
			if (player_1[i].cardNumber == currentMainCard && player_1[i].cardType == "红桃")
			{
				cout << cardToString(player_1[i]) << "是逢人配  ";
			}
		}
		cout << endl;
		removeCard(player_1, intList);
	}
	if (playerNumber == 2)
	{
		for (auto& i : intList)
		{
			cout << cardToString(player_2[i]) << "  ";
			if (player_2[i].cardNumber == currentMainCard && player_2[i].cardType == "红桃")
			{
				cout << cardToString(player_2[i]) << "是逢人配  ";
			}
		}
		cout << endl;
		removeCard(player_2, intList);
	}
	if (playerNumber == 3)
	{
		for (auto& i : intList)
		{
			cout << cardToString(player_3[i]) << "  ";
			if (player_3[i].cardNumber == currentMainCard && player_3[i].cardType == "红桃")
			{
				cout << cardToString(player_3[i]) << "是逢人配  ";
			}
		}
		cout << endl;
		removeCard(player_3, intList);
	}
	if (playerNumber == 4)
	{
		for (auto& i : intList)
		{
			cout << cardToString(player_4[i]) << "  ";
			if (player_4[i].cardNumber == currentMainCard && player_4[i].cardType == "红桃")
			{
				cout << cardToString(player_4[i]) << "是逢人配  ";
			}
		}
		cout << endl;
		removeCard(player_4, intList);
	}
}

void DataHandler::removeCard(vector<Card>& list, vector<int> cardList)//从手牌中移除出掉的牌
{
	for (auto& i : cardList)
	{
		list[i].cardKey = -1;
	}
	vector<Card> result;
	for (auto& i : list)
	{
		if (i.cardKey != -1)
		{
			result.push_back(i);
		}
	}
	list = result;
}

bool DataHandler::gameOver()//游戏结束判定
{
	if ((player_1.size() == 0 && player_3.size() == 0) || (player_2.size() == 0 && player_4.size() == 0))
	{
		return true;
	}
	return false;
}

void DataHandler::handleWinner(int first, int second, int third, int fourth)
{
	int level = 0;
	if (first == 1 || first == 3)
	{
		currentWin = "A";
		if (second == 1 || second == 3)
		{
			level = 3;
		}
		else if (third == 1 && third == 3)
		{
			level = 2;
		}
		else
		{
			level = 1;
		}
	}
	else
	{
		currentWin = "B";
		if (second == 2 || second == 4)
		{
			level = 3;
		}
		else if (third == 2 && third == 4)
		{
			level = 2;
		}
		else
		{
			level = 1;
		}
	}
	if (currentWin == "A")
	{
		mainFirst = calculateLevel(mainFirst, level);
		if (mainFirst == "A")
		{
			firstPlayTime++;
		}
		if (firstPlayTime > 1 && level >0 && lastWin == currentWin)
		{
			cout << "掼蛋游戏到此结束，【玩家1】【玩家3】获得最终胜利！" << endl;
			exit(0);
		}
		lastWin = currentWin;
		if (firstPlayTime == 4)
		{
			firstPlayTime = 0;
			mainFirst = "2";
		}
		currentMainCard = mainFirst;
	}
	else
	{
		mainSecond = calculateLevel(mainSecond, level);
		if (mainSecond == "A")
		{
			secondPlayTime++;
		}
		if (secondPlayTime > 1 && level == 3 && lastWin == currentWin)
		{
			cout << "掼蛋游戏到此结束，【玩家2】【玩家4】获得最终胜利！" << endl;
			exit(0);
		}
		lastWin = currentWin;
		if (secondPlayTime == 4)
		{
			secondPlayTime = 0;
			mainSecond = "2";
		}
		currentMainCard = mainSecond;
	}
}

string DataHandler::calculateLevel(string mainCard, int level)
{
	static string levelRule[13] = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };
	int currentIndex = 0;
	for (int i = 0; i < 13; i++)
	{
		if (levelRule[i] == mainCard)
		{
			currentIndex = i;
			break;
		}
	}
	currentIndex += level;
	if (currentIndex >= 12)
	{
		return "A";
	}
	return levelRule[currentIndex];
}

bool DataHandler::isPartner(int playerA, int playerB)
{
	if (playerA + playerB == 4 || playerA + playerB == 6)
	{
		return true;
	}
	return false;
}

vector<Card> DataHandler::getPlayerCardList(int number)
{
	if (number == 1)
	{
		return player_1;
	}
	if (number == 2)
	{
		return player_2;
	}
	if (number == 3)
	{
		return player_3;
	}
	if (number == 4)
	{
		return player_4;
	}
}

void DataHandler::insertCardList(int playerNumber, Card card)
{
	if (playerNumber == 1)
	{
		player_1.push_back(card);
	}
	if (playerNumber == 2)
	{
		player_2.push_back(card);
	}
	if (playerNumber == 3)
	{
		player_3.push_back(card);
	}
	if (playerNumber == 4)
	{
		player_4.push_back(card);
	}
}

int DataHandler::cardExist(int playerNumber, int cardKey)
{
	int cardCount = 0;
	vector<Card> tmpVec = getPlayerCardList(playerNumber);
	for ( auto& i :tmpVec)
	{
		if (i.cardKey == cardKey)
		{
			cardCount++;
		}
	}
	return cardCount;
}

bool DataHandler::tributeValid(int playerNumber, Card card)
{
	if (card.cardNumber == currentMainCard && card.cardType == "红桃")
	{
		cout << "不可进贡红桃主牌！" << endl;
		return false;
	}

	vector<Card> tmpVec = getPlayerCardList(playerNumber);
	sortPlayerCardList(tmpVec);

	//判断是否有大王在手
	if (cardExist(playerNumber, 200) > 0)
	{
		if (card.cardKey != 200)
		{
			cout << "必须进贡大王！" << endl;
			return false;
		}
		return true;
	}
	//判断是否有小王在手
	if (cardExist(playerNumber, 100) > 0)
	{
		if (card.cardKey != 100)
		{
			cout << "必须进贡小王！" << endl;
			return false;
		}
		return true;
	}
	//判断当前是否有主牌在手
	for (int i = 0; i < tmpVec.size(); i++)
	{
		if (tmpVec[i].cardNumber == currentMainCard && tmpVec[i].cardType != "红桃")
		{
			if (card.cardNumber != currentMainCard)
			{
				cout << "必须进贡非红桃主牌！" << endl;
				return false;
			}
			return true;
		}
	}
	//如果没有大王，小王，主牌，就判断是否有A在手
	if (currentMainCard != "A")
	{
		for (int i = 0; i < tmpVec.size(); i++)
		{
			if (tmpVec[i].cardNumber == "A")
			{
				if (card.cardNumber != "A")
				{
					cout << "必须进贡A！" << endl;
					return false;
				}
				return true;
			}
		}
	}
	//如果一副牌没有大小王或者主牌，最大值也不是A，找整副牌中数值最大的
	Card maxCard = tmpVec[26];
	if (maxCard.cardNumber != card.cardNumber)
	{
		cout << "必须进贡" << maxCard.cardNumber << "！" << endl;
		return false;
	}
	return true;
}

bool DataHandler::returnValid(Card card)
{
	//如果数值大于10
	if (card.cardNumber == "J" || card.cardNumber == "Q" || card.cardNumber == "K" || card.cardNumber == "A")
	{
		cout << "不可还贡大于10的牌！" << endl;
		return false;
	}
	//如果还贡的是主牌
	if (card.cardNumber == currentMainCard)
	{
		cout << "不可还贡主牌！" << endl;
		return false;
	}
	//如果还贡的牌是王牌
	if (card.cardNumber == "")
	{
		cout << "不可还贡王牌！" << endl;
		return false;
	}
	return true;
}

string DataHandler::getOrderTail(string cardNumber)
{
	if (cardNumber == "A")
	{
		return "5";
	}
	if (cardNumber == "2")
	{
		return "6";
	}
	if (cardNumber == "3")
	{
		return "7";
	}
	if (cardNumber == "4")
	{
		return "8";
	}
	if (cardNumber == "5")
	{
		return "9";
	}
	if (cardNumber == "6")
	{
		return "10";
	}
	if (cardNumber == "7")
	{
		return "J";
	}
	if (cardNumber == "8")
	{
		return "Q";
	}
	if (cardNumber == "9")
	{
		return "K";
	}
	if (cardNumber == "10")
	{
		return "A";
	}
	return "";
}

void DataHandler::calculateStraightFlush(vector<Card> cardList)
{
	//首先对牌组按照key值排序，寻找同花顺，如果找到就打印牌的数据
	bool haveFound = false;
	sortCardKey(cardList);
	for (int i = 0; i <= cardList.size() - 5; i++)
	{
		int firstCard = i;
		if (firstCard + 1 > cardList.size() - 1)
		{
			if (!haveFound)
			{
				cout << "没有同花顺！" << endl;
			}
			return;
		}
		int secondCard = cardList[firstCard + 1].cardKey == cardList[firstCard].cardKey ? (firstCard + 2) : (firstCard + 1);
		if (secondCard + 1 > cardList.size() - 1)
		{
			if (!haveFound)
			{
				cout << "没有同花顺！" << endl;
			}
			return;
		}
		int thirdCard = cardList[secondCard + 1].cardKey == cardList[secondCard].cardKey ? (secondCard + 2) : (secondCard + 1);
		if (thirdCard + 1 > cardList.size() - 1)
		{
			if (!haveFound)
			{
				cout << "没有同花顺！" << endl;
			}
			return;
		}
		int fourthCard = cardList[thirdCard + 1].cardKey == cardList[thirdCard].cardKey ? (thirdCard + 2) : (thirdCard + 1);
		if (fourthCard + 1 > cardList.size() - 1)
		{
			if (!haveFound)
			{
				cout << "没有同花顺！" << endl;
			}
			return;
		}
		int fifthCard = cardList[fourthCard + 1].cardKey == cardList[fourthCard].cardKey ? (fourthCard + 2) : (fourthCard + 1);
		if (fifthCard + 1 > cardList.size() - 1)
		{
			if (!haveFound)
			{
				cout << "没有同花顺！" << endl;
			}
			return;
		}

		int step_1 = cardList[secondCard].cardKey - cardList[firstCard].cardKey;
		int step_2 = cardList[thirdCard].cardKey - cardList[secondCard].cardKey;
		int step_3 = cardList[fourthCard].cardKey - cardList[thirdCard].cardKey;
		int step_4 = cardList[fifthCard].cardKey - cardList[fourthCard].cardKey;

		if (step_1 == 1 && step_2 == 1 && step_3 == 1 && (step_4 == 1 || step_4 == -12))
		{
			haveFound = true;
			cout << cardToString(cardList[firstCard]) << "  " << cardToString(cardList[secondCard]) << "  " << cardToString(cardList[thirdCard]) << "  "
				<< cardToString(cardList[fourthCard]) << "  " << cardToString(cardList[fifthCard]) << endl;
		}
	}
	if (!haveFound)
	{
		cout << "没有同花顺！" << endl;
	}
	//同花顺的过程执行完毕之后，需要把牌组的顺序还原
	sortPlayerCardList(cardList);
}
