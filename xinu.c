#include <xinu.h>
#include <stdio.h>
#include <string.h>

struct CookingCycle {
    int power_level;
    int duration;
    char food_type[20];
};

struct Light {
    bool is_on;
};

void initialize_cooking_cycle(struct CookingCycle *cycle, int power, int time, const char *type) {
    cycle->power_level = power;
    cycle->duration = time;
    snprintf(cycle->food_type, sizeof(cycle->food_type), "%s", type);
    kprintf("Ciclo configurado: %s - Potência %d%% por %d segundos.\n", type, power, time);
}

void execute_cooking_cycle(struct CookingCycle *cycle) {
    kprintf("\nIniciando ciclo de cozimento...\n");
    kprintf("Aquecendo %s a %d%% de potência por %d segundos...\n", cycle->food_type, cycle->power_level, cycle->duration);
    for (int i = 0; i < cycle->duration; i++) {
        kprintf("Cozinhando... [%d/%d]\n", i + 1, cycle->duration);
        sleep(1);
    }
    kprintf("Beep! Cozimento concluído para %s.\n", cycle->food_type);
}

void display_brasilia_time() {
    time_t now = clktime;
    struct tm timeinfo;
    localtime_r(&now, &timeinfo);
    kprintf("Hora atual em Brasília: %02d:%02d\n", timeinfo.tm_hour, timeinfo.tm_min);
}

void display_menu() {
    kprintf("\n--- Menu de Funções ---\n");
    kprintf("1. Configurar Ciclo de Cozimento\n");
    kprintf("2. Executar Ciclo de Cozimento\n");
    kprintf("3. Exibir Hora Atual\n");
    kprintf("0. Sair\n");
    kprintf("Escolha uma opção: ");
}

process main(void) {
    struct CookingCycle cycle = {0, 0, ""};
    struct Light light = {false};
    int option;
    do {
        display_menu();
        scanf("%d", &option);
        switch (option) {
            case 1: {
                int power, time;
                char food[20];
                kprintf("Digite o tipo de alimento (ex. Frango): ");
                scanf("%s", food);
                kprintf("Digite o nível de potência (0-100): ");
                scanf("%d", &power);
                kprintf("Digite a duração em segundos: ");
                scanf("%d", &time);
                initialize_cooking_cycle(&cycle, power, time, food);
                break;
            }
            case 2:
                if (strlen(cycle.food_type) == 0) {
                    kprintf("Erro: Nenhum ciclo configurado! Configure primeiro.\n");
                } else {
                    execute_cooking_cycle(&cycle);
                }
                break;
            case 3:
                display_brasilia_time();
                break;
            case 0:
                kprintf("Encerrando...\n");
                break;
            default:
                kprintf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (option != 0);
    return OK;
}
