Analysis-HEPMC
==============

ntuple producer on top of showered and hadronized events.

    HEPMC as input
    ROOT trees as output

    

    
Istall pythia

    cd pythia8153/
    mv configure old_configure; ln -s ../LH-HH-DECAY/configure .
    ./configure --enable-gzip  --with-hepmcversion=2.06.08
    make -j 8

    

Run Hadronizer
=======

from:

    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY
    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY/pythia8153/examples

haronization only:

    ln -s ../../Makefile
    ln -s ../../main98.cc
    make main98
    source config.sh
    ./main98.exe   /tmp/amassiro/HHvbf_100tev_bbww_CV-1-C2V-3-C3-10.lhe /tmp/amassiro/HHvbf_100tev_bbww_CV-1-C2V-3-C3-10.lhe.hepmc   13    0     100
    
    
Use Delphes:
=======


Delphes simulation:

    rm data/example2.delphes.root
    ../Delphes-3.0.10/DelphesHepMC    delphes_card_CMS_modified.tcl    data/example2.delphes.root ../Delphes-3.0.10/data/test-ttbar.lhe.hepmc
    ../Delphes-3.0.10/DelphesHepMC    delphes_card_CMS_modified.tcl    data/example2.delphes.root data/HHvbf_100tev_bbww_CV-1-C2V-3-C3-10.lhe.hepmc
    

create ntuple:

    source setup.sh 
    make ntupleMakerHEPMCDelphes.exe
    ./ntupleMakerHEPMCDelphes.exe -i data/example2.delphes.root


