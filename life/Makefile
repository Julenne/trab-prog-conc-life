# Makefile de corretude na pasta "life"

# Diretórios
CONC_DIR = concorrente
SEQ_DIR  = sequencial
TEST_DIR = tests

# Executáveis
CONC_BIN = $(CONC_DIR)/life-conc
SEQ_BIN  = $(SEQ_DIR)/life-seq

# Compilador e flags
CC = gcc
CFLAGS = -O3

# Lista de testes
TESTS = $(wildcard $(TEST_DIR)/board_*.in)

# Arquivo de log/resultados
RESULTS = $(TEST_DIR)/results.txt

# Alvo padrão
all: $(CONC_BIN) $(SEQ_BIN)

# Compilar versão concorrente
$(CONC_BIN): $(CONC_DIR)/life-conc.c $(CONC_DIR)/timer.h
	$(CC) $(CFLAGS) -o $@ $<

# Compilar versão sequencial
$(SEQ_BIN): $(SEQ_DIR)/life-seq.c $(SEQ_DIR)/timer.h
	$(CC) $(CFLAGS) -o $@ $<

# Executar ambos para cada teste e salvar em RESULTS (com eco no console)
run: all
	@{ \
		echo "============================================"; \
		echo "     JOGO DA VIDA — TESTES AUTOMATIZADOS"; \
		echo "============================================"; \
		for test in $(TESTS); do \
			echo ""; \
			echo ">>> Executando com $$test"; \
			echo "---- SEQUENCIAL ----"; \
			$(SEQ_BIN) < $$test; \
			echo "---- CONCORRENTE ----"; \
			$(CONC_BIN) < $$test; \
		done; \
	} 2>&1 | tee $(RESULTS)

# Limpeza
clean:
	rm -f $(CONC_BIN) $(SEQ_BIN) $(RESULTS)
	find . -name "*.o" -delete
