reset
set title 'Compute-pi Comparsion'
set xlabel 'N'
set ylabel 'Time (sec)'
set datafile separator ","
set terminal png font 'Verdana,10'
set output 'runtime.png'
set key left

plot 'result_clock_gettime.csv' using 1:2 with linespoints linewidth 2 title 'baseline' , \
'' using 1:4 with linespoints linewidth 2 title 'OpenMP_2', \
'' using 1:6 with linespoints linewidth 2 title 'OpenMP_4', \
'' using 1:8 with linespoints linewidth 2 title 'AVX', \
'' using 1:10 with linespoints linewidth 2 title 'AVX_Unroll', \
'' using 1:12 with linespoints linewidth 2 title 'Leibniz', \
'' using 1:14 with linespoints linewidth 2 title 'Leibniz_omp4'
