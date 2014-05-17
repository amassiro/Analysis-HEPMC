From LHE to trees
==============

hepmc and delphes trees on the batch system

HEPMC
=======

Input:

    LHE

where:

    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC
    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/lxbatch

    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY/pythia8153/examples

kate:

    cmsneu
    CMSNEU-LH2013


How:

    python PrepareAndSubmit.py    1000     ttjj     14TeV
    python PrepareAndSubmit.py    1000     ttjj     100TeV


But first:

    cd /afs/cern.ch/work/a/amassiro/Generation/CMSSW_5_3_14_patch2/src/
    cmsenv
    cd /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/
    export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
    make -j 4







ls /tmp/amassiro/*.hepmc | awk '{print "/afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/DelphesHepMC    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/delphes_card_CMS_modified.tcl  "$1".delphes.root "$1"  "}'
ls /tmp/amassiro/*.hepmc | awk '{print "/afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/DelphesHepMC    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/delphes_card_CMS_modified.tcl  "$1".delphes.root "$1"  "}' | /bin/sh





