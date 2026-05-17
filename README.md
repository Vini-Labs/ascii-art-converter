# ascii-art-converter

converte imagens em arte ascii no terminal — suporta png, jpg e bmp.

```
@@@@@@@@@##SSS%%%???***+++;;;:::,,,... 
@@@@@@##SS%%%???***+++;;;:::,,,......  
@@@##SS%%???***+++;;;:::,,,......      
```

---

## Dependências

este projeto usa [stb_image](https://github.com/nothings/stb) — uma biblioteca de carregamento de imagens em arquivo único. é necessário baixá-la manualmente antes de compilar:

```bash
curl -o include/stb_image.h https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
```

ou acesse o link acima pelo navegador e salve o arquivo na pasta `include/`.

---

## Compilando

```bash
make
```

para limpar os arquivos gerados:

```bash
make clean
```

---

## Uso

```bash
./ascii <imagem> [opções]
```

### Opções

| flag | descrição | padrão |
|------|-----------|--------|
| `-w <largura>` | largura da saída em caracteres | 100 |
| `-o <arquivo>` | salva a saída em um arquivo `.txt` | — |
| `-h` | exibe a ajuda | — |

### Exemplos

```bash
# exibir no terminal
./ascii foto.jpg

# largura personalizada
./ascii foto.jpg -w 120

# salvar em arquivo
./ascii foto.jpg -o resultado.txt

# ambos
./ascii foto.jpg -w 80 -o resultado.txt
```

> **atenção:** o programa procura a imagem a partir da pasta onde o comando é executado. use o caminho completo ou copie a imagem para a pasta do projeto antes de rodar.

```bash
# usando caminho completo
./ascii /home/usuario/Downloads/foto.jpg

# ou copiando a imagem para a pasta do projeto
cp /home/usuario/Downloads/foto.jpg .
./ascii foto.jpg
```

---

## Estrutura do projeto

```
ascii-art-converter/
├── include/
│   ├── stb_image.h   ← baixar manualmente (veja acima)
│   ├── image.h
│   ├── gray.h
│   ├── ascii.h
│   └── output.h
├── src/
│   ├── main.c        ← ponto de entrada, leitura de argumentos
│   ├── image.c       ← carrega a imagem do disco
│   ├── gray.c        ← converte pixels rgb em brilho
│   ├── ascii.c       ← mapeia brilho em caracteres ascii
│   └── output.c      ← exibe no terminal e salva em arquivo
└── Makefile
```

---

## Como funciona

1. **carregamento** — lê o arquivo de imagem e extrai os pixels rgb brutos usando `stb_image`
2. **escala de cinza** — converte cada pixel em um valor de brilho (0–255) usando a fórmula de luminância: `0.299r + 0.587g + 0.114b`
3. **mapeamento** — mapeia cada valor de brilho para um caractere de `@#S%?*+;:,. ` (escuro para claro)
4. **saída** — exibe o resultado no terminal e opcionalmente salva em arquivo `.txt`

---

## Requisitos

- gcc
- make
- linux / macos