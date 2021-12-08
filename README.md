### Analisadores Léxico e Sintático Para Calculadora Avançada
#### Implementação parcial de um compilador que reconhece expressões mátematicas
###### desenvolvido para ser apresentado como trabalho final à disciplina de Compiladores (2021.2)

#### Documentação:
A descrição e definições do projeto estão disponíveis em [docs/](https://github.com/v-manoel/calc-compiler/tree/main/docs)


#### Para Executar o programa:
  - Utilaze o qmake para gerar um novo makefile:
    ``` 
    qmake -o Makefile 
    ```
  - Use make para executar o Makefile e compilar o programa
    ``` 
    make 
    ```
  - Acesse a pasta do binario e execute o arquivo passando como parametros os arquivos de entrada e saída, com seus respectivos caminhos relativos. (o segundo parametro é opcional)
    ```
    cd src/bin
    ./fjrv_compiler ../../input.frjv ../../output.tkn
    ```

O arquivo de entrada deve conter a extensão **.frjv**, enquanto o de saída, se informado, deve conter a extensão **.tkn**.

No arquivo de saída, são escritos todos os tokens reconhecidos pelo analisador léxico. Este arquivo é utilizado pelo analisador sintático para a validação da sintaxe do programa fonte (expressão matématica), presente no arquivo **.frjv** informado.


### Sobre os autores:
Projeto desenvolvido por: 
- [Jéssica Cardoso](https://github.com/jessicacardoso1)
- [Filipe Silva](https://github.com/fsilva-c)
- [Reinilson Bispo](https://github.com/rey4ssis)
- [Vitor Manoel](https://github.com/v-manoel)

