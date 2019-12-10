#include "TransferWindowManager.h"
#include <fstream>
#include <string>
#include <sstream>

TransferWindowManager::SoccerTeam::SoccerTeam()
{
	//You don't need to edit this function.
}

TransferWindowManager::SoccerTeam::SoccerTeam(SoccerPlayerData fw, SoccerPlayerData mf, SoccerPlayerData df, SoccerPlayerData gk)
{
	this->fw = fw;
	this->mf = mf;
	this->df = df;
	this->gk = gk;

	this->sum_transfer_fee = fw.m_transfer_fee + mf.m_transfer_fee + df.m_transfer_fee + gk.m_transfer_fee;
	this->sum_ability = fw.m_ability + mf.m_ability + df.m_ability + gk.m_ability;
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager::SoccerTeam& team)
{
	os << team.fw << std::endl;
	os << team.mf << std::endl;
	os << team.df << std::endl;
	os << team.gk << std::endl;

	os << "sum_transfer_fee " << team.sum_transfer_fee << std::endl;
	os << "sum_ability " << team.sum_ability << std::endl;

	return os;
}


TransferWindowManager::TransferWindowManager(std::string file_dir, int budget)
{
	m_budget = budget;

	std::ifstream in(file_dir);
	std::string line;

	while (std::getline(in, line))
	{
		//Fill in the code to initialize 4 Binary Search Trees(fw, mf, df, gk)

		SoccerPlayerData data = split(line);

		insertPlayer(data);
	}
}

void TransferWindowManager::insertPlayer(SoccerPlayerData data)
{
	if (data.m_position == "Forward")
		fwBST.insert(data);
	else if (data.m_position == "Midfielder")
		mfBST.insert(data);
	else if (data.m_position == "Defender")
		dfBST.insert(data);
	else //if (data.m_position == "Goalkeeper"
		gkBST.insert(data);
}

SoccerPlayerData TransferWindowManager::split(const std::string &s)
{
	std::stringstream ss(s);
	std::string str;
	SoccerPlayerData spdata;

	// name, position, fee, ability
	std::getline(ss, str, ',');
	spdata.m_name = str;

	std::getline(ss, str, ',');
	str.erase(0, 1);
	spdata.m_position = str;

	std::getline(ss, str, ',');
	str.erase(0, 1);
	spdata.m_transfer_fee = std::stoi(str);

	std::getline(ss, str, ',');
	str.erase(0, 1);
	spdata.m_ability = std::stoi(str);

	return spdata;
}

std::ostream& operator<<(std::ostream& os, const TransferWindowManager& manager)
{
	os << "********Forward List********" << std::endl;
	os << manager.fwBST;
	os << "****************************" << std::endl;

	os << "********Midflder List********" << std::endl;
	os << manager.mfBST;
	os << "*****************************" << std::endl;

	os << "********Defender List********" << std::endl;
	os << manager.dfBST;
	os << "*****************************" << std::endl;

	os << "********Goalkeeper List********" << std::endl;
	os << manager.gkBST;
	os << "*******************************" << std::endl;

	return os;
}

//void TransferWindowManager::removePlayer(SoccerPlayerData data)
//{
//	if (data.m_position == "Forward")
//		fwBST.deletion(data.m_ability);
//	else if (data.m_position == "Midfielder")
//		mfBST.deletion(data.m_ability);
//	else if (data.m_position == "Defender")
//		dfBST.deletion(data.m_ability);
//	else //if (data.m_position == "Goalkeeper"
//		gkBST.deletion(data.m_ability);
//}

TransferWindowManager::SoccerTeam TransferWindowManager::getBestTeam()
{
	SoccerTeam best_team;
	
	//Fill in the code to search the best_team from 4 BSTs
	//The datas for best team must be stored in the variable best_team.
	//*best team means the most powerful team that is defined in the project introduction file. 
	
	SoccerPlayerData temp = SoccerPlayerData("", "", 0, 0);
	best_team = SoccerTeam(temp, temp, temp, temp);

	// Input player in each position vector
	std::vector<SoccerPlayerData> fw_vector;
	std::vector<SoccerPlayerData> mf_vector;
	std::vector<SoccerPlayerData> df_vector;
	std::vector<SoccerPlayerData> gk_vector;

	fwBST.make_vector(fw_vector);
	mfBST.make_vector(mf_vector);
	dfBST.make_vector(df_vector);
	gkBST.make_vector(gk_vector);

	// Full search
	for (auto fwit = fw_vector.begin(); fwit != fw_vector.end(); fwit++)
	{
		for (auto mfit = mf_vector.begin(); mfit != mf_vector.end(); mfit++)
		{
			for (auto dfit = df_vector.begin(); dfit != df_vector.end(); dfit++)
			{
				for (auto gkit = gk_vector.begin(); gkit != gk_vector.end(); gkit++)
				{
					SoccerTeam new_team = SoccerTeam(*fwit, *mfit, *dfit, *gkit);

					// Team that can be merged in budget
					if (new_team.sum_transfer_fee <= m_budget)
					{
						// If sum of ability is higher than previous best team
						if (new_team.sum_ability > best_team.sum_ability)
						{
							// replace
							best_team = new_team;
						}
						// if sum of ability is same
						else if (new_team.sum_ability == best_team.sum_ability)
						{
							// check price
							if (new_team.sum_transfer_fee < best_team.sum_transfer_fee)
							{
								// replace best team
								best_team = new_team;
							}
						}
					}
				}

			}

		}

	}

	//// init­
	//best_team = SoccerTeam(fw_queue.front(), mf_queue.front(), df_queue.front(), gk_queue.front());
	//
	//fw_queue.pop();
	//mf_queue.pop();
	//df_queue.pop();
	//gk_queue.pop();

	//// SEarch for limit
	//while (best_team.sum_transfer_fee > m_budget)
	//{
	//	SoccerPlayerData target_player;
	//	int value = 0;
	//	std::pair<int, int> gap_list[4];

	//	if (!fw_queue.empty())
	//	{
	//		gap_list[0] = std::make_pair(best_team.fw.m_transfer_fee - fw_queue.front().m_transfer_fee, 0);
	//	}
	//	else
	//	{
	//		gap_list[0] = std::make_pair(99999, 0);
	//	}

	//	if (!mf_queue.empty())
	//	{
	//		gap_list[1] = std::make_pair(best_team.mf.m_transfer_fee - mf_queue.front().m_transfer_fee, 1);
	//	}
	//	else
	//	{
	//		gap_list[1] = std::make_pair(99999, 1);
	//	}

	//	if (!df_queue.empty())
	//	{
	//		gap_list[2] = std::make_pair(best_team.df.m_transfer_fee - df_queue.front().m_transfer_fee, 2);
	//	}
	//	else
	//	{
	//		gap_list[2] = std::make_pair(99999, 2);
	//	}

	//	if (!gk_queue.empty())
	//	{
	//		gap_list[3] = std::make_pair(best_team.gk.m_transfer_fee - gk_queue.front().m_transfer_fee, 3);
	//	}
	//	else
	//	{
	//		gap_list[3] = std::make_pair(99999, 3);
	//	}

	//	for (int i = 0; i < 4; i++)
	//	{
	//		for (int k = 0; k < 3 - i; k++)
	//		{
	//			if (gap_list[k].first > gap_list[k + 1].first)
	//			{
	//				std::pair<int, int> temp = gap_list[k];
	//				gap_list[k] = gap_list[k + 1];
	//				gap_list[k + 1] = temp;
	//			}
	//		}
	//	}

	//	int i;

	//	for (i = 0; i < 4; i++)
	//	{
	//		if (best_team.sum_transfer_fee - gap_list[i].first <= m_budget)
	//		{
	//			if (gap_list[i].second == 0) // fw
	//			{
	//				best_team = SoccerTeam(fw_queue.front(), best_team.mf, best_team.df, best_team.gk);
	//				fw_queue.pop();
	//				break;
	//			}
	//			else if (gap_list[i].second == 1) // mf
	//			{
	//				best_team = SoccerTeam(best_team.fw, mf_queue.front(), best_team.df, best_team.gk);
	//				mf_queue.pop();
	//				break;
	//			}
	//			else if (gap_list[i].second == 2) // df
	//			{
	//				best_team = SoccerTeam(best_team.fw, best_team.mf, df_queue.front(), best_team.gk);
	//				df_queue.pop();
	//				break;
	//			}
	//			else //if (gap_list[i].second == 3) // gk
	//			{
	//				best_team = SoccerTeam(best_team.fw, best_team.mf, best_team.df, gk_queue.front());
	//				gk_queue.pop();
	//				break;
	//			}
	//		}
	//	}

	//	if (i == 4)
	//	{
	//		if (gap_list[0].second == 0) // fw
	//		{
	//			best_team = SoccerTeam(fw_queue.front(), best_team.mf, best_team.df, best_team.gk);
	//			fw_queue.pop();
	//		}
	//		else if (gap_list[0].second == 1) // mf
	//		{
	//			best_team = SoccerTeam(best_team.fw, mf_queue.front(), best_team.df, best_team.gk);
	//			mf_queue.pop();
	//		}
	//		else if (gap_list[0].second == 2) // df
	//		{
	//			best_team = SoccerTeam(best_team.fw, best_team.mf, df_queue.front(), best_team.gk);
	//			df_queue.pop();
	//		}
	//		else //if (gap_list[0].second == 3) // gk
	//		{
	//			best_team = SoccerTeam(best_team.fw, best_team.mf, best_team.df, gk_queue.front());
	//			gk_queue.pop();
	//		}
	//	}

	//	//SoccerPlayerData target_player;
	//	//int value = 0;
	//	//
	//	//if (!fw_queue.empty())
	//	//{
	//	//	if (value < best_team.fw.m_transfer_fee - fw_queue.front().m_transfer_fee)
	//	//	{
	//	//		target_player = best_team.fw;
	//	//	}
	//	//}

	//	//if (!mf_queue.empty())
	//	//{
	//	//	if (value < best_team.mf.m_transfer_fee - mf_queue.front().m_transfer_fee)
	//	//	{
	//	//		target_player = best_team.mf;
	//	//	}
	//	//}

	//	//if (!df_queue.empty())
	//	//{
	//	//	if (value < best_team.df.m_transfer_fee - df_queue.front().m_transfer_fee)
	//	//	{
	//	//		target_player = best_team.df;
	//	//	}
	//	//}

	//	//if (!gk_queue.empty())
	//	//{
	//	//	if (value < best_team.gk.m_transfer_fee - gk_queue.front().m_transfer_fee)
	//	//	{
	//	//		target_player = best_team.gk;
	//	//	}
	//	//}

	//	//if (target_player.m_ability == 100)
	//	//{

	//	//}

	//	//if (target_player.m_position == "Forward")
	//	//{
	//	//	best_team = SoccerTeam(fw_queue.front(), best_team.mf, best_team.df, best_team.gk);
	//	//	fw_queue.pop();
	//	//}
	//	//else if (target_player.m_position == "Midfielder")
	//	//{
	//	//	best_team = SoccerTeam(best_team.fw, mf_queue.front(), best_team.df, best_team.gk);
	//	//	mf_queue.pop();
	//	//}
	//	//else if (target_player.m_position == "Defender")
	//	//{
	//	//	best_team = SoccerTeam(best_team.fw, best_team.mf, df_queue.front(), best_team.gk);
	//	//	df_queue.pop();
	//	//}
	//	//else //if (target_player.m_position == "Goalkeeper"
	//	//{
	//	//	best_team = SoccerTeam(best_team.fw, best_team.mf, best_team.df, gk_queue.front());
	//	//	gk_queue.pop();
	//	//}
	//}

	fwBST.deletion(best_team.fw.m_ability);
	mfBST.deletion(best_team.mf.m_ability);
	dfBST.deletion(best_team.df.m_ability);
	gkBST.deletion(best_team.gk.m_ability);

	return best_team;
}


