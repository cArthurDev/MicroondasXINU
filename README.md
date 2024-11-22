# Simulador de Micro-ondas no Xinu

Este projeto implementa um simulador funcional de micro-ondas no sistema operacional **Xinu**. Ele utiliza recursos básicos do Xinu, como gerenciamento de processos e funções de temporização, para simular ciclos de aquecimento, exibir a hora atual no fuso horário de Brasília e gerenciar funcionalidades essenciais do micro-ondas.

## Funcionalidades

- **Configuração de Ciclos de Cozimento**: Permite definir o tipo de alimento, potência (0-100%) e duração em segundos.
- **Execução de Ciclos de Cozimento**: Simula o aquecimento do alimento, com um **beep** ao término do processo.
- **Exibição da Hora Atual (Horário de Brasília)**: Mostra a hora baseada no fuso horário de Brasília.
- **Menu Interativo**: Apresenta opções para configurar, executar ciclos e exibir o horário.

---

## Como Funciona

### Estruturas Principais

1. **CookingCycle**: Representa um ciclo de cozimento.
   - Nível de potência (`power_level`).
   - Duração (`duration`).
   - Tipo de alimento (`food_type`).

2. **Light**: Gerencia o estado da luz interna.
   - Ligada (`is_on = true`).
   - Desligada (`is_on = false`).

### Fluxo do Programa

1. O programa exibe um menu interativo.
2. O usuário escolhe uma das opções:
   - Configurar um ciclo de cozimento.
   - Executar o ciclo configurado.
   - Exibir o horário de Brasília.
3. As funções simulam o comportamento do micro-ondas com base na escolha do usuário.

---

## Exemplo de Uso

### Menu Interativo

Ao iniciar o programa, o seguinte menu será exibido:

--- Menu de Funções ---

Configurar Ciclo de Cozimento
Executar Ciclo de Cozimento
Exibir Hora Atual (Brasília)
Sair Escolha uma opção:

### Teste Prático

1. Escolha a opção `1` para configurar um ciclo:
   - Digite o tipo de alimento, por exemplo, `Frango`.
   - Defina a potência, por exemplo, `80`.
   - Defina a duração, por exemplo, `10 segundos`.

2. Escolha a opção `2` para executar o ciclo configurado:
   - O programa simulará o cozimento, exibindo uma barra de progresso e emitindo um beep ao final.

3. Escolha a opção `3` para exibir a hora atual de Brasília.

4. Escolha `0` para sair.

---

## Estrutura do Código

- **microondas.c**: Contém todas as funções principais e o menu interativo.
- **Funções Principais**:
  - `initialize_cooking_cycle()`: Configura o ciclo de cozimento.
  - `execute_cooking_cycle()`: Simula a execução do ciclo.
  - `display_brasilia_time()`: Exibe a hora de Brasília.
  - `display_menu()`: Exibe o menu interativo.
  - `main()`: Gerencia o fluxo principal do programa.

---

## Licença

Este projeto é licenciado sob a [MIT License](LICENSE).
