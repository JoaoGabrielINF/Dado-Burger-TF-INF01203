# Dado-Burger---TF-INF01203
O projeto se trata do trabalho final da disciplina de Estrutura de Dados (INF01203 - UFRGS), sendo ele um jogo programado em C utilizando como interface gráfica a Raylib, implementando estruturas de dados clássicas como filas, pilhas, heap, listas e algoritmos de ordenação.

## Como compilar e rodar (Windows)

> **Atenção ao prefixo do terminal!** `build.bat` "seco" só funciona no Prompt de Comando (cmd). No PowerShell use `.\build.bat` e no Git Bash `./build.bat`.

1. **Uma única vez** — configure a toolchain portátil (raylib 6.2 + gcc/make, ~70 MB, sem instalação nem admin):
   ```
   cmd:      tools\setup_tools.bat
   PS:       .\tools\setup_tools.bat
   Git Bash: ./tools/setup_tools.bat
   ```
2. **Compilar:** `build.bat` (com o prefixo do seu terminal). Gera `dado_burger.exe` na raiz.
3. **Rodar:** `build.bat run` ou execute `dado_burger.exe` na **raiz do projeto** (assets são carregados por caminho relativo).

Não apague nem limpe a pasta `tools\` — ela contém o compilador e a raylib do projeto.

## Símbolos dos mapas (`dados/*.txt`)

| Símbolo | Significado | Colisão com o jogador |
|---------|-------------|----------------------|
| `#`     | parede / bloqueado | tile inteiro (40×40) |
| `M`     | mesa               | **só a faixa superior** (`ALTURA_COLISAO_MESA`, 20px) — o jogador pode sobrepor a frente da mesa |
| `V`     | mesa lateral (balcão vertical) | **só a faixa esquerda** (20px) do tile |
| `N`     | parede baixa vista de cima | **só uma faixa fina no rodapé** do tile (8px) — o jogador para na borda do desenho |
| `.`     | piso livre         | nenhuma |
| `j`     | spawn do jogador   | nenhuma |
| `l`     | spawn do cliente   | nenhuma |
| `f`     | fogão              | nenhuma (a fazer no gameplay) |
| `c`     | bancada            | nenhuma (a fazer no gameplay) |
| `u`     | tábua              | nenhuma (a fazer no gameplay) |

As constantes ficam em `src/core/constants.h`; a lógica de colisão em `src/gameplay/jogador.c` (`regiao_solida_tile`).
