rm main; rm *.o;
g++ rectangulo.cpp -c -lm;
g++ circulo.cpp -c -lm;
g++ main.cpp rectangulo.o circulo.o -o main
