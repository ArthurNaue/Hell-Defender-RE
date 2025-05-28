# 🎮 Hell Defender RE

Projeto retrabalhado do jogo Hell Defender, feito em C usando a [Raylib](https://www.raylib.com/).

## 📁 Estrutura do Projeto

```
Hell-Defender-RE/
├── assets/             # Recursos do jogo (texturas, sons, etc)
├── include/            # Headers (.h)
├── src/                # Código-fonte principal (.c)
├── libraries/
│   └── raylib/         # Raylib como subdiretório (local)
├── CMakeLists.txt      # Script de build com CMake
└── README.md           # Este arquivo
```

## 🧩 Pré-requisitos

Certifique-se de ter os seguintes pacotes instalados:

### 🐧 Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install build-essential cmake libasound2-dev libpulse-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev libgl1-mesa-dev
```

### 🍎 macOS

```bash
brew install cmake
```

### 🪟 Windows

```bash
- Instale:
  - [MinGW-w64](https://www.mingw-w64.org/) ou MSYS2
  - [CMake](https://cmake.org/download/)
- Adicione o compilador ao PATH
```

## 🚀 Como clonar o projeto corretamente

Esse repositório usa a **Raylib como submódulo Git**, então você deve clonar com a flag `--recursive`:

```bash
git clone --recursive https://github.com/ArthurNaue/Hell-Defender-RE.git
cd Hell-Defender-RE
```

Se você já clonou sem `--recursive`, execute:

```bash
git submodule update --init --recursive
```

## 🛠️ Como compilar

### 🔧 Usando CMake no terminal:

```bash
mkdir build
cd build
cmake ..
make
```

## 🎮 Como rodar o jogo

Após compilar, dentro da pasta `build`, execute:

```bash
./HellDefender
```

No Windows, o executável será `HellDefender.exe`.

## 📝 Observações

- A pasta `assets/` será copiada automaticamente para o diretório do executável.
- O projeto foi configurado para **usar a Raylib localmente**, então **não é necessário instalar a Raylib separadamente**.

## 👨‍💻 Autor

Arthur Naue  
[GitHub](https://github.com/ArthurNaue)
