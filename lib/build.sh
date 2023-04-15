cc -O2 -pthread -shared -fPIC -o librindowmatlib.so matlib.c
#cc -O2 -fopenmp -msse2 -shared -fPIC -o librindowmatlib.so matlib.c
#cc -O3 -msse2 -shared -fPIC -o librindowmatlib.so matlib.c
#cc -L./ testclient.c -o testclient -lrindowmatlib
