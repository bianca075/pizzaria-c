# 🍕 Pizzada Certa — Sistema de Gerenciamento de Pizzaria em C

Um sistema completo em **linguagem C** para gerenciamento de pizzaria via terminal, com cadastro, consulta e exclusão de clientes, validação de CPF, realização de pedidos e gravação em arquivos.  
Feito para fins acadêmicos e de aprendizado em programação estruturada.

#

## Funcionalidades

- **Cadastro de clientes** com validação de CPF e verificação de duplicidade.  
- **Consulta** e **listagem** de clientes por ordem alfabética ou numérica.  
- **Desativação e exclusão** de clientes com atualização automática dos arquivos.  
- **Realização de pedidos**, incluindo escolha de sabor, tamanho e quantidade.  
- **Gravação em arquivos (`clientes.txt` e `pedidos.txt`)**, garantindo persistência de dados.  
- **Ordenação e busca binária** para consultas rápidas.  
- **Interface textual** com arte ASCII temática e menus interativos.

#

## Estrutura do Projeto
├── projeto.c # Arquivo principal (menu e lógica central)
├── pizza.c # Tela inicial com arte ASCII e inicialização
├── pizza.h # Cabeçalho com definição da função pizza()
├── instruções.txt # Instruções básicas de compilação e execução
├── clientes.txt # Gerado automaticamente - dados de clientes
├── pedidos.txt # Gerado automaticamente - dados de pedidos


#

## Tecnologias Utilizadas

- Linguagem **C (ANSI C)**
- Bibliotecas padrão:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `stdbool.h`
  - `ctype.h`
  - `locale.h`
- Compilador: **GCC**

#

## Como Compilar e Executar

1. Abra o terminal no diretório do projeto.  
2. Compile o programa:
   ```bash
   gcc projeto.c pizza.c -o pizza
3. Execute o programa:
  ./pizza.exe   # ou ./pizza no Linux
4. Divirta-se com o sistema da pizzaria! 🍕

#

## Estrutura Lógica

  main(): controla o menu principal.
  Cadastro e validação: funções de leitura, escrita e verificação de CPF.
  Pedidos: cálculo de total e gravação no arquivo pedidos.txt.
  QuickSort e busca binária: ordenação e consulta eficiente de clientes.

#

##  Arquivos Gerados

  clientes.txt → armazena dados dos clientes cadastrados.
  pedidos.txt → guarda o histórico de pedidos realizados.
  
Ambos são atualizados automaticamente a cada ação no sistema.


