//
//  MCPoly.hpp
//  LatticePoly
//
//  Created by mtortora on 30/11/2019.
//  Copyright © 2019 ENS Lyon. All rights reserved.
//

#ifndef MCPoly_hpp
#define MCPoly_hpp

#include "MCTad.hpp"


class MCPoly
{
public:
	MCPoly(MCLattice*);
	~MCPoly();

	void Init(int);
	void GenerateRandom(int);
	
	void ToVTK(int);
	void FromVTK(int);

	void TrialMove(double*);
	void AcceptMove();
	
	double GetSpecificEnergy() const {return 0.;};

	MCTad* tad;
	MCLattice* lat;
	
protected:
	int tadType[Nchain];
	int tadConf[Nchain];
	int tadBond[Nchain-1];
	
private:
	double centreMass[3];
};


#endif /* MCPoly_hpp */
