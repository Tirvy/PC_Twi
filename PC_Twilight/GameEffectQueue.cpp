/*GameEffectQueue::GameEffectQueue(){
	GameEffects = new PowVec<GameEffect>;
	GameEffects->elem = new EmptyGameEffect;
	GameEffects->next = 0;
	lastGameEffect = GameEffects;
}
void GameEffectQueue::Init(GameEffectQs squeue){
	queue = squeue;
}
GameEffectQueue::GameEffectQueue(GameEffectQs squeue){
	queue = squeue;
	GameEffects = new PowVec<GameEffect>;
	GameEffects->elem = new EmptyGameEffect;
	GameEffects->next = 0;
	lastGameEffect = GameEffects;
}
int GameEffectQueue::Add(GameEffect* sGameEffect){
	//if (! sGameEffect->GetQ() == queue)
	//	throw throwable ("Dammit, leeroy!");
	lastGameEffect->next = new PowVec<GameEffect>;
	lastGameEffect = lastGameEffect->next;
	lastGameEffect->elem = sGameEffect;
	lastGameEffect->next = 0;
	return 1;
}
int GameEffectQueue::Execute(ExecuteParams EP){
	PowVec<GameEffect> *temp,*pretemp;
	pretemp = GameEffects;
	temp = pretemp->next;
	while(temp!=0){
		if (temp->elem == 0)
			throw throwable ("GameEffectQueue::Execute got no GameEffect!");
		if (temp->elem->Execute(EP) == er_delete){
			pretemp->next = temp->next;
			temp->next = 0;
			delete temp;
			temp = pretemp->next;
		}
		else{
			pretemp = temp;
			temp = pretemp->next;
		}
	}
	return 1;
}*/