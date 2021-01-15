Deck<e_Politic> _PoliticsDeck;

list<e_Politic*> PoliticsList;
vector<GameEffect*> StartUnits;
vector<GameEffect*> CommonEffects;
vector<e_Tech*> TechList;
vector<GameEffect*> RaceEffectList;
vector<e_Objective*> ObjectiveList;
vector<e_StratCard*> StratCardList;
vector<GameEffect*> Miscellaneous;
vector<e_ActionCard*> ActionCardList;

void FillPolitics(){
	PoliticsList.push_back(new e_p_AggressiveStrategy());
	PoliticsList.push_back(new e_p_AncientArtifact());
	PoliticsList.push_back(new e_p_ArmsReduction());
	PoliticsList.push_back(new e_p_CentrillicGas());
	PoliticsList.push_back(new e_p_CompensatedDisarmament());
	PoliticsList.push_back(new e_p_CostOverruns());
	PoliticsList.push_back(new e_p_CrownOfThalnos());
	PoliticsList.push_back(new e_p_EconomicRevitalization());
	PoliticsList.push_back(new e_p_FighterTax());
	//PoliticsList.push_back(new e_p_FleetRegulations());//не доделано
	PoliticsList.push_back(new e_p_FreeTrade());
	PoliticsList.push_back(new e_p_FundResearchComplex());
	PoliticsList.push_back(new e_p_HumanLabor());
	PoliticsList.push_back(new e_p_IntergalacticCommerce());
	PoliticsList.push_back(new e_p_InterstellarArmsDealers());
	PoliticsList.push_back(new e_p_MiningOperations());
	PoliticsList.push_back(new e_p_MinisterOfCommerce());
	PoliticsList.push_back(new e_p_MinisterOfExploration());
	PoliticsList.push_back(new e_p_MinisterOfPolicy());
	PoliticsList.push_back(new e_p_MinisterOfWar());
	PoliticsList.push_back(new e_p_PlanetarySecurity());
	PoliticsList.push_back(new e_p_PublicExecution());
	PoliticsList.push_back(new e_p_ResearchGrant());
	PoliticsList.push_back(new e_p_SubsidizedIndustry());
	PoliticsList.push_back(new e_p_SupportedExpansion());
	PoliticsList.push_back(new e_p_TechnologyTariffs());
	PoliticsList.push_back(new e_p_UnconventionalWeapon());
	PoliticsList.push_back(new e_p_VorhalPeacePrize());
	PoliticsList.push_back(new e_p_WarshipCommision());

}
void FillRaceStartUnits(){
	StartUnits.push_back(new e_ArborecStartUnits());
	StartUnits.push_back(new e_CreussStartUnits());
	StartUnits.push_back(new e_HacanStartUnits());
	StartUnits.push_back(new e_JolNarStartUnits());
	StartUnits.push_back(new e_L1z1xStartUnits());
	StartUnits.push_back(new e_LetnevStartUnits());
	StartUnits.push_back(new e_MentakStartUnits());
	StartUnits.push_back(new e_MuaatStartUnits());
	StartUnits.push_back(new e_NaaluStartUnits());
	StartUnits.push_back(new e_NekroStartUnits());
	StartUnits.push_back(new e_NorrStartUnits());
	StartUnits.push_back(new e_SaarStartUnits());
	StartUnits.push_back(new e_SolStartUnits());
	StartUnits.push_back(new e_WinnuStartUnits());
	StartUnits.push_back(new e_XxchaStartUnits());
	StartUnits.push_back(new e_YinStartUnits());
	StartUnits.push_back(new e_YssarilStartUnits());
}

void FillCommonEffects(){
	CommonEffects.push_back(new e_TacticalAction);
	CommonEffects.push_back(new e_TransferAction);
	CommonEffects.push_back(new e_SendGoods);
	CommonEffects.push_back(new e_ShockTroopersUpgrade);
	CommonEffects.push_back(new e_ShockTroopersCapture);
	//CommonEffects.push_back(new e_DestroyersMarkII);
	CommonEffects.push_back(new e_DestroyersMarkI);
	CommonEffects.push_back(new e_Bombardment);
	CommonEffects.push_back(new e_PDS);
	CommonEffects.push_back(new e_PDScommon);
	CommonEffects.push_back(new e_PlanetTechDiscount);
	CommonEffects.push_back(new e_PlanetRefreshAbilities);
	CommonEffects.push_back(new e_DockBuildLimit);
	CommonEffects.push_back(new e_FlagshipBuild);
	CommonEffects.push_back(new e_HomeControl);
	CommonEffects.push_back(new e_IonStormFighters);
	CommonEffects.push_back(new e_NebulaBonus);
	CommonEffects.push_back(new e_GravityRift);
	CommonEffects.push_back(new e_StatusPhaseTradeAgreementBreak);
	CommonEffects.push_back(new e_StatusPhaseScuttleUnits);
	CommonEffects.push_back(new e_ResearchTech);
	CommonEffects.push_back(new e_ActionCardLimit);
	CommonEffects.push_back(new e_RetreatWithdraw);
	CommonEffects.push_back(new o_Tracker);
}

void FillTechs(){
	TechList.push_back(new e_HylarVAssualtLaser);
	TechList.push_back(new e_DeepSpaceCannon);
	TechList.push_back(new e_WarSun);
	TechList.push_back(new e_MagenDefenseGrid);
	TechList.push_back(new e_DuraniumArmor);
	TechList.push_back(new e_ADT);
	TechList.push_back(new e_AssaultCannon);
	TechList.push_back(new e_GravityNegator);
	//
	TechList.push_back(new e_StasisCapsules);
	TechList.push_back(new e_Cybernetics);
	TechList.push_back(new e_GenSynthesis);
	TechList.push_back(new e_NeuralMotivator);
	TechList.push_back(new e_NeuralComputing);
	TechList.push_back(new e_DacxiveAnimators);
	TechList.push_back(new e_HyperMetabolism);
	TechList.push_back(new e_X89);
	//
	TechList.push_back(new e_Antimass);
	TechList.push_back(new e_GravityDrive);
	TechList.push_back(new e_XRDtransporters);
	TechList.push_back(new e_TypeIVDrive);
	TechList.push_back(new e_AdvancedFighters);
	TechList.push_back(new e_LightWaveDeflector);
	TechList.push_back(new e_ManeuveringJets);
	TechList.push_back(new e_FleetLogistics);
	//
	TechList.push_back(new e_EnviroCompensator);
	TechList.push_back(new e_SarweenTools);
	TechList.push_back(new e_Microtechnology);
	TechList.push_back(new e_Nanotechnology);
	TechList.push_back(new e_IntegratedEconomy);
	TechList.push_back(new e_Transfabrication);
	TechList.push_back(new e_GravitonLaserSystem);
	TechList.push_back(new e_TransitDiodes);
	//
	TechList.push_back(new e_L1z1xDreadnoughtInvasionPods);
	TechList.push_back(new e_L1z1xInheritanceSystems);
	//
	TechList.push_back(new e_NorrValkyrieArmor);
	TechList.push_back(new e_NorrExotrireme);
	//
	TechList.push_back(new e_YssarilShuttleLogistics);
	TechList.push_back(new e_YssarilMageonImplants);
	//
	TechList.push_back(new e_LetnevL4Disruptors);
	TechList.push_back(new e_LetnevNoneuclidianShields);
	//
	TechList.push_back(new e_MentakSalvageOperations);
	TechList.push_back(new e_MentakMirrorComputing);
	//
	TechList.push_back(new e_JolNarSpatialConduitNetwork);
	TechList.push_back(new e_JolNarElectroResonanceTurbines);
	//
	TechList.push_back(new e_HacanProductionCenters);
	TechList.push_back(new e_HacanQuantumDatahubNode);
	//
	TechList.push_back(new e_SolMarkIICarrier);
	TechList.push_back(new e_SolSpecOpsTraining);
	//
	TechList.push_back(new e_XxchaDiplomats);
	TechList.push_back(new e_XxchaInstinctTraining);
	//
	TechList.push_back(new e_NaaluTelepathicMindWeapon);
	TechList.push_back(new e_NaaluHybridCrystalDrives);
	//
	TechList.push_back(new e_YinFanatic);
	TechList.push_back(new e_YinSpinner);
	//
	TechList.push_back(new e_SaarFloatingFactories);
	TechList.push_back(new e_SaarChaosMapping);
	//
	TechList.push_back(new e_MuaatMagmusReactor);
	TechList.push_back(new e_MuaatNovaSeed);
	//
	TechList.push_back(new e_WinnuBiopticRecyclers);
	TechList.push_back(new e_WinnuLazaxGateFolding);
	//
	TechList.push_back(new e_ArborecBioplasmosis);
	TechList.push_back(new e_ArborecSporeAcceleration);
	//
	TechList.push_back(new e_CreussDimensionalSplicers);
	TechList.push_back(new e_CreussSlaveWormholeGenerator);
}

void FillRaceEffects(){
	RaceEffectList.push_back(new e_HacanFlagship);
	RaceEffectList.push_back(new e_HacanAdditionalTG);
	RaceEffectList.push_back(new e_JolNarRacialAbilityStats);
	RaceEffectList.push_back(new e_JolNarTechnology);
	RaceEffectList.push_back(new e_JolNarReroll);
	RaceEffectList.push_back(new e_L1z1xRacialAbilityStats);
	RaceEffectList.push_back(new e_L1z1xFlagship);
	RaceEffectList.push_back(new e_LetnevBattleAbility);
	RaceEffectList.push_back(new e_LetnevFleetSupply);
	RaceEffectList.push_back(new e_MentakPreBattle);
	RaceEffectList.push_back(new e_MentakStealGoods);
	RaceEffectList.push_back(new e_MentakFlagship);
	RaceEffectList.push_back(new e_MuaatWarSunSpeed);
	RaceEffectList.push_back(new e_MuaatWarSunSpawn);
	RaceEffectList.push_back(new e_MuaatFlagshipSpawn);
	RaceEffectList.push_back(new e_MuaatSuperNovaMove);
	RaceEffectList.push_back(new e_NaaluRacialAbilityStats);
	RaceEffectList.push_back(new e_NaaluFlagship);
	RaceEffectList.push_back(new e_NaaluInitiative);
	RaceEffectList.push_back(new e_NaaluRetreat);
	RaceEffectList.push_back(new e_NekroFlagship);
	RaceEffectList.push_back(new e_NekroValefarAssmilator);
	RaceEffectList.push_back(new e_NekroTechResearch);
	RaceEffectList.push_back(new e_NekroAbstain);
	RaceEffectList.push_back(new e_NorrRacialAbilityStats);
	RaceEffectList.push_back(new e_NorrFlagship);
	RaceEffectList.push_back(new e_SaarDocks);
	RaceEffectList.push_back(new e_SaarExploration);
	RaceEffectList.push_back(new e_SolCounter);
	RaceEffectList.push_back(new e_SolRecruit);
	RaceEffectList.push_back(new e_WinnuFlagship);
	RaceEffectList.push_back(new e_WinnuTechnology);
	RaceEffectList.push_back(new e_WinnuPolitic);
	RaceEffectList.push_back(new e_WinnuLocalUnrest);
	RaceEffectList.push_back(new e_XxchaRacialAbilityStats);
	RaceEffectList.push_back(new e_XxchaDiplomacy);
	RaceEffectList.push_back(new e_XxchaVeto);
	RaceEffectList.push_back(new e_YinFanaticism);
	RaceEffectList.push_back(new e_YinKamikaze);
	RaceEffectList.push_back(new e_YinFlagship);
	RaceEffectList.push_back(new e_YinReverse);
	RaceEffectList.push_back(new e_YssarilAdditionalAC);
	RaceEffectList.push_back(new e_YssarilSpy);
	RaceEffectList.push_back(new e_YssarilWait);
}

void FillObjectives(){
	ObjectiveList.push_back(new o_1_10ror10i());
	ObjectiveList.push_back(new o_1_5techs());
	ObjectiveList.push_back(new o_1_6tg());
	ObjectiveList.push_back(new o_1_5planets());
	ObjectiveList.push_back(new o_1_3docks());
	ObjectiveList.push_back(new o_1_Mecatol());
	ObjectiveList.push_back(new o_1_Blockade());
	ObjectiveList.push_back(new o_1_Invasion());
	ObjectiveList.push_back(new o_1_SpaceVictory());
	ObjectiveList.push_back(new o_1_Take3Planets());
	ObjectiveList.push_back(new o_1_PlanetAllColors());
	ObjectiveList.push_back(new o_1_Tech4Color());
	ObjectiveList.push_back(new o_1_TechInColor());
	ObjectiveList.push_back(new o_1_10res());
	ObjectiveList.push_back(new o_1_10inf());
	ObjectiveList.push_back(new o_1_3CC());
	ObjectiveList.push_back(new o_1_GreatInf());
	/////////////////////////////////////////////
	ObjectiveList.push_back(new o_2_20ror20i());
	ObjectiveList.push_back(new o_2_12tg());
	ObjectiveList.push_back(new o_2_20res());
	ObjectiveList.push_back(new o_2_20inf());
	ObjectiveList.push_back(new o_2_6CC());
	ObjectiveList.push_back(new o_2_9techs());
	ObjectiveList.push_back(new o_2_10planets());
	ObjectiveList.push_back(new o_2_Invasion());
	ObjectiveList.push_back(new o_2_SpaceVictory());
	ObjectiveList.push_back(new o_2_TechInColor());
	ObjectiveList.push_back(new o_2_mecatol3());
	ObjectiveList.push_back(new o_2_mecatol6());
	ObjectiveList.push_back(new o_2_GreatInf());
	ObjectiveList.push_back(new o_2_DestroyedDock());
	ObjectiveList.push_back(new o_2_Supremacy());
	ObjectiveList.push_back(new o_2_Domination());	
	ObjectiveList.push_back(new o_2_ImperiumRex());
	/////////////////////////////////////////////
	ObjectiveList.push_back(new o_p_Defender());
	ObjectiveList.push_back(new o_p_Commander());
	ObjectiveList.push_back(new o_p_Scientist());
	ObjectiveList.push_back(new o_p_Researcher());
	ObjectiveList.push_back(new o_p_Antagonist());
	ObjectiveList.push_back(new o_p_Enemy());
	ObjectiveList.push_back(new o_p_Infiltrator());
	ObjectiveList.push_back(new o_p_Explorer());
	ObjectiveList.push_back(new o_p_Invader());
	ObjectiveList.push_back(new o_p_Traitor());
	/////////////////////////////////////////////
	ObjectiveList.push_back(new o_s_MasterOfShips());
	ObjectiveList.push_back(new o_s_Forceful());
	ObjectiveList.push_back(new o_s_Usurper());
	ObjectiveList.push_back(new o_s_Diversified());
	ObjectiveList.push_back(new o_s_Conqueror());
	ObjectiveList.push_back(new o_s_Expansionist());
	ObjectiveList.push_back(new o_s_Threatening());
	ObjectiveList.push_back(new o_s_Technocrat());
	ObjectiveList.push_back(new o_s_Merciless());
	ObjectiveList.push_back(new o_s_Industrial());
	ObjectiveList.push_back(new o_s_Focused());
	ObjectiveList.push_back(new o_s_Regulator());
	/////////////////////////////////////////////
	ObjectiveList.push_back(new o_g_VP());
}

void FillActions(){
	ActionCardList.push_back(new e_a_TestActionCard());
	///////////////////////////////////////////////////////////
	ActionCardList.push_back(new e_a_AdvancedReinforcements());
	ActionCardList.push_back(new e_a_AlienTechnology());
	ActionCardList.push_back(new e_a_BeaconOfHope());
	ActionCardList.push_back(new e_a_CivilDefence());
	ActionCardList.push_back(new e_a_CommandSammit());
	ActionCardList.push_back(new e_a_EquipmentSabotage());
	ActionCardList.push_back(new e_a_FighterPrototype());
	ActionCardList.push_back(new e_a_GeomagneticMines());
	ActionCardList.push_back(new e_a_GoodYear());
	ActionCardList.push_back(new e_a_IntoTheBreach());
	ActionCardList.push_back(new e_a_LocalUnrest());
	ActionCardList.push_back(new e_a_MoraleBoost());
	ActionCardList.push_back(new e_a_Overrun());
	ActionCardList.push_back(new e_a_Plague());
	ActionCardList.push_back(new e_a_Privateers());
	ActionCardList.push_back(new e_a_RallyOfPeople());
	ActionCardList.push_back(new e_a_Recheck());
	ActionCardList.push_back(new e_a_RiseOfMessiah());
	ActionCardList.push_back(new e_a_SecretIndustrialAgent());
	ActionCardList.push_back(new e_a_SignalJamming());
	ActionCardList.push_back(new e_a_SpaceDockAccident());
	ActionCardList.push_back(new e_a_TradeStop());
	ActionCardList.push_back(new e_a_UnexpectedAction());
	ActionCardList.push_back(new e_a_Uprising());
	ActionCardList.push_back(new e_a_VoluntaryAnnexation());
}

void FillStrats(){
	_StratShared[0] = new e_Leadership;
	_StratShared[1] = new e_Diplomacy;
	_StratShared[2] = new e_Assembly;
	_StratShared[3] = new e_Production;
	_StratShared[4] = new e_Trade;
	_StratShared[5] = new e_Warfare;
	_StratShared[6] = new e_Technology;
	_StratShared[7] = new e_Bureaucracy;
	StratCardList.push_back(new e_Leadership);
	StratCardList.push_back(new e_Diplomacy);
	StratCardList.push_back(new e_Assembly);
	StratCardList.push_back(new e_Production);
	StratCardList.push_back(new e_Trade);
	StratCardList.push_back(new e_Warfare);
	StratCardList.push_back(new e_Technology);
	StratCardList.push_back(new e_Bureaucracy);
}

void FillMiscellaneous(){
	Miscellaneous.push_back(new e_HighAlert);
	//Add-effects politics here!
	Miscellaneous.push_back(new e_p_AggressiveStrategy_nay);
	Miscellaneous.push_back(new e_p_CrownOfThalnos_add);
	Miscellaneous.push_back(new e_p_FighterTax_add);
	Miscellaneous.push_back(new e_p_FreeTrade_YAY);
	Miscellaneous.push_back(new e_p_FundResearchComplex_bonus);
	Miscellaneous.push_back(new e_p_HumanLabor_YAY);
	Miscellaneous.push_back(new e_p_HumanLabor_NAY);
	Miscellaneous.push_back(new e_p_IntergalacticCommerce_add);
	Miscellaneous.push_back(new e_p_InterstellarArmsDealers_add);
	Miscellaneous.push_back(new e_p_MinisterOfCommerce_add);
	Miscellaneous.push_back(new e_p_MinisterOfExploration_add);
	Miscellaneous.push_back(new e_p_MinisterOfPolicy_add());
	Miscellaneous.push_back(new e_p_MinisterOfWar_add);
	Miscellaneous.push_back(new e_p_PublicExecution_add);
	Miscellaneous.push_back(new e_p_ResearchGrant_YAY);
	Miscellaneous.push_back(new e_p_ResearchGrant_NAY);
	Miscellaneous.push_back(new e_p_TechnologyTariffs_YAY);
	Miscellaneous.push_back(new e_p_TechnologyTariffs_NAY);
	Miscellaneous.push_back(new e_p_UnconventionalWeapon_add);
	Miscellaneous.push_back(new e_p_VorhalPeacePrize_add);
	Miscellaneous.push_back(new e_p_WarshipCommision_add);
	//Miscellaneous.push_back(new );
}

void Despair(){
	FillPolitics();
	FillRaceStartUnits();
	FillCommonEffects();
	FillTechs();
	FillRaceEffects();
	FillObjectives();
	FillStrats();
	FillMiscellaneous();
	FillActions();
}