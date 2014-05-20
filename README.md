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

See:

    https://github.com/amassiro/LH-HH-DECAY

from:

    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY
    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY/pythia8153/examples

haronization only:

    ln -s ../../Makefile
    ln -s ../../main98.cc
    make main98
    source config.sh
    ./main98.exe   /tmp/amassiro/HHvbf_100tev_bbww_CV-1-C2V-3-C3-10.lhe /tmp/amassiro/HHvbf_100tev_bbww_CV-1-C2V-3-C3-10.lhe.hepmc   13    0     100
    
    # it doesn't compile on cmsneu ...
    ./main98.exe   /home/amassiro/HH/data/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe    /home/amassiro/HH/datahepmc/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe.hepmc   13    0     10000
    
    ./main98.exe   /tmp/amassiro/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe    /tmp/amassiro/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe.hepmc   13    0     10000
    ls /tmp/amassiro/*.lhe | awk '{print "./main98.exe   "$1"  "$1".hepmc   13    0     10000"}'

    cd /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10
    export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH 
    cd -
    ls /tmp/amassiro/*.lhe | awk '{print "/afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/DelphesHepMC  /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/delphes_card_CMS_modified.tcl    "$1".hepmc.delphes.root    "$1".hepmc    "}'
    
    
Signal:

    cd /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY/pythia8153/examples
    source config.sh
    scp amassiro@cmsneu.cern.ch:/home/amassiro/HH/data/* /tmp/amassiro/

    ls /tmp/amassiro/*.lhe | awk '{print "./main98.exe   "$1"  "$1".hepmc   13    0     10000  \n \
          cd /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10  \n \
             export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH  \n\
             cd -  \n\
             cd /afs/cern.ch/work/a/amassiro/Generation/CMSSW_5_3_14_patch2 \n \
             eval `scram runtime -sh`  \n \
             cd -  \n\
             /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/DelphesHepMC    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/delphes_card_CMS_modified.tcl  "$1".hepmc.delphes.root   "$1".hepmc    \n\
             /afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select cp "$1".hepmc  /eos/cms/store/user/amassiro/HH/Samples/Signal/   \n\
             rm "$1".hepmc  \n\
         "}'  &> doit.sh
    
    ls /tmp/amassiro/*.lhe | awk '{print "./main98.exe   "$1"  "$1".hepmc   13  \n \
             cd /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10  \n \
             export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH  \n\
             cd -  \n\
             cd /afs/cern.ch/work/a/amassiro/Generation/CMSSW_5_3_14_patch2 \n \
             eval `scram runtime -sh`  \n \
             cd -  \n\
             /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/DelphesHepMC    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/delphes_card_CMS_modified.tcl  "$1".hepmc.delphes.root   "$1".hepmc    \n\
             /afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select cp "$1".hepmc  /eos/cms/store/user/amassiro/HH/Samples/Signal/   \n\
             rm "$1".hepmc  \n\
         "}'  &> doit.sh

   ls /tmp/amassiro/ | grep .lhe | grep -v .root | grep -v .hepmc | awk '{print "./main98.exe   /tmp/amassiro/"$1"  /tmp/amassiro/"$1".hepmc   13  \n\
             cd /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10  \n \
             export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH  \n\
             cd -  \n\
             cd /afs/cern.ch/work/a/amassiro/Generation/CMSSW_5_3_14_patch2 \n \
             eval `scram runtime -sh`  \n \
             cd -  \n\
             scp /tmp/amassiro/"$1".hepmc   amassiro@cmsneu.cern.ch:/data/amassiro/HEPMC/HH/  \n\
             rm /tmp/amassiro/"$1".hepmc.delphes.root \n\
             /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/DelphesHepMC    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/delphes_card_CMS_modified.tcl  /tmp/amassiro/"$1".hepmc.delphes.root   /tmp/amassiro/"$1".hepmc    \n\
             scp /tmp/amassiro/"$1".hepmc.delphes.root amassiro@cmsneu.cern.ch:/data/amassiro/HEPMC/HH_Delphes/ \n\
             rm /tmp/amassiro/"$1".hepmc  \n\
         "}'  &> doit.sh
         
         
         
         
         
    ./main98.exe   /tmp/amassiro/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe    /tmp/amassiro/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe.hepmc   13    0     10000
    ls /tmp/amassiro/*.lhe | awk '{print "./main98.exe   "$1"  "$1".hepmc   13    0     10000"}'
    
    
      
Pythia decay of WW into lvlv and hadronization.

    main95.cc

    ln -s ../../Makefile
    ln -s ../../main95.cc
    source config.sh
    make main95

    
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.hepmc
    ./main95.exe   /tmp/amassiro/unweighted_events.lhe           /tmp/amassiro/unweighted_events.lhe.hepmc


    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.0.hepmc    13     0  1000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.1.hepmc    13  1000  2000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.2.hepmc    13  2000  3000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.3.hepmc    13  3000  4000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.4.hepmc    13  4000  5000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.5.hepmc    13  5000  6000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.6.hepmc    13  6000  7000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.7.hepmc    13  7000  8000
    ./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.8.hepmc    13  8000  9000

    
 
    for i in {1..1000}
      do
        echo "./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.$i.hepmc    13  $((i*1000))  $((i*1000+1000))   ;   "
      done

lxbatch script:

    ....
      
      
    
    
Use Delphes:
=======


Delphes simulation:

    rm data/example2.delphes.root
    ../Delphes-3.0.10/DelphesHepMC    delphes_card_CMS_modified.tcl    data/example2.delphes.root ../Delphes-3.0.10/data/test-ttbar.lhe.hepmc
    ../Delphes-3.0.10/DelphesHepMC    delphes_card_CMS_modified.tcl    data/example2.delphes.root data/HHvbf_100tev_bbww_CV-1-C2V-3-C3-10.lhe.hepmc
    
    ../Delphes-3.0.10/DelphesHepMC    delphes_card_CMS_modified.tcl    data/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.delphes.root data/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.lhe.hepmc
    
    
    ../Delphes-3.0.10/DelphesHepMC    delphes_card_CMS_modified.tcl    data/tt_100TeV_unweighted_events.lhe.2.hepmc.root data/tt_100TeV_unweighted_events.lhe.2.hepmc
    
    
    

create ntuple:

    source setup.sh 
    make ntupleMakerHEPMCDelphes.exe
    ./ntupleMakerHEPMCDelphes.exe -i data/example2.delphes.root

    ./ntupleMakerHEPMCDelphes.exe -i data/HHvbf_14tev_bbww_CV-1-C2V-1-C3-10.delphes.root

    ./ntupleMakerHEPMCDelphes.exe -i data/tt_100TeV_unweighted_events.lhe.2.hepmc.root
    
    
    ls data/signalDelphes/EXTERNAL | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/signalDelphes/EXTERNAL/"$1" -o data/trees/"$1".trees.root"}'
    ls data/signalDelphes/Massironi1TB | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/signalDelphes/Massironi1TB/"$1" -o data/trees/"$1".trees.root"}'
    ls data/signalDelphes | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/signalDelphes/"$1" -o data/trees/"$1".trees.root"}'
    ls data/backgroundDelphes/14TeV/ttjj_14TeV/ | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/backgroundDelphes/14TeV/ttjj_14TeV/"$1" -o data/trees/"$1".trees.root"}'
    ls data/backgroundDelphes/100TeV/ttjj_100TeV/ | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/backgroundDelphes/100TeV/ttjj_100TeV/"$1" -o data/trees/"$1".trees.root"}'
    
    ls data/backgroundDelphes/14TeV/NEW14TeV_19May/ | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/backgroundDelphes/14TeV/NEW14TeV_19May/"$1" -o data/trees/"$1".trees.root"}'
    ls data/backgroundDelphes/100TeV/NEW100TeV_19May/ | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/backgroundDelphes/100TeV/NEW100TeV_19May/"$1" -o data/trees/"$1".trees.root"}'
    
    
    ls data/signalDelphes | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/signalDelphes/"$1" -o data/trees/"$1".trees.root"}' | /bin/sh
    ls data/backgroundDelphes/14TeV/ttjj_14TeV/ | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/backgroundDelphes/14TeV/ttjj_14TeV/"$1" -o data/trees/"$1".trees.root"}' | /bin/sh
    ls data/backgroundDelphes/100TeV/ttjj_100TeV/ | awk '{print "./ntupleMakerHEPMCDelphes.exe -i data/backgroundDelphes/100TeV/ttjj_100TeV/"$1" -o data/trees/"$1".trees.root"}' | /bin/sh
    
    
    
    ./ntupleMakerHEPMCDelphes.exe -i data/signalDelphes/HHvbf_14tev_bbww_CV-1-C2V-2-C3-7.lhe.hepmc.delphes.root -o data/trees/HHvbf_14tev_bbww_CV-1-C2V-2-C3-7.lhe.hepmc.delphes.root.trees.root







    
