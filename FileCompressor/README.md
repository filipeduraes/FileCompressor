# Trabalho 02

Instruções para compilar e executar o projeto.

**Nota:** Estamos usando features da versão 17 do C++, então tenha certeza de que está com essa versão ou uma superior instalada.

---

## Pré-requisitos

Antes de compilar o projeto, certifique-se de ter as seguintes ferramentas instaladas:

- **CMake**
- **Compilador C++**:
  - Windows: [Visual Studio](https://visualstudio.microsoft.com/) (com suporte a C++) ou [MinGW](http://www.mingw.org/)
  - Linux: `g++` ou `clang`

### Instalando as Ferramentas

#### Windows

1. **CMake**: Baixe e instale o executável do CMake a partir do link https://cmake.org/download/ e adicione-o ao PATH.
2. **Compilador**: Instale o [Visual Studio](https://visualstudio.microsoft.com/) com as workloads para C++ ou [MinGW](http://www.mingw.org/) e adicione-o ao PATH.

#### Linux

1. Instale o CMake e o pacote de build-essential, que inclui o compilador e o make, usando o gerenciador de pacotes:
    ```bash
    sudo apt update
    sudo apt install cmake build-essential
    ```
    ou, para usar o `g++` como compilador:
    ```bash
    sudo apt install cmake make g++
    ```
    ou, para usar o `clang` como compilador:
    ```bash
    sudo apt install cmake make clang
    ```

---

## Compilando o Projeto

Uma vez que as ferramentas estejam instaladas, siga as instruções abaixo para compilar o projeto.

### Passo 1: Abra o diretório do projeto na linha de comando

```bash
cd FileCompressor
```

### Passo 2: Crie o Diretório de Build

No diretório do projeto, crie um diretório para armazenar os arquivos de build:
```bash
mkdir build
cd build
```

### Passo 3: Configure o Build com o CMake

Configure o CMake com o seguinte comando:
```bash
cmake ..
```

### Passo 4: Compile o Projeto

Após configurar o CMake, compile o projeto com o seguinte comando:
```bash
cmake --build .
```
Ele irá gerar um arquivo executável dentro da pasta de build.

### Passo 5: Execute o programa

#### Windows
Após a compilação, será mostrado o path onde foi gerado o arquivo executável. Atualize o comando para o caminho mostrado caso diferente.
```bash
.\Debug\SearchMethodsComparison.exe
```

#### Linux
Após a compilação, será mostrado o path onde foi gerado o arquivo executável. Atualize o comando para o caminho mostrado caso diferente.
```bash
./FileCompressor
```

## Dicas para Resolução de Problemas

- Certifique-se de que todas as ferramentas (CMake, compilador) estejam no PATH do sistema.
- Verifique se as versões do CMake e do compilador são compatíveis com o projeto.
- No Windows, se você estiver usando o Visual Studio, lembre-se de abrir o terminal "Developer Command Prompt" para garantir que os comandos do compilador estejam disponíveis.
