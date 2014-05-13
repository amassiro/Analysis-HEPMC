From LHE to trees
==============

hepmc and delphes trees on the batch system

HEPMC
=======

Input:

    LHE
    
where:

    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC
    
    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY/pythia8153/examples
    
kate:

    cmsneu
    CMSNEU-LH2013

    
How:

    python PrepareAndSubmit.py    1000     ttjj     14TeV
    
    
But first:

    cd /afs/cern.ch/work/a/amassiro/Generation/CMSSW_5_3_14_patch2/src/
    cmsenv
    cd /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/
    export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
    make -j 4

    
    