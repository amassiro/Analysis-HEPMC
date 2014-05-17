#!/bin/env python

import os
import subprocess
import sys

numOfProcesses = int(sys.argv[1])
process = sys.argv[2]
energy  = sys.argv[3]


wd = os.getcwd()
#queue = '8nm'
queue = '1nh' # -> not enough !?!?
#queue = '8nm' #--> not enough time!
newfol = 'makeDecay_{PROCESS}'.format(PROCESS=process)
os.system('mkdir -p {PWD}/{NEW}'.format(PWD=wd,NEW=newfol))



if len(sys.argv) == 1:
   print "uff, not enough information"
   sys.exit(0)


#./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.$i.hepmc    13  $((i*1000))  $((i*1000+1000))  




for i in range(numOfProcesses) :
  min = i*1000
  max = i*1000+1000
  command = '#!/bin/bash\n\
             cd /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/LH-HH-DECAY/pythia8153/examples/\n\
             source config.sh\n\
             FILE=/tmp/unweighted_events_{PROCESS}_{ENERGY}.lhe \n\
             if [ -f $FILE ];\n\
             then\n\
                 echo "File $FILE exists."\n\
                 sleep 30 \n\
             else\n\
                 echo "File $FILE does not exist."\n\
                 FILE=/tmp/unweighted_events_{PROCESS}_{ENERGY}.lhe.gz \n\
                 if [ -f $FILE ];\n\
                 then\n\
                     echo "File $FILE exists, unzipping now."\n\
                     sleep 30 \n\
                 else\n\
                     cp /afs/cern.ch/user/a/amassiro/public/xLHTF/hhwwbb/{PROCESS}/{ENERGY}/unweighted_events.lhe.gz    /tmp/unweighted_events_{PROCESS}_{ENERGY}.lhe.gz   \n\
                     cd /tmp/   \n\
                     gunzip -d /tmp/unweighted_events_{PROCESS}_{ENERGY}.lhe.gz   \n\
                 fi \n\
                 cd - \n\
             fi \n\
             /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/lxbatch/splitLHE  /tmp/unweighted_events_{PROCESS}_{ENERGY}.lhe         /tmp/unweighted_events_{PROCESS}_{ENERGY}.{NUM}.lhe       {MIN}   {MAX}  \n \
             ./main95.exe    /tmp/unweighted_events_{PROCESS}_{ENERGY}.{NUM}.lhe   /tmp/unweighted_events_{PROCESS}_{ENERGY}.{NUM}.hepmc     \n \
             echo "now run delphes" \n \
             cd /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10  \n\
             export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH  \n\
             cd -  \n\
             cd /afs/cern.ch/work/a/amassiro/Generation/CMSSW_5_3_14_patch2 \n \
             eval `scram runtime -sh`  \n \
             cd -  \n\
             /afs/cern.ch/work/a/amassiro/Generation/Delphes-3.0.10/DelphesHepMC    /afs/cern.ch/user/a/amassiro/work/Generation/HH/Pythia8/Analysis-HEPMC/delphes_card_CMS_modified.tcl    /tmp/unweighted_events_{PROCESS}_{ENERGY}.{NUM}.hepmc.delphes.root   /tmp/unweighted_events_{PROCESS}_{ENERGY}.{NUM}.hepmc    \n\
             /afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select cp /tmp/unweighted_events_{PROCESS}_{ENERGY}.{NUM}.hepmc.delphes.root   /eos/cms/store/user/amassiro/HH/SamplesNew/{PROCESS}/{ENERGY}/ \n\
             '.format(PWD=wd, PROCESS=process, ENERGY=energy, NUM=i, MIN=min, MAX=max)



  fname = '/'.join([wd,newfol,'sub_'+str(i)+'.sh'])
  f1 = open(fname, 'w+')
  print >> f1 , command
  os.system('chmod 755 {FILE}'.format(FILE=fname))
  f1.close()

print "now submit"
for i in range(numOfProcesses) :
  fname = '/'.join([wd,newfol,'sub_'+str(i)+'.sh'])
  subprocess.Popen(['bsub -q {QUEUE} < {FILE}'.format(QUEUE=queue,FILE=fname)], stdout=subprocess.PIPE, shell=True)
  os.system('sleep 5')



