# trab-prog-conc-life

### Para rodar:

```
$make
$./life < ../tests/life.in
```

Existem 2 arquivos Makefile na pasata \life para rodar os testes de desempenho, basta renomear para Makefile, e irá rodar tanto os códigos concorrentes quanto os sequenciais. Lembre-se, só pode ter um Makefile por pasta.

Após isso basta rodar o comando no terminal, ainda na pasta \life:
```
$make run
```
Para avaliar a corretude basta rodar o script verificar_outputs.py com o seguinte comando na pasta \tests\results_corretude:
```
$ python verificar_outputs.py results_{steps}_{threads}.json