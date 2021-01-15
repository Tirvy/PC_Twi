//#define PATH_TO_DATA "C:\\Users\\Tirvy\\Documents\\Visual Studio 2008\\Projects\\PC_Twilight\\PC_Twilight\\data\\"
#define PATH_TO_DATA "..\\Release\\data\\"
#define DEBUGMODE
#define MAX_PLAYERS 8
#define MAX_PLANETS 3
#define MAX_ROLLS 100
#define MAX_TRADES 2
#define MAX_TECH_COLORED 8
#define DICE 10
#define FREE_TECH_COST -100

#define MECATOLREX "Mecatol_Rex"
#define MECATOLSYSTEM "MecatolRex"
#define NEXUS "Mallice"


enum PaysType {pt_res, pt_inf, pt_goods};
enum GamePhaseType {gpt_pregame, gpt_strategy, gpt_action, gpt_status, gpt_max};
const string  GamePhases[]={"Pregame ", "Strategy", "Action  ", "Status  ", "Sum Ting Wong phase"};

//politics types. none if none))
enum PCtypes { pc_none, pc_yaynay, pc_cplayer, pc_csystem, pc_cplanet};

//Counter pools
enum CC_pools {CC_strat,CC_fleet,CC_comm,CC_MAX};
const string  CC_PoolsFull[] = {"Strategy Allocation","Fleet supply","Command pool"};

//Battle
enum Battle_Result {br_AttackerWins, br_Draw, br_AttackerLoses, br_MAX};
enum Battle_Type {bt_Space, bt_AFB, bt_PDS, bt_DSC, bt_Bombardment, bt_Invasion, bt_AssaultCannon, bt_Mentak};
enum Assign_Damage {ad_Space, ad_Fighters, ad_CapitalShips, ad_Invasion, ad_BeforeInvasion};
enum Unit_Status {us_None, us_AFB, us_BombSelect, us_BombDone, us_Mentak, us_GF, us_ST};
//Victory Points, objectives
enum VP_type { vp_prelim, vp_secret, vp_stage1, vp_stage2, vp_win, vp_special };
enum Objective_Type { obj_10rOR10i, obj_5techs, obj_6tg, obj_5planets, obj_3docks,
	obj_Mecatol, 
	obj_9techs, obj_20rOR20i, obj_10planets,
	obj_GAME_OVER,
	obj_Commander, obj_Defender, obj_Scientist, obj_Researcher,
	OBJECTIVE_MAX};
//Systems
enum LinkType {ltBound, ltPortal, ltNone};	//ZoldnMap
enum DangerType { DT_NONE, Nebula, Asteroids, IonStorm, Supernova, GravityRift, DT_MAX};
const string  DangersLong[]={"         ","Nebula   ","Asteroids","Ion Storm","Supernova","Gr. Rift "};
enum SystemType { RedSys, EmptySys, PlanetSys, HomeSys, SpecSys };
//Wormholes
enum WormholeType { wh_NONE, wh_A, wh_B, wh_C, wh_D, wh_MAX};
const string  WormholeShort[]={"","@A","@B","@C","@D"};
//Planets
enum PlanetStatus { ps_exhausted, ps_open, ps_captured, ps_opencaptured };
enum PlanetState {psExhausted, psCaptured, psDiplomated, psNoSurface, psProtected, psMax};//Zoldn
	//psExhausted - потапанная
	//psCaptured - захвачена в этот раунд
	//psDiplomated - сдипломачено
	//psNoSurface - нет поверхности для высадки
	//psProtected - вторжение на эту планету запрещено
	//psRadiation - радиация
	//psBiohazard - зомби на планете
const string  SpecialShort[]={"","ST","FG","GF","TS","--"};
const string  SpecialFull[]={"","ShockTroopers academy","Fighters factory","Ground Forces barraks","Trade Station","--"};
enum SpecialsType { st_ZERO, ShockTroops, Fighters, GroundForces, TradeStation, st_MAX };
//Game Effects
enum GameEffectRets { er_normal, er_none, er_delete, er_delete_none };
enum GameEffectQs { eq_None, eq_AAA, 
	eq_StrategyStart, eq_StrategyEnd, eq_StrategyAction,
	eq_ActionStart, eq_ActionEnd, 
	eq_Fulfill, eq_ObjCanQualify, eq_ObjCheck, eq_FinishGame, 
	eq_StatusStart, eq_StatusPhase, eq_StatusEnd, 
	eq_StratActiveStart, eq_StratActiveEnd, 
	eq_StratSecStart, eq_StratSecEnd, 
	eq_PreVotings, eq_Votings, eq_AfterVotings, // pre - После вскрытия, до голосов; Votings - перед своим голосом; After - после итогов, но до применения эффектов
	eq_Movement, eq_BeforeMovement, eq_AfterMovement, eq_FleetSupply, eq_FleetControl, eq_AfterFleetSupply,
	eq_Battle, eq_BattleStart, eq_BattleEnd,
	eq_BeforeBattle, eq_BeforeBattleAction,
	//eq_AFB, eq_AssaultCannon, eq_MentakAssault, eq_MinisterOfWar, eq_NaaluRetreat,
	eq_BeforeBattleRound, eq_BeforeBattleRoundAction,
	eq_AfterRollingDices, eq_AfterRollingDicesAction, 
	eq_AfterRoll, 
	eq_AfterAssignDamage, 
	eq_AfterBattleRound, eq_AfterBattleRoundAction,
	eq_AfterBattle, 
	eq_Retreat,
	eq_Bombardment, eq_AfterBombardment, eq_BeforeBombardment,
	eq_PDSmain, eq_PDSfire, eq_PDSmod,
	eq_BeforeBuild, eq_AfterBuild, eq_DockBuild, eq_SpawnUnits,
	eq_Pregame,
	eq_TechnologyBuy, eq_TechnologyAvailable,
	eq_Payment,
	eq_CreateUnit, eq_LaunchEffect, eq_LoadGame, eq_AfterRefreshAbilities,
	eq_BeforeLanding, eq_Landing, eq_AfterLanding, eq_OnCapture, eq_BeforeCapture, eq_PlanetDestroyed,
	eq_ActionCard, eq_PoliticCard, eq_Objective, eq_ObjectiveTracker,
	eq_SpecialStratCard, eq_Scuttle, eq_ResearchTech,
	eq_ActionCardBreak, eq_ReceiveActionCard,
	eq_TradeModificator, eq_ActivateSystem, eq_AfterTactical
};
//Units
enum UnitType { GF, MU, ST, PDS, FG, DS, CS, CR, DR, WS, FM, DCK, MAX_UNIT };
const string  ShipsFull[]={"Infantry","Tank","Shocks","PDS","Fighter", "Destroyer","Cruiser","Carrier","Brevnout","WarSun","Flagman","Dock","Sum Ting Wong"};//,"Space Dock"
const string  ShipsShort[] = {"GF","MU","ST","PDS","FG","DS","CS","CR","DR","WS","FM","DCK","Sum Ting Wong"};
enum StatType {sPW, sSH, sHP, sSP, sCOST, sQNT, sCP, sFGCP, sGFCP, sPROD, sNP, MAX_STAT};
const int defUnitNumbers[MAX_UNIT] = {1024, 4, 12, 6, 1024, 8, 8, 4, 5, 2, 1, 3};
	/*PW=power, SH=shots, HP=HP, SP=speed, COST=cost, QNT=quantity, 
	CP=capacity (carrier, warsun, flagship), 
	GFCP=ground forces capacity (stasis capsules, Genesis I),
	FGCP=fighter capacity (docks)
	NS=need support
	sBuildable = 0 - нет, 1 - да, 2 - только в доках
	*/
enum UnitAbType {uaSpaceBattle, uaLandBattle, uaInfantry, uaCarried, uaUpToST, uaCapture,
	uaFirstTarget, uaStructure, uaProduction, uaCarrier, uaPlanetaryShield, uaLand,
	uaCapitalShip, uaCannon, uaSustain, uaAFB, uaBombard, uaProdCount, uaHeavyShip,
	uaLightShip, uaHyperDrive, uaAutoRepair, uaCritical, uaHeavyDamage, uaLimitOnPlanet,
	uaDamagedPenalty, uaEvasion, uaNeedSupport, uaInvasion, uaDropped, uaMultiple,
	uaUnlimGF, uaFighter, uaMentak, uaDeepSpaceCannon, uaKilled, uaDreadnought, 
	uaYinFighter, uaHighAlert, uaSupply, uaTransfered, uaNone
};

const int defStat[MAX_UNIT][MAX_STAT]={
	//   PW,SH,HP,SP,CT,QN,CP,fg,gf,pr,np
		{ 8, 1, 1, 0, 1,99, 0, 0, 0, 0, 2},//GF
		{ 6, 2, 2, 0, 2, 4, 0, 0, 0, 0, 1},//MU
		{ 5, 1, 1, 0, 0,12, 0, 0, 0, 0, 0},//ST
		{ 6, 1, 0, 0, 2, 6, 0, 0, 0, 0, 1},//PDS
		{ 9, 1, 1, 0, 1,99, 0, 0, 0, 0, 2},//FG
		{ 9, 1, 1, 2, 1, 8, 0, 0, 0, 0, 1},//DS
		{ 7, 1, 1, 2, 2, 8, 0, 0, 0, 0, 1},//CS
		{ 9, 1, 1, 1, 3, 4, 6, 0, 0, 0, 1},//CR
		{ 5, 1, 2, 1, 5, 5, 0, 0, 0, 0, 1},//DR
		{ 3, 3, 2, 2,12, 2, 6, 0, 0, 0, 0},//WS
		{ 9, 3, 2, 1,10, 1, 1, 0, 0, 0, 1},//FM
		{42,-9, 0, 0, 4, 3, 0, 0, 0, 2, 1} //DCK
	};
//Interface
enum FreeRoamRets { frr_none, frr_normal, frr_confirm, frr_pass};
//Races
//enum RacesType {  L1z1x, Norr, Yssaril, Letnev, Mentak, JolNar, Hacan, Sol, Xxcha, Naalu, Yin, Saar, Muaat, Winnu, Arborec, Nekro ,Creuss, MAX_RACE};
//const string  RacesFull[]={ "L1z1x", "Norr", "Yssaril", "Letnev", "Mentak", "JolNar", "Hacan", "Sol", "Xxcha", "Naalu", "Yin", "Saar", "Muaat", "Winnu", "Arborec", "Nekro","Creuss","Sum Ting Wong"};
enum RacesType { Arborec, Creuss, Hacan, JolNar, L1z1x, Letnev, Mentak, Muaat, Naalu, Nekro, Norr, Saar, Sol, Winnu, Xxcha, Yin, Yssaril, MAX_RACE};
const string  RacesFull[]={ "Arborec", "Creuss", "Hacan", "JolNar", "L1z1x", "Letnev", "Mentak", "Muaat", "Naalu", "Nekro", "Norr", "Saar", "Sol", "Winnu", "Xxcha", "Yin", "Yssaril", "Sum Ting Wong"};
const int FMstats[MAX_RACE][MAX_STAT]={
   //PW,SH,HP,SP,CT,QN,CP,fg,gf,pr,np
	{ 5, 3, 2, 1,11, 1, 2, 0, 0, 0, 1},//L1z1x
	{ 5, 3, 2, 1,10, 1, 2, 0, 0, 0, 1},//Norr
	{ 7, 2, 2, 2, 9, 1, 5, 0, 0, 0, 1},//Yssaril
	{ 5, 2, 2, 1,10, 1, 2, 0, 0, 0, 1},//Letnev
	{ 5, 2, 2, 2, 8, 1, 2, 0, 0, 0, 1},//Mentak
	{ 2, 2, 2, 2,10, 1, 2, 0, 0, 0, 1},//JolNar
	{ 7, 3, 2, 2,10, 1, 4, 0, 0, 0, 1},//Hacan
	{ 5, 3, 2, 1,10, 1, 3, 0, 0, 0, 1},//Sol
	{ 6, 2, 2, 1,10, 1, 4, 0, 0, 0, 1},//Xxcha
	{ 8, 2, 2, 1, 9, 1, 6, 0, 0, 0, 1},//Naalu
	{ 5, 2, 2, 1,10, 1, 4, 0, 0, 0, 1},//Yin
	{ 6, 3, 2, 1,10, 1, 4, 0, 0, 0, 1},//Saar
	{ 5, 3, 2, 1,10, 1, 4, 0, 0, 0, 1},//Muaat
	{ 7, 0, 2, 1,10, 1, 3, 0, 0, 0, 1},//Winnu
	{ 6, 2, 2, 1,10, 1, 5, 0, 0, 5, 1},//Arborec
	{ 9, 3, 2, 1, 9, 1, 1, 0, 0, 0, 1}//Necro
};
//Strategy cards
enum StratsType { Leadership, Diplomacy, Assembly, Production, Trade, Warfare, Technology, Bureaucracy, MAX_STRAT };
const string  StratsFull[]={"Leadership","Diplomacy", "Assembly","Production","Trade","Warfare","Technology","Bureaucracy","Sum Ting Wong"};
//Techs
enum TechTree { Red, Green, Blue, Yellow, RaceTech, tt_MAX };
const string  TechColorFull[]={"Red","Green","Blue","Yellow","","-"};

#define tt_STANDART 3
const string  TechColorShort[]={"r","g","b","y","","-"};
enum TechType {ttHylar, ttDeepSpaceCannon, ttWarSun, ttMagenDefenseGrid, ttDuranium, ttADT, ttAssaultCannon, ttGravityNegator,
			   ttStasis, ttCybernetics, ttGenSynthesis, ttNeuralMotivator, ttNeuralComputing, ttDacxiveAnimators, ttHyperMetabolism, ttX89,
			   ttAntimass, ttGravityDrive, ttXRD, ttTypeIVDrive, ttAdvancedFighters, ttLightWaveDeflector, ttManeuveringJets, ttFleetLogistics,
			   ttEnviroCompensator, ttSarweenTools, ttMicroTechnology, ttNanoTechnology, ttIntegratedEconomy, ttTransfabrication, ttGravitonLaserSystem, ttTransitDiodes,
			   ttDreadnoughtInvasionPod, ttInheritanceSystems,//L1z1x
			   ttValkyrieArmor, ttExotrireme,//Norr
			   ttShuttleLogistics, ttMageonImplants,//Yssaril
			   ttL4Disruptors, ttNoneuclidianShielding,//Letnev
			   ttSalvageOperations, ttMirrorComputing,//Mentak
			   ttSpatialConduitNetwork, ttElectroResonanceTurbines,//Jolnar
			   ttProductionCenters, ttQuantumDatahubNode,//Hacan
			   ttMarkIIAdvancedCarriers, ttSpecOpsTraining,//Sol
			   ttDiplomats, ttInstinctTraining,//Xxcha
			   ttTelepathicMindWeapon, ttHybridCrystalDrives,//Naalu
			   ttFanaticism, ttYinSpinner,//Yin
			   ttFloatingFactories, ttChaosMapping,//Saar
			   ttMagmusReactor, ttNovaSeed,//Muaat
			   ttBiopticRecyclers, ttLazaxGateFolding,//Winnu
			   ttBioplasmosis, ttSporeAcceleration,//Arborecs
			   ttDimensionalSplicers, ttSlaveWormholeGenerator,//Creuss
			   MAX_TECH
			   
};

const string  TechFull[]={	"Hylar V Assualt Laser","Deep Space Cannon","War Sun","Magen Defense Grid","Duranium Armor","Automated Defense turrets","Assault Cannon","Graviton Negator",
								"Stasis capsules","Cybernetics","Gen Synthesis","Neural Motivator","Neural Computing","Dacxive Animators","Hyper Metabolism","X-89 Bacterial Weapon",
								"Antimass Deflector","Gravity Drive","XRD Transporters","Type IV Drive","Advanced Fighters","Light/Wave Deflector","Maneuvering Jets","FleetLogistics",
								"Enviro Compensator","Sarween Tools","Micro Technology","Nano Technology","Integrated Economy","Transfabrication","Graviton Laser System","Transit Diodes",
								"Dreadnought Invasion Pod", "Inheritance Systems",//L1z1x
								"Valkyrie Armor", "Exotrireme",//Norr
								"Shuttle Logistics", "Mageon Implants",//Yssaril
								"L4 Disruptors", "Noneuclidian Shielding",//Letnev
								"Salvage Operations", "Mirror Computing",//Mentak
								"Spatial Conduit Network", "Electro-resonance Turbines",//Jolnar
								"Production Centers", "Quantum Datahub Node",//Hacan
								"Mark II Advanced Carriers", "Spec Ops Training",//Sol
								"Diplomats", "Instinct Training",//Xxcha
								"Telepathic Mind Weapon", "Hybrid Crystal Drives",//Naalu
								"Fanaticism", "Yin Spinner",//Yin
								"Floating Factories", "Chaos-mapping",//Saar
								"Magmus Reactor", "Nova Seed",//Muaat
								"Bioptic Recyclers", "LazaxGate Folding",//Winnu
								"Bioplasmosis","Spore Acceleration",//Arborec
								"Dimensional Splicer","Slave Wormhole Generator"//Creuss
};
