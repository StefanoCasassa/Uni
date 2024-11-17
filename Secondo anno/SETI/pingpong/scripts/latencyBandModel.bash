#! /bin/bash
# Expect protocol name as first parameter (tcp or udp)

# Define input and output file names
ThroughFile="../data/$1_throughput.dat";
PngName="../data/LB$1.png";

#getting the first and the last line of the file
HeadLine=($(head $ThroughFile --lines=1))
TailLine=($(tail $ThroughFile --lines=1))

#getting the information from the first and the last line
FirstN=${HeadLine[0]}
LastN=${TailLine[0]}

# TO BE DONE START
FirstTN=${HeadLine[2]}
LastTN=${TailLine[2]}
gcc "../src/BeLCALC.c" -o Calc
Band=$(./Calc $FirstN $FirstTN $LastN $LastTN 1)
Latency=$(./Calc $FirstN $FirstTN $LastN $LastTN 2)
# TO BE DONE END


# Plotting the results
gnuplot <<-eNDgNUPLOTcOMMAND
  set term png size 900, 700
  set output "${PngName}"
  set logscale x 2
  set logscale y 10
  set xlabel "msg size (B)"
  set ylabel "throughput (KB/s)"
  set xrange[$FirstN:$LastN]
  lbmodel(x)= x / ($Latency + (x/$Band))

# TO BE DONE START
  
  lbf(x) = x / ( $Latency + x / $Band )
  plot lbf(x) title "Latency-Bandwidth model with L=$Latency and B=$Band" at screen 0.85, 0.15 \
    with linespoints, \
    "../data/$1_throughput.dat" using 1:3 title "$1 median Throughput" at screen 0.85, 0.125 \
  	with linespoints 

# TO BE DONE END

  clear

eNDgNUPLOTcOMMAND
