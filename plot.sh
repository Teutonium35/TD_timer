#! /bin/sh

rm -rf results
mkdir results
mkdir results/data
mkdir results/data/normal
mkdir results/data/normal_with_taskset
mkdir results/data/pert
mkdir results/plot
mkdir results/plot/normal
mkdir results/plot/normal_with_taskset
mkdir results/plot/pert
for timer in $((10000)) $((100000)) $((1000000)); do
low_bound=$(($timer/2))
high_bound=$(($timer*2))

echo "$timer"
echo "$low_bound"
echo "$high_bound"

echo "./bin/timer_jitter $timer | ./bin/histogramme 1000 $low_bound $high_bound > results/data/normal/$timer"

./bin/timer_jitter $timer | ./bin/histogramme 1000 $low_bound $high_bound > "results/data/normal/$timer"

echo "$timer normal" >> "results/math"

echo "./bin/timer_jitter $timer | ./bin/calculStats $timer >> results/math"

./bin/timer_jitter $timer | ./bin/calculStats $timer >> "results/math"

output="| tee results/plot/normal/$timer.png"

gnuplot << EOF
	set terminal gif size 800,600
	set title "$timer"
	set output '$output'
	# échelle log en ordonnée
	set logscale y 10
	# afficher le contenu du fichier
	plot [] [0.1:] "results/data/normal/$timer" notitle with boxes
	pause mouse
EOF

echo "\n" >> "results/math"





echo "taskset -c 1 ./bin/timer_jitter $timer | ./bin/histogramme 1000 $low_bound $high_bound > results/data/normal_with_taskset/$timer"

taskset -c 1 ./bin/timer_jitter $timer | ./bin/histogramme 1000 $low_bound $high_bound > "results/data/normal_with_taskset/$timer"

echo "$timer normal with taskset" >> "results/math"

echo "taskset -c 1 ./bin/timer_jitter $timer | ./bin/calculStats $timer >> results/math"

taskset -c 1 ./bin/timer_jitter $timer | ./bin/calculStats $timer >> "results/math"

output="| tee results/plot/normal_with_taskset/$timer.png"

gnuplot << EOF
	set terminal gif size 800,600
	set title "$timer"
	set output '$output'
	# échelle log en ordonnée
	set logscale y 10
	# afficher le contenu du fichier
	plot [] [0.1:] "results/data/normal_with_taskset/$timer" notitle with boxes
	pause mouse
EOF

echo "\n" >> "results/math"



echo "taskset -c 1 ./bin/pert &"

taskset -c 1 ./bin/pert &

echo "taskset -c 1 ./bin/timer_jitter $timer | ./bin/histogramme 1000 $low_bound $high_bound > results/data/pert/$timer"

taskset -c 1 ./bin/timer_jitter $timer | ./bin/histogramme 1000 $low_bound $high_bound > "results/data/pert/$timer"

echo "$timer pert" >> "results/math"

echo "taskset -c 1 ./bin/timer_jitter $timer | ./bin/calculStats $timer >> results/math"

taskset -c 1 ./bin/timer_jitter $timer | ./bin/calculStats $timer >> "results/math"

output="| tee results/plot/pert/$timer.png"

gnuplot << EOF
	set terminal gif size 800,600
	set title "$timer"
	set output '$output'
	# échelle log en ordonnée
	set logscale y 10
	# afficher le contenu du fichier
	plot [] [0.1:] "results/data/pert/$timer" notitle with boxes
	pause mouse
EOF

echo "\n" >> "results/math"

echo "pkill -f pert"

pkill -f pert

done

exit 0