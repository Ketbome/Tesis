#!/bin/bash
#chmod +x script.sh
files=("ex2_1_8.bch" "ex2_1_9.bch" "ex6_1_3bis.bch" "launch.bch" "ex14_2_7.bch" "ex2_1_9fact.bch" "ex6_1_4.bch" "ex6_2_6.bch" "ex6_2_8.bch" "ex7_3_4.bch" "ex7_3_4bis.bch" "ex14_2_3.bch" "haverly.bch" "like.bch")

for file in ${files[@]}
do
  for i in {1..10}
  do
     ./__build__/src/ibexopt benchs/optim/medium/$file --random-seed=$i >> commands.log
  done
done

#----------------------------------------------------------------------------------------------

#!/bin/bash
#chmod +x script.sh
files=("ex2_1_8.bch" "ex2_1_9.bch" "ex6_1_3bis.bch" "launch.bch" "ex14_2_7.bch" "ex2_1_9fact.bch" "ex6_1_4.bch" "ex6_2_6.bch" "ex6_2_8.bch" "ex7_3_4.bch" "ex7_3_4bis.bch" "ex14_2_3.bch" "haverly.bch" "like.bch")

for file in ${files[@]}
do
  for i in {1..30}
  do
     ./__build__/src/ibexopt benchs/optim/medium/$file --random-seed=$i >> commands.log
  done
done


