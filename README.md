# trabalho-2-grafos

Garantir que a biblioteca <math.h> está sendo compilada corretamente (adicionando a flag -lm no GCC, por exemplo). Caso dê erro de compilação por falta dessa macro, pode ser usado um valor inteiro muito grande (como 99999999).

Usar o comando no terminal: 
gcc main.c -o programa -lm
./programa

Para testar os arquivos tsp:
gcc main.c -o tsp -lm

./tsp < tsp29.t
ou
Get-Content tsp436.tsp | ./tsp.exe


