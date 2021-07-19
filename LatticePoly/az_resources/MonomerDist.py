# -*- coding: utf-8 -*-
##
# MonomerDist.py
# LatticePoly
##
# Based on mtortora's code.
# Copyright © 2021 ENS Lyon. All rights reserved.
##

import os
import sys

import numpy as np

from scipy.spatial import cKDTree

from vtkReader import vtkReader


class MonomerDmap():

    def __init__(self, outputDir, initFrame):
        self.reader = vtkReader(outputDir, initFrame,
                                readLiq=False, readPoly=True, backInBox=True)

        #self.anisoFile = os.path.join(self.reader.outputDir, "polyAniso.res")
        self.monomerFile = os.path.join(self.reader.outputDir, "monomerdistmat_z.res")
        self.contactFile = os.path.join(self.reader.outputDir, "contactProb_z.res")

        if os.path.exists(self.monomerFile):
            print("Files %s' already exist - aborting" % (self.monomerFile))
            sys.exit()

    def Compute(self):
        #self.polyAniso = np.zeros((self.reader.N, self.reader.nDom), dtype=np.float32)
        self.monomer     = np.zeros((self.reader.nTad, self.reader.nTad), dtype=np.float32)
        self.contactProb = np.zeros((self.reader.nTad, self.reader.nTad), dtype=np.float32)
        

        for i in range(initFrame, self.reader.N):
            self.ProcessFrame(i)

            if (i+1) % 10 == 0:
                print("Processed %d out of %d configurations" %
                      (i+1, self.reader.N))

        self.monomer     = self.monomer/(self.reader.N-initFrame)
        self.contactProb = self.contactProb/(self.reader.N-initFrame)
        np.fill_diagonal(self.contactProb, self.contactProb.diagonal() + 1)  

    def ProcessFrame(self, i):
        data = next(self.reader)

        tree1   = cKDTree(data.polyPos, boxsize = data.boxDim)
        sparse1 = tree1.sparse_distance_matrix(tree1,np.sqrt(3*(data.boxDim[0]**2))) 
        sparse1 = sparse1.toarray()
        self.monomer = self.monomer + sparse1
        

        pairs = tree1.query_pairs(r = 0.71) # NN distance FCC lattice 1/np.sqrt(2)
        for (i,j) in pairs:
            self.contactProb[i,j] = self.contactProb[i,j] + 1



    def Print(self):
        #np.savetxt(self.anisoFile, self.polyAniso)
        np.savetxt(self.monomerFile, self.monomer )
        np.savetxt(self.contactFile, self.contactProb )

        print("\033[1;32mPrinted avg.contact probability to '%s'\033[0m" %self.contactFile)
        print("\033[1;32mPrinted distance map to '%s'\033[0m" % self.monomerFile)


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("\033[1;31mUsage is %s outputDir initFrame\033[0m" % sys.argv[0])
        sys.exit()

    outputDir = sys.argv[1]
    initFrame = int(sys.argv[2])

    monom = MonomerDmap(outputDir, initFrame=initFrame)

    monom.Compute()
    monom.Print()

