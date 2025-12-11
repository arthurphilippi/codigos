#include <stdio.h>
#include <stdlib.h>


//INTERPRETADOR DE BRAINFUCK FEITO EM C
//ALUNOS: Arthur Philippi, Matheus Hames;

int main(){

    FILE *pf; //Dedica um arquivo a PF
    char *vetor_cru; //Cria um ponteiro para o vetor cru, para ser alocado a memoria depois
    char *vetorbf;
    int tamanho = 30000; //Tamanho de um vetor Brainfuck
    int indice = 0; //Explicarei quando chegar em uso
    int indice2 = 0;
    int indice3 = 0;
    size_t bytes;
    char *vetorgeral;
    int *vetorloops;
    int *armazenamentoposicoes;

    vetorbf = calloc(30000, sizeof(char)); //Aloca um vetor de 30000 chars, sendo todas elas 0, vazias
    vetor_cru = calloc(30000, sizeof(char));
    vetorgeral = calloc(30000, sizeof(char));
    vetorloops = calloc(30000, sizeof(int));
    armazenamentoposicoes = calloc(30000, sizeof(int)); //30000 Ints

    pf = fopen("C:\\Users\\discente\\Documents\\interp\\intertp\Brainfuck.bf", "r"); //Abre o arquivo, tendo que dizer o caminho, e "r" esta em modo de leitura

    if(pf == NULL){ //Se o arquivo não existe...
        printf("Nao foi achado esse arquivo!");
    }
    while ((bytes = fread(vetor_cru, sizeof(char), tamanho, pf)) > 0){ //FREAD vai ler de PF, tamanho caracteres, cada um com o tamanho de sizeof(char), e vai guardar em vetor cru. essa ação vai retornar quantos elementos foram lidos, por isso bytes > 0, pois quando bytes for > 0, vai ter coisas para ler
        for(int i = 0; i < bytes; i++){ //Para cada coisa do vetor, ele vai rodar esse loop
            char caracter = vetor_cru[i]; //Vai guardar o caracter que está nessa posição em char caracter
            if(caracter == '>' || caracter == '<' ||
               caracter == '+' || caracter == '-' ||
               caracter == ',' || caracter == '.' || //Se o caracter for um desses, que pertecem a linguagem brainfuck
               caracter == '[' || caracter == ']'){

                vetorbf[indice] = caracter; //Vai guardar em vetorbf, e vai guardar na posicao indice, por isso indice = 0 la em cima

                if(caracter == '['){ //Se o caracter for a abertura de um loop, vai guardar sua posicao (indice) em vetor loops, indice3 é apenas um indice novo
                    vetorloops[indice3] = indice;
                    indice3++;
                }
                if(caracter == ']' && indice3 <= 0 ){
                    printf("Nao achei a abertura de um loop!");
                    return 0; //Se o caracter for um fechamento de um loop, e o indice3 for menor ou igual a 0, quer dizer que nao existiu a abertura desse loop, entao, retorna erro
                }else if(caracter == ']' && indice3 > 0){
                    indice3--; //Se o caracter for um fechamento de um loop e o indice3 for maior que 0, ou seja, há uma abertura
                    int posicao_abertura = vetorloops[indice3]; //Cria duas variáveis, uma para a posicao de abertura e outra para a posicao de fechamento, para guardar essas posicoes temporariamente
                    int posicao_fechamento = indice;
                    armazenamentoposicoes[posicao_abertura] = posicao_fechamento; //Guarda as mesmas em um vetor, onde o indice da posicao do fechamento é a posicao de sua abertura, e vice versa
                    armazenamentoposicoes[posicao_fechamento] = posicao_abertura; //Isso serve para que sabermos para onde voltar, caso o loop não esteja completo
                }

                }
            indice++; //Vai aumentar o valor de indice antes de retornar a proxima iteração do for loop

            }

            }
            if(indice3 > 0){ //Caso o indice3 for maior que 0, ou seja, depois da filtragem de loops, o indice ainda mostra que há uma abertura sem par, ele retorna erro
                printf("Nao achei um fechamento de loop");
                return 0;
        }

    for(int i = 0; i < indice; i++){ //Faz um loop conforme o tamanho do vetorbf, que é indice, pois para cada caracter do vetorbf, adicionamos 1 a indice
        switch(vetorbf[i]){ //Switch case com o caracter na posicao i do vetorbf
            case '>':
                indice2++; //Caso for >, significa ir um espaço de memoria para o lado, então, adiciona 1 ao indice2, que é o indice do vetorbf, que é o vetor total, com o código brainfuck limpo
                break;
            case '<':
                indice2--; // O contrario de >, vai um espaço de memoria para a esquerda
                break;
            case '+':
                vetorgeral[indice2]++; //vetorgeral é o vetor em que vai ocorrer as mudanças que o vetorbf manda, então, se for "+", diz que é para adicionar um ao espaço de memoria em que estamos atualmente
                break;
            case '-':
                vetorgeral[indice2]--; //O contrario de "+", remove 1 do espaço de memoria atual
                break;
            case ',':
                vetorgeral[indice2] = getchar(); //"," Diz que o usuario ira dar input de um caracter, logo, o comando getchar() serve para isso, receber um input de caracter
                break;
            case '.':
                vetorgeral[indice2] = (vetorgeral[indice2] % 128 + 128) % 128; //Faz com que o numero que esta na posicao atual vire um numero de 0 a 128, limite do ASCII
                putchar(vetorgeral[indice2]); //"." Diz para colocar um caracter na tela, com base em seu valor ASCII, entao, se o valor for 76, vai ser L, isso que o putchar faz
                break;
            case '[':
                if(vetorgeral[indice2] == 0){ //Se for uma abertura de loop, o brainfuck diz que se for igual a 0, o loop nao vai rodar, entao aqui diz que, se for igual a 0 a posicao de memoria atual
                    i = armazenamentoposicoes[i]; //Ele vai pular para armazenamentoposicoes[i], pois i representa a posicao da abertura, e como vimos antes, o indice de armazenamentoposicoes do fechamento de um loop e a posicao da abertura de seu loop
                }
                break;
            case ']':
                if(vetorgeral[indice2] != 0){ //Se for um fechamento de loop, se o espaco de memoria atual for diferente de 0, o loop nao pode parar, tem que voltar a posicao da abertura do loop, entao
                    i = armazenamentoposicoes[i]; //Se essa condicao for verdadeira, i = armazenamentoposicoes[i], pois o indice da abertura de um loop e a posicao de seu fechamento, igual fizemos la em cima
                }
                break;
            }

        }

    free(vetorbf); //Libera a memoria dos vetores no final do programa, para evitar espaços de memorias reservados para nada
    free(vetor_cru);
    free(vetorgeral);
    free(vetorloops);
    free(armazenamentoposicoes);
    fclose(pf); //fecha o arquivo que lemos o brainfuck
    return 0;
}
//Foi dahora fazer, dificil, mas foi dahora, funciona bem, aqui há exemplos de programas em brainfuck e o que eles fazem:
/*
++++++++[>+>++++<<-]>++>>+<[-[>>+<<-]+>>]>+[
    -<<<[
        ->[+[-]+>++>>>-<<]<[<]>>++++++[<<+++++>>-]+<<++.[-]<<
    ]>.>+[>>]>+
]

TRIANGULO LEGAL

>++++++++[<+++++++++>-]<.
>++++[<+++++++>-]<+.
+++++++..
+++.
>>++++++[<+++++++>-]<++.
------------.
>++++++[<+++++++++>-]<+.
<.
+++.
------.
--------.
>>>++++[<++++++++>-]<+.

HELLO WORLD

++++[>+++++<-]>[<+++++>-]+<+[
    >[>+>+<<-]++>>[<<+>>-]>>>[-]++>[-]+
    >>>+[[-]++++++>>>]<<<[[<++++++++<++>>-]+<.<[>----<-]<]
    <<[>>>>>[>>>[-]+++++++++<[>-<-]+++++++++>[-[<->-]+[<<<]]<[>+<-]>]<<-]<<-
]

QUADRADOS PERFEITOS ATE 10.000

--->--->>>>->->->>>>>-->>>>>>>>>>>>>>>>>>+>>++++++++++[
  <<++[
    --<+<<+<<+>>>>[
      >[<->>+++>>[-]+++<<<+[<++>>+<--]]+>+++++[>>+++++++++<<-]
      >>++++.[-]>>+[<<<<+>>+>>-]<<<<<<[>+<-]<<
    ]++++++++++.[-]>++
  ]-->>[-->[-]>]<<[
    >>--[
      -[
        -[
          -----[>+>+++++++<<+]-->>-.----->,[<->-]<[[<]+[->>]<-]<[<<,[-]]>>>>
        ]>
      ]<[
        >-[+<+++]+<+++[+[---->]+<<<<<<[>>]<[-]]
        >[<+[---->]++[<]<[>]>[[>]+>+++++++++<<-[<]]]>[>>>>]
      ]<[
        -[[>+>+<<-]>[<+>-]++>+>>]<[<<++[-->>[-]]>[[-]>[<<+>>-]>]]
      ]<[
        [[<<]-[>>]<+<-]>[-<+]<<[<<]-<[>[+>>]>[>]>[-]]
        >[[+>>]<-->>[>]+>>>]
      ]<[
        -[
          --[+<<<<--[+>[-]>[<<+>+>-]<<[>>+<<-]]++[>]]
          <<[>+>+<<-]>--[<+>-]++>>>
        ]<[<<<[-]+++>[-]>[<+>>>+<<-]+>>>]
      ]<[
        +[[<]<<[<<]-<->>+>[>>]>[>]<-]+[-<+]<++[[>+<-]++<[<<->>+]<++]<
        <<<<<<      +> > >+> > >+[
        <<<               ->+>+>+[
        <<<<<<<   +>->+> > >->->+[
        <<<<<         ->+>+> >+>+[
        <<<<            ->->+>->+[
        <<<<<<<<+>-> >+> > >->+>+[
        <<<<<         -> >+> >->+[
        <<<<            +>->+> >+]]]]]]]
        +++[[>+<-]<+++]--->>[-[<->-]<++>>]++[[<->-]>>]>[>]
      ]<
    ]
  ]<
]

JOGO DA VELHA
*/
