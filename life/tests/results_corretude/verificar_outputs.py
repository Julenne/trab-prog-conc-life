import json
import sys

# Verifica se o arquivo JSON foi passado como argumento
if len(sys.argv) < 2:
    print("Uso: python3 verificar_outputs.py results.json")
    sys.exit(1)

json_file = sys.argv[1]

# Abrir e ler o JSON
with open(json_file, 'r', encoding='utf-8') as f:
    data = json.load(f)

# Inicializa contadores
total = 0
iguais = 0

# Itera pelos testes
for test in data.get("tests", []):
    total += 1
    seq = test.get("sequencial_output", "")
    conc = test.get("concorrente_output", "")
    if seq == conc:
        print(f"[OK] {test.get('input')} → Saídas iguais")
        iguais += 1
    else:
        print(f"[ERRO] {test.get('input')} → Saídas diferentes")
        # Opcional: mostrar a diferença
        print("Sequencial:", repr(seq))
        print("Concorrente:", repr(conc))
        print()

print(f"\nTotal de testes: {total}")
print(f"Testes com saídas iguais: {iguais}")
print(f"Testes com saídas diferentes: {total - iguais}")
