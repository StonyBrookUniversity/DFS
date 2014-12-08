void networkControlLogic2::updateRoutingDeletLink(int s,int d) {
//	BFSOneNodeUpdateRoutesUpdateAll();
	edge ff;
	ff.s=s;
	ff.d=d;

	routingNeedsUpdate=false;
	if (this->topology[s][d]>0) return;
	BFSOneNodeUpdateRoutes(s);
	BFSOneNodeUpdateRoutes(d);
	flowIt it;
	for (it=this->flowsUsingThisEdge[s][d].begin();it!=flowsUsingThisEdge[s][d].begin();it++) {
//		string fID=it->first;
		flowPtr f=*it;
		list<edge>::iterator it2,it3;
		it2=f->second.edgesUsed.begin();
		while (!((*it2)==ff)) ++it2;
		it3=it2;
		for (;it2!=f->second.edgesUsed.end();it2++) {
			this->FlowRoutingTable[it2->s].erase(f->second.flowID);
		}
		reRouteElephent(f,it3->s);
		this->flowsUsingThisEdge[s][d].clear();
	}
	//*/		 
}






































void networkControlLogic2::reRouteElephent(flowPtr f,int s) {
		
	int nextHop=this->RoutingTable[s][f->second.destination][0].first;
	edge ff;
	ff.s=s;
	ff.d=nextHop;
	f->second.edgesUsed.push_back(ff);
	this->flowsUsingThisEdge[ff.s][ff.d].insert(f);
	this->flowsUsingThisEdge[ff.d][ff.s].insert(f);
	this->FlowRoutingTable[ff.s][f->second.flowID].first=ff.d;
	this->FlowRoutingTable[ff.s][f->second.flowID].second=0;
	//Traffic Engineering Needed


	ff.s=nextHop;
	while (nextHop!=f->second.destination) {
		ff.s=nextHop;	
		nextHop=this->RoutingTable[nextHop][f->second.destination][0].first;
		if (this->topology[nextHop][ff.s]) ff.d=nextHop;
		this->flowsUsingThisEdge[ff.s][ff.d].insert(f);
		this->flowsUsingThisEdge[ff.d][ff.s].insert(f);

		this->FlowRoutingTable[ff.s][f->second.flowID].first=ff.d;
		this->FlowRoutingTable[ff.s][f->second.flowID].second=0;
		//Traffic Engineering Needed


		f->second.edgesUsed.push_back(ff);
		if (this->topology[nextHop][ff.s]) break;
	}
}
