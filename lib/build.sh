cc -O2 -pthread -shared -fPIC -o librindowmathlib.so mathlib.c
#cc -O2 -fopenmp -msse2 -shared -fPIC -o librindowmathlib.so mathlib.c
#cc -O3 -msse2 -shared -fPIC -o librindowmathlib.so mathlib.c
#cc -L./ testclient.c -o testclient -lrindowmathlib
