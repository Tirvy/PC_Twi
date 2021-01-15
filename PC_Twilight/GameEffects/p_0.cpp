/*e_Politic::e_Politic(PCtypes in_type){
	type = in_type;
}*/
bool e_Politic::GetQ(GameEffectQs queue){
	if (queue==eq_None)
		return true;
	return false;
} 
string e_Politic::GetEffect(){
	return effect;
}
GameEffectRets e_Politic::Execute(ExecuteParams EP){
	int i,max,max2,j,k;
	vector<int> tempvec;
	ostringstream ss;
	vector<Voting> votes;
	votes.resize(_GameStats.GetPlayersNumber());
	vector<string> results;
	results.resize(_GameStats.GetPlayersNumber());
	e_Politic * exec = this;

	_Interface.PrintThingAll(exec->effect);

	for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		_Interface.SetCurrPlayer(i);

		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_PreVotings,_Players[i],&votes,&exec));//veto etc
	}
	for (k=_GameStats.Speaker; k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		votes[i] = exec->tvote;
		votes[i].votes = _Players[i]->GetVotes();
		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_Votings,_Players[i],&votes));//nekro etc
		ss.str("");
		ss<<"Player {"<<_Players[i]->GetName()<<"} got "<<votes[i].votes<<" votes";
		_Interface.PrintThingAll(ss.str());
	}

	for (k=_GameStats.Speaker;k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		_Interface.SetCurrPlayer(i);
		
		ss.str("");
		ss<<"Player {"<<_Players[i]->GetName()<<"} voted for: ";
		if ((votes[i].votes == 0)||(SelectDialogYesNo("---- ABSTAIN? ----"))){
			ss<<" abstain";
			_Interface.PrintThingAll(ss.str());
			votes[i] = Voting();
			continue;
		}

		// Votings
		for (j=0; j<votes[i].yesno.size(); ++j){
			votes[i].yesno[j] = SelectDialogYesNo("Vote yes or no");
			if (votes[i].yesno[j])
				results[i]+="[YES] ";
			else 
				results[i]+="[NO] ";
		}
		for (j=0; j<votes[i].player.size(); ++j){
			votes[i].player[j] = SelectDialogPlayer("Choose a player");
			results[i] += string("[") + votes[i].player[j]->GetName() + "] ";
		}
		for (j=0; j<votes[i].system.size(); ++j){
			tempvec = _GrIn.SysChoise("Choose a system");
			votes[i].system[j] = _Map.GetHexh(tempvec[0], tempvec[1]);
			results[i] += string("[") + votes[i].system[j]->GetId() + "] ";
		}
		for (j=0; j<votes[i].planet.size(); ++j){
			tempvec = _GrIn.SysChoise("Choose a system");
			votes[i].planet[j] = _Map.GetHexh(tempvec[0], tempvec[1])->GetPlanet(SelectDialogPlanetInSystem(_Map.GetHexh(tempvec[0], tempvec[1])));
			results[i] += string("[") + votes[i].planet[j]->GetName() + "] ";
		}
		ss<<results[i];
		_Interface.PrintThingAll(ss.str());
	}
	max = 0;
	max2 = -1;
	for (i = 0; i<_GameStats.GetPlayersNumber()-1; ++i)
		for (k = i+1; k<_GameStats.GetPlayersNumber(); ++k)
			if (votes[i].SameAs(votes[k])){
				votes[i].votes += votes[k].votes;
				votes[k].votes = 0;
			}
	for (i = 0; i<_GameStats.GetPlayersNumber(); ++i){
		if (votes[i].votes > votes[max].votes)
			max = i;
		else if (votes[max].votes == votes[i].votes)
			max2 = i;
	}
	if ((max2 != -1)&&(votes[max2].votes == votes[max].votes)&&(max2 != max)){
		ss.str("");
		ss<<"A tie! Speaker {"<< _Players[_GameStats.Speaker]->GetName() <<"} must resolve!";
		_Interface.PrintThingAll(ss.str());

		_Interface.SetCurrPlayer(_GameStats.Speaker);
		if (votes[max].votes != 0){
			_GrIn.InitChoise("Resolve a draw");
			for (i = 0; i<_GameStats.GetPlayersNumber(); ++i)
				if (votes[i].votes == votes[max].votes)
					_GrIn.AddOption(EMPTY_EVENT_IMG,results[i]);
			tempvec = _GrIn.LaunchChoise();
			for (i = 0; i < tempvec.size(); ++i)
				if (tempvec[i] == 1)
					max2 = i;
			if (max2 != 0){
				j = 0;
				for (i = 0; i<_GameStats.GetPlayersNumber(); ++i){
					if ((votes[i].votes = votes[max].votes)&&(!votes[i].SameAs(votes[max])))
						if (max2 == j){
							max = j;
							break;
						}
						++j;
				}
			}
		}
		else{
			i = _GameStats.Speaker;
			votes[i] = tvote;
			results[i].clear();
			for (j=0; j<votes[i].yesno.size(); ++j){
				votes[i].yesno[j] = SelectDialogYesNo("Vote yes or no");
				if (votes[i].yesno[j])
					results[i]+="[YES] ";
				else 
					results[i]+="[NO] ";
			}
			for (j=0; j<votes[i].player.size(); ++j){
				if (votes[i].player[j] != 0){
					votes[i].player[j] = SelectDialogPlayer("Choose a player");
					results[i] += string("[") + votes[i].player[j]->GetName() + "] ";
				}
			}
			for (j=0; j<votes[i].system.size(); ++j){
				if (votes[i].system[j] != 0){
					tempvec = _GrIn.SysChoise("Choose a system");
					votes[i].system[j] = _Map.GetHexh(tempvec[0], tempvec[1]);
					results[i] += string("[") + votes[i].system[j]->GetId() + "] ";
				}
			}
			for (j=0; j<votes[i].planet.size(); ++j){
				if (votes[i].planet[j] != 0){
					tempvec = _GrIn.SysChoise("Choose a system");
					votes[i].planet[j] = _Map.GetHexh(tempvec[0], tempvec[1])->GetPlanet(SelectDialogPlanetInSystem(_Map.GetHexh(tempvec[0], tempvec[1])));
					results[i] += string("[") + votes[i].planet[j]->GetName() + "] ";
				}
			}
			max = i;
		}
	}
	ss.str("");
	ss<<"Variant "<< results[max] <<" has won!";
	_Interface.PrintThingAll(ss.str());
	for (k=_GameStats.Speaker; k<_GameStats.GetPlayersNumber()+_GameStats.Speaker;++k){
		i = k % _GameStats.GetPlayersNumber();
		_Players[i]->ExecuteGameEffect(ExecuteParams(eq_AfterVotings,_Players[i],&votes));
	}
	exec->DoEffect(votes[max]);
	return er_delete;
} 
//-------------------------------------------		done?	tested?	debuged?
#include "politics\\p_AggressiveStrategy.cpp"	//	1		1		1
#include "politics\\p_AncientArtifact.cpp"      //  1       1       1
#include "politics\\p_ArchivedSecret.cpp"		//	0		0		0
#include "politics\\p_ArmsReduction.cpp"		//	0		0		0
#include "politics\\p_BuildMonument.cpp"		//	0		0		0
#include "politics\\p_CentrillicGas.cpp"		//	1		1		1
#include "politics\\p_ChecksandBalances.cpp"	//	0		0		0
#include "politics\\p_ClassStruggle.cpp"		//	0		0		0
#include "politics\\p_ClosingtheWormholes.cpp"	//	0		0		0
#include "politics\\p_CodeofHonor.cpp"			//	0		0		0
#include "politics\\p_ColonialRedistribution.cpp"//	0		0		0
#include "politics\\p_ColonizationLicensing.cpp"//	0		0		0
#include "politics\\p_CompensatedDisarmament.cpp"//	1		1		1
#include "politics\\p_ConventionsWar.cpp"		//	0		0		0
#include "politics\\p_CoreStability.cpp"		//	0		0		0
#include "politics\\p_CorruptEmpire.cpp"		//	0		0		0
#include "politics\\p_CostOverruns.cpp"			//	1		0		0
#include "politics\\p_Council'sCensure.cpp"		//	0		0		0
#include "politics\\p_CouncilElder.cpp"			//	0		0		0
#include "politics\\p_CrownofThalnos.cpp"		//	1		0		0
#include "politics\\p_DefendtheJewel.cpp"		//	0		0		0
#include "politics\\p_DefensiveMobilizations.cpp"//	0		0		0
#include "politics\\p_DisputeResolution.cpp"	//	0		0		0
#include "politics\\p_DiversifiedIncome.cpp"	//	0		0		0
#include "politics\\p_DocumentingResearch.cpp"	//	0		0		0
#include "politics\\p_EconomicRevitalization.cpp"//	1		1		1
#include "politics\\p_Emperor.cpp"				//	0		0		0
#include "politics\\p_EnemyoftheThrone.cpp"		//	0		0		0
#include "politics\\p_EqualThreats.cpp"			//	0		0		0
#include "politics\\p_FighterTax.cpp"			//	1		1		1
#include "politics\\p_FlawePlanning.cpp"		//	0		0		0
#include "politics\\p_FleetRegulations.cpp"		//	1/2		0		0
#include "politics\\p_FleetRestriction.cpp"		//	0		0		0
#include "politics\\p_ForbiddenResearch.cpp"	//	0		0		0
#include "politics\\p_ForcedEconomicIndependence.cpp"//	0		0		0
#include "politics\\p_FreeTrade.cpp"			//	0		0		0
#include "politics\\p_FundResearchComplex.cpp"	//	1		1		1
#include "politics\\p_GloryoftheEmpire.cpp"		//	0		0		0
#include "politics\\p_HolderofMecatolRex.cpp"	//	0		0		0
#include "politics\\p_HolyPlanetofIxth.cpp"			//	0		0		0
#include "politics\\p_HopesEndTrainingGround .cpp"	//	0		0		0
#include "politics\\p_HumaneLabor.cpp"				//	0		0		0
#include "politics\\p_ImperialAcademy.cpp"			//	0		0		0
#include "politics\\p_ImperialContainment.cpp"		//	0		0		0
#include "politics\\p_ImperialMandate.cpp"			//	0		0		0
#include "politics\\p_ImperialPeace.cpp"			//	0		0		0
#include "politics\\p_IncentiveProgram.cpp"			//	0		0		0
#include "politics\\p_IntergalacticCommerce.cpp"		//	1		0		0
#include "politics\\p_InterstellarArmsDealers.cpp"		//	0		0		0
#include "politics\\p_InvestigateSpatialAnomalies.cpp"	//	0		0		0
#include "politics\\p_LaborForcePolitics.cpp"		//	0		0		0
#include "politics\\p_LimitstoIndividualPower.cpp"	//	0		0		0
#include "politics\\p_MassMobilization.cpp"			//	0		0		0
#include "politics\\p_MiningOperations.cpp"			//	1		1		1
#include "politics\\p_MinisterofCommerce.cpp"		//	0		0		0
#include "politics\\p_MinisterofExploration.cpp"	//	0		0		0
#include "politics\\p_MinisterofInternalSecurity.cpp"	//	0		0		0
#include "politics\\p_MinisterofPeace.cpp"			//	0		0		0
#include "politics\\p_MinisterofPolicy.cpp"			//	0		0		0
#include "politics\\p_MinisterofWar.cpp"			//	0		0		0
#include "politics\\p_Mutiny.cpp"					//	0		0		0
#include "politics\\p_NeutralityPact.cpp"			//	0		0		0
#include "politics\\p_NewConstitution.cpp"			//	0		0		0
#include "politics\\p_NonAggressionPact.cpp"		//	0		0		0
#include "politics\\p_OfficialSanction.cpp"			//	0		0		0
#include "politics\\p_OpentheTradeRoutes.cpp"		//	0		0		0
#include "politics\\p_PlanetaryConscription.cpp"	//	0		0		0
#include "politics\\p_PlanetarySecurity.cpp"		//	1		1		1
#include "politics\\p_PoliticalFocus.cpp"			//	0		0		0
#include "politics\\p_ProphecyofIxth.cpp"			//	0		0		0
#include "politics\\p_PublicExecution.cpp"			//	0		0		0
#include "politics\\p_RecognizeAccomplishments.cpp"	//	0		0		0
#include "politics\\p_RedefiningWarCrimes.cpp"		//	0		0		0
#include "politics\\p_RegressiveRhetoric.cpp"		//	0		0		0
#include "politics\\p_RegulatedConscription.cpp"	//	0		0		0
#include "politics\\p_Repeal.cpp"					//	0		0		0
#include "politics\\p_ResearchGrant.cpp"			//	0		0		0
#include "politics\\p_ResourceManagement.cpp"		//	0		0		0
#include "politics\\p_Revote.cpp"					//	0		0		0
#include "politics\\p_ScienceCommunitySpeaker.cpp"	//	0		0		0
#include "politics\\p_SeedofanEmpire.cpp"			//	0		0		0
#include "politics\\p_SharingofaTechnology.cpp"		//	0		0		0
#include "politics\\p_ShortTermTruce.cpp"			//	0		0		0
#include "politics\\p_SubsidizedIndustry.cpp"		//	1		1		1
#include "politics\\p_SubsidizedStudies.cpp"		//	0		0		0
#include "politics\\p_SupportedExpansion.cpp"		//	1		0		0
#include "politics\\p_TechInvestigationCommittee.cpp"	//	0		0		0
#include "politics\\p_TechnologicalJihad.cpp"		//	0		0		0
#include "politics\\p_TechnologyBuyBack.cpp"		//	0		0		0
#include "politics\\p_TechnologyTariffs.cpp"		//	0		0		0
#include "politics\\p_TheCrownofEmphidia.cpp"		//	0		0		0
#include "politics\\p_TradeEmbargo.cpp"				//	0		0		0
#include "politics\\p_TradeWar.cpp"					//	0		0		0
#include "politics\\p_TrafficTariffs.cpp"			//	0		0		0
#include "politics\\p_UnconventionalMeasures.cpp"	//	0		0		0
#include "politics\\p_UnconventionalWeapons.cpp"	//	1		0		0
#include "politics\\p_VetoPower.cpp"				//	0		0		0
#include "politics\\p_VorhalPeacePrize.cpp"			//	1		1		1
#include "politics\\p_WarFunding.cpp"				//	0		0		0
#include "politics\\p_WarshipCommission.cpp"		//	0		0		0
#include "politics\\p_WormholeReconstruction.cpp"	//	0		0		0
#include "politics\\p_WormholeResearch.cpp"			//	0		0		0