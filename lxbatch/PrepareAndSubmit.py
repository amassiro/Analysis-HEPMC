#!/bin/env python

import os
import subprocess
import sys

numOfProcesses = int(sys.argv[1])
process = sys.argv[2]

wd = os.getcwd()
queue = '8nh'
#queue = '1nh' # -> not enough !?!?
#queue = '8nm' #--> not enough time!
newfol = 'makeDecay_{PROCESS}'.format(PROCESS=process)
os.system('mkdir -p {PWD}/{NEW}'.format(PWD=wd,NEW=newfol))



if len(sys.argv) == 1:
   print "uff, not enough information"
   sys.exit(0)


./main95.exe   /tmp/amassiro/100TeV_unweighted_events.lhe    /tmp/amassiro/100TeV_unweighted_events.lhe.$i.hepmc    13  $((i*1000))  $((i*1000+1000))  




for i in range(numOfProcesses) :
  min = i*1000
  max = i*1000+1000
  
  command = '#!/bin/bash\n\
             cd {PWD}\n\
             source config.sh\n\
             ./main95.exe    blabla.lhe    blabla.{NUM}.hepmc  {MIN}   {MAX}\n \
             '.format(PWD=wd, ITER=str(i), NUM=i, MIN=min, MAX=max).replace(' ','')

  fname = '/'.join([wd,newfol,'sub_'+str(i)+'.sh'])
  f1 = open(fname, 'w+')
  print >> f1 , command
  os.system('chmod 755 {FILE}'.format(FILE=fname))
  f1.close()

for i in range(numOfProcesses) :
  fname = '/'.join([wd,newfol,'sub_'+str(i)+'.sh'])
  subprocess.Popen(['bsub -q {QUEUE} < {FILE}'.format(QUEUE=queue,FILE=fname)], stdout=subprocess.PIPE, shell=True)



