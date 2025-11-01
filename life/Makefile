# Makefile principal na pasta "life"

# Número de repetições para cada teste
REPS = 5

# Diretórios
CONC_DIR = concorrente
SEQ_DIR = sequencial
TEST_DIR = tests

# Executáveis
CONC_BIN = $(CONC_DIR)/life-conc
SEQ_BIN = $(SEQ_DIR)/life-seq

# Compilador e flags
CC = gcc
CFLAGS = -O3

# Lista de testes
TESTS = $(wildcard $(TEST_DIR)/board_*.in)

# Arquivo de resultados
RESULTS = $(TEST_DIR)/resultados.txt

# Alvo padrão
all: $(CONC_BIN) $(SEQ_BIN)

# Compilar versão concorrente
$(CONC_BIN): $(CONC_DIR)/life-conc.c $(CONC_DIR)/timer.h
	$(CC) $(CFLAGS) -o $@ $<

# Compilar versão sequencial
$(SEQ_BIN): $(SEQ_DIR)/life-seq.c $(SEQ_DIR)/timer.h
	$(CC) $(CFLAGS) -o $@ $<

# Executar ambos para cada teste e salvar saída no arquivo
run: all
	@echo "============================================"
	@echo "     JOGO DA VIDA — TESTES AUTOMATIZADOS"
	@echo "============================================"
	@echo "Relatório salvo em: $(RESULTS)"
	@echo "============================================" > $(RESULTS)
	@date >> $(RESULTS)
	@for test in $(TESTS); do \
		for i in $(shell seq 1 $(REPS)); do \
			echo "" | tee -a $(RESULTS); \
			echo ">>> Executando com $$test (Rodada $$i)" | tee -a $(RESULTS); \
			$(SEQ_BIN) < $$test | tee -a $(RESULTS); \
			$(CONC_BIN) < $$test | tee -a $(RESULTS); \
		done; \
		echo "--------------------------------------------" | tee -a $(RESULTS); \
	done
	@echo "" | tee -a $(RESULTS)
	@echo "============================================" | tee -a $(RESULTS)
	@echo "Fim da execução — resultados registrados em segundos." | tee -a $(RESULTS)

# Limpeza
clean:
	rm -f $(CONC_BIN) $(SEQ_BIN) $(RESULTS)
	find . -name "*.o" -delete
