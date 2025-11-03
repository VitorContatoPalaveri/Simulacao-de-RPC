# Simulação de RPC

## Requisitos:

- CMake 3.16 ou superior
- ROOT 6
- Geant4-11

## Como executar

1. Editar configuração em [config.hh](https://github.com/VitorContatoPalaveri/Simulacao-de-RPC/blob/main/SimulacaoRPC/include/config.hh).

2. Criar pasta para compilação:
```bash
cd SimulacaoRPC
mkdir build
cd build
```

3. Compilar (esta etapa precisa ser feita toda vez que uma configuração ou macro for editada):
```bash
cmake ..
make -j4
```
Obs.: `-j4` é opcional, para compilar em paralelo.

4. Executar
```bash
./SimulacaoRPC
```
para visualização ou
```bash
./SimulacaoRPC run.mac
```
para execução sem visualização.

5. Analizar
```bash
root output_0.root
```
e no terminal do ROOT
```root
[1] new TBrowser
[2] Hits->Draw("detY:detX", "nElectrons_ind", "colz");
[3] .q
```
