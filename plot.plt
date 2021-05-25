###############################
name1="data"

data1=sprintf("%s.dat",name1)


epsname = "plot.eps"

#eps�t�@�C���̃T�C�Y�ύX
epswidth = 7
epsheight= 5

###############################
set autoscale
#unset mouse
set multiplot layout 1,1

set style line 1 lt 1
set style line 2 lt 2
set style line 3 lt 3
set style line 4 lt 4
#set ticslevel 0
unset xlabel
set xlabel "Frequency [Hz]"
unset grid


###########################################
#			     �����lx	1			  #
###########################################
set autoscale
set ylabel "Value []"
set xlabel "Time [s]"
#set xrange [10:500]
p data1 u 1:3 every 1 w l lc "#00c800" ti "calculate",\
  data1 u 1:2 every 1 w l lc "#c80000" ti "ideal",\



unset multiplot
