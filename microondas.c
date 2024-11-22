#include <xinu.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int power_level;
    int duration;
    char food_type[20];
} CookingCycle;

typedef struct {
    bool light_on;
} InternalLight;

void specify_cycle(CookingCycle *cycle, const char *food, int power, int time) {
    cycle->power_level = power;
    cycle->duration = time;
    snprintf(cycle->food_type, sizeof(cycle->food_type), "%s", food);
    kprintf("Ciclo configurado: %s - Potência %d%% por %d segundos.\n", food, power, time);
}

void control_klystron(int power) {
    kprintf("Klystron operando a %d%% de potência.\n", power);
}

void announce_beep() {
    kprintf("Beep! Cozimento concluído.\n");
}

void emergency_stop() {
    kprintf("Parada de emergência ativada! Ciclo cancelado e porta destravada.\n");
}

void schedule_future_action(CookingCycle *cycle, int delay) {
    kprintf("Ciclo será iniciado em %d segundos...\n", delay);
    sleep(delay);
    start_cycle(cycle);
}

void cooling() {
    kprintf("Resfriamento em andamento...\n");
    sleep(2);
    kprintf("Resfriamento concluído.\n");
}

void rotate_plate() {
    kprintf("Prato girando para distribuição uniforme de calor.\n");
}

void light_during_cooking(InternalLight *light, bool state) {
    light->light_on = state;
    kprintf("Luz interna %s.\n", light->light_on ? "ligada" : "desligada");
}

void display_clock() {
    time_t agora = clktime;
    struct tm horario;
    localtime_r(&agora, &horario);
    kprintf("Hora atual em Brasília: %02d:%02d\n", horario.tm_hour, horario.tm_min);
}

void cooking_programs_menu(CookingCycle *cycle) {
    int choice;
    kprintf("\n--- Programas de Cozimento ---\n");
    kprintf("1. Carnes (80%%, 10 minutos)\n");
    kprintf("2. Peixe (70%%, 8 minutos)\n");
    kprintf("3. Frango (90%%, 12 minutos)\n");
    kprintf("4. Lasanha (60%%, 15 minutos)\n");
    kprintf("5. Pipoca (100%%, 3 minutos)\n");
    kprintf("Escolha uma opção: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            specify_cycle(cycle, "Carnes", 80, 600);
            break;
        case 2:
            specify_cycle(cycle, "Peixe", 70, 480);
            break;
        case 3:
            specify_cycle(cycle, "Frango", 90, 720);
            break;
        case 4:
            specify_cycle(cycle, "Lasanha", 60, 900);
            break;
        case 5:
            specify_cycle(cycle, "Pipoca", 100, 180);
            break;
        default:
            kprintf("Opção inválida!\n");
            break;
    }
}

void display_menu() {
    kprintf("\n--- Menu de Funções ---\n");
    kprintf("1. Configurar Ciclo de Cozimento\n");
    kprintf("2. Iniciar Ciclo de Cozimento\n");
    kprintf("3. Programas de Cozimento\n");
    kprintf("4. Programar Ação Futura\n");
    kprintf("5. Parada de Emergência\n");
    kprintf("6. Luz Interna Durante Preparo\n");
    kprintf("7. Resfriamento\n");
    kprintf("8. Tração do Prato\n");
    kprintf("9. Exibir Relógio Cortesia\n");
    kprintf("0. Sair\n");
    kprintf("Escolha uma opção: ");
}

void start_cycle(const CookingCycle *cycle) {
    if (strlen(cycle->food_type) == 0) {
        kprintf("Erro: Nenhum ciclo configurado! Configure primeiro.\n");
        return;
    }

    kprintf("\nIniciando ciclo de cozimento...\n");
    kprintf("Aquecendo %s a %d%% de potência por %d segundos...\n", 
            cycle->food_type, cycle->power_level, cycle->duration);

    for (int i = 0; i < cycle->duration; i++) {
        kprintf("Cozinhando... [%d/%d]\n", i + 1, cycle->duration);
        sleep(1);
    }

    announce_beep();
}

void process_option(int option, CookingCycle *cycle, InternalLight *light) {
    switch (option) {
        case 1:
            specify_cycle(cycle, "Personalizado", 0, 0);
            break;
        case 2:
            start_cycle(cycle);
            break;
        case 3:
            cooking_programs_menu(cycle);
            break;
        case 4: {
            int delay;
            kprintf("Digite o tempo em segundos para iniciar o ciclo: ");
            scanf("%d", &delay);
            schedule_future_action(cycle, delay);
            break;
        }
        case 5:
            emergency_stop();
            break;
        case 6: {
            int state;
            kprintf("Deseja ligar a luz interna? (1 = Sim, 0 = Não): ");
            scanf("%d", &state);
            light_during_cooking(light, state == 1);
            break;
        }
        case 7:
            cooling();
            break;
        case 8:
            rotate_plate();
            break;
        case 9:
            display_clock();
            break;
        case 0:
            kprintf("Encerrando...\n");
            break;
        default:
            kprintf("Opção inválida! Tente novamente.\n");
            break;
    }
}

process main(void) {
    CookingCycle cycle = {0, 0, ""};
    InternalLight light = {false};
    int option;

    do {
        display_menu();
        scanf("%d", &option);
        process_option(option, &cycle, &light);
    } while (option != 0);

    return OK;
}
