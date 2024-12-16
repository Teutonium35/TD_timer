#! /bin/sh

rm -rf "results/math"
for timer in $((10000)) $((100000)) $((1000000)); do
low_bound=$(($timer/2))
high_bound=$(($timer*2))

echo "$timer"
echo "$low_bound"
echo "$high_bound"

echo "./timer_jitter $timer | ./histo 1000 $low_bound $high_bound"

echo "$timer" >> "results/math"


./timer_jitter $timer | ./histo 1000 $low_bound $high_bound > "results/data/normal_with_taskset/$timer"

echo "./calculStats results/data/normal_with_taskset/$timer >> results/math"

./calculStats "results/data/normal_with_taskset/$timer" >> "results/math"

output="| tee results/plot/normal_with_taskset/$timer.png"

# gnuplot << EOF
# 	set terminal gif size 800,600
# 	set title "$filename"
# 	set output '$output'
# 	# échelle log en ordonnée
# 	set logscale y 10
# 	# afficher le contenu du fichier
# 	plot [] [0.1:] "results/data/normal_with_taskset/$timer" notitle with boxes
# 	pause mouse
# EOF
done

exit 0