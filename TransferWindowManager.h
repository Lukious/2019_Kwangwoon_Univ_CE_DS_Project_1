
#include "BinarySearchTree.h"

#include <iostream>
#include <string>
#include <queue>
#include <vector>

class TransferWindowManager
{
private:
	int m_budget;

	BinarySearchTree fwBST;
	BinarySearchTree mfBST;
	BinarySearchTree dfBST;
	BinarySearchTree gkBST;

public:

	struct SoccerTeam
	{
		SoccerPlayerData fw;
		SoccerPlayerData mf;
		SoccerPlayerData df;
		SoccerPlayerData gk;

		int sum_transfer_fee;
		int sum_ability;

		SoccerTeam();
		SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk);
		friend std::ostream& operator<<(std::ostream& os, const SoccerTeam& team);
	};

	TransferWindowManager(std::string file_dir, int budget);
	

	friend std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager);

	//void removePlayer(SoccerPlayerData data);

	SoccerTeam getBestTeam();

	//std::priority_queue<SoccerPlayerData, std::vector<SoccerPlayerData>, > all_player_queue;

	SoccerPlayerData split(const std::string &s);

	void insertPlayer(SoccerPlayerData data);

	struct cmp
	{
		bool operator()(SoccerPlayerData a, SoccerPlayerData b)
		{
			return a.m_ability > b.m_ability;
		}
	};
};

