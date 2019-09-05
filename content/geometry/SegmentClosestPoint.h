/**
* Author: Letícia Freire
* Description: Returns the closest point to p in the segment from point 
* s to e as well as the distance between them
*/


pair<P,double> SegmentClosestPoint(P &s, P &e, P &p){
	P ds=p-s, de=p-e;
	if(e==s)
		return {s, ds.dist()};
	P u=(e-s).unit();
	P proj=u*ds.dot(u);
	if(onSegment(s, e, proj+s))
		return {proj+s, (ds-proj).dist()};
	double dist_s=ds.dist(), dist_e=de.dist();
	if(cmp(dist_s, dist_e)==1)
		return {s, dist_s};
	return{e, dist_e};
}
