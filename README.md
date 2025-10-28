# Simulação de RPC

## Requisitos:

- CMake 3.16 ou superior
- ROOT 6
- Geant4-11

## Como executar

1. Criar pasta para compilação:
```bash
cd SimulacaoRPC
mkdir build
cd build
```

2. Compilar
```bash
cmake ..
make -j4
```
Obs.: `-j4` é opcional, para compilar em paralelo.

3. Executar
```bash
./SimulacaoRPC
```
para visualização ou
```bash
./SimulacaoRPC run.mac
```
para execução sem visualização.

4. Analizar
```bash
root output0.root
```
e no terminal do ROOT
```root
[1] new TBrowser
[2] Hits->Draw("fX:fY", "", "colz")
[3] .q
```