//
//  MCReplicPoly.hpp
//  LatticePoly
//
//  Created by mtortora on 02/10/2020.
//  Copyright © 2020 ENS Lyon. All rights reserved.
//

#ifndef MCReplicPoly_hpp
#define MCReplicPoly_hpp

#include "MCHeteroPoly.hpp"


class MCReplicPoly: public MCHeteroPoly
{
public:
	MCReplicPoly(MCLattice*);
	
	void Init(int);
	void TrialMove(double*);
	
protected:
	void Replicate(MCTad*);
	void ReplicateTADs(MCTad*);
	void ReplicateBonds(MCTad*);
	
	void UnsetFork(MCTad*);
	void Update();

	int Nfork;

	std::vector<MCTad*> activeForks;
};


#endif /* MCReplicPoly_hpp */
