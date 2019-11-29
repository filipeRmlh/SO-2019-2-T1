# Trabalho 1 de Sistemas operacionais - 2019.2

Aluno: Filipe Ramalho  
Professora: Silvana

## Instruções
### Requisitos:
* cmake versão 3.13 ou maior;
* g++

### Compilar:
Supondo que você está com a raiz do projeto aberta no terminal, execute os comandos abaixo:

```bash
cmake --clean .
cmake --build .
```
### Rodar:
Rode o arquivo binário gerado `SO_2019_2_T1` passando como parâmetro o numero de quadros e redirecionando a entrada padrão para ser o arquivo com a sequência de referência de páginas:
```bash
./SO_2019_2_T1 4 < path/para/seu/arquivo/de/referências/de/página
```
