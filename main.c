#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

struct P{
    int numero;
    char name[20];
    float exp;
    int level;
    int hp;
    int attack;
    int defense;
    int velocidade;
    float dmgMultiplier;
    struct  P *prox;
};
// FUNCOES E PROCEDIMENTOS
typedef struct P pokemon;
void inicial(pokemon* CAPTURADOS);
void mostrarPokemons(pokemon *CAPTURADOS);
void menu();
void treinar(pokemon *CAPTURADOS);
void clearScreen();
void soltarTodos(pokemon *CAPTURADOS);
int batalha(pokemon *CAPTURADOS);
char* choose_random_name();
float gerarEXP(float min, float max);
int gerarBase();

// VARIVAVEL(IS) GOBAL(IS)

const char* FILE_PATH = "nomes.txt";
int cont=0;
#define MAX 6
#define MAX_NAME_LENGTH 30

// Damage = (((2 * Level / 5 + 2) * AttackStat * MovePower / DefenseStat) / 50 + 2) * Modifier
int main()
{
    pokemon *CAPTURADOS = malloc(sizeof(pokemon));
    int mainMenuOption = 0;
    int gameMenuOption = 0;
    int gameStarted = 0;

    while (1) {
        printf("Menu Inicial\n");
        printf("1. Novo Jogo\n");
        printf("2. Sair\n");
        printf("Enter your choice: ");
        scanf("%d", &mainMenuOption);

        switch (mainMenuOption) {
            case 1:
                CAPTURADOS->prox=NULL;
                gameStarted = 1;
                while (gameStarted) {
                    menu();
                    scanf("%d", &gameMenuOption);

                    switch (gameMenuOption) {
                        case 1:
                            inicial(CAPTURADOS);
                            break;
                        case 2:
                            mostrarPokemons(CAPTURADOS);
                            getch();
                            break;
                        case 3:
                            treinar(CAPTURADOS);
                            break;
                        case 4:
                            gameStarted = 0;
                            soltarTodos(CAPTURADOS);
                            exit(0);
                            break;
                        case 5:
                            printf("%s",choose_random_name());
                            getch();
                            break;
                        default:
                            printf("Invalid choice in Game Menu.\n");
                            break;
                    }
                }
                break;
            case 2:
                printf("Leaving the program...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice in Main Menu.\n");
                break;
        }
    }
    getch();
    return 0;
}

// FUNCOES E PROCEDIMENTOS

// GERADOR DE POKEMON
void inicial(pokemon* CAPTURADOS)
{
    clearScreen();
    pokemon *tmp;
    pokemon *novo = (pokemon *)malloc(sizeof(pokemon));
    if (!novo)
    {
        printf("Xiiii que pc fraco nem tens RAM");
        exit(1);
    }
    if(cont < MAX)
    {
        cont++;
        novo->prox=NULL;
        novo->numero=cont;
        printf("Que nome queres dar ao pokemon: ");
        fflush(stdin);
        gets(novo->name);
        if(strlen(novo->name) == 0)
        {
            strcpy(novo->name, choose_random_name());
        }
        novo->exp=gerarEXP(1000, 4000);
        novo->level=(int)novo->exp/1000;
        novo->hp=novo->level*4;
        novo->attack = gerarBase();
        novo->defense = gerarBase();
        novo->velocidade = gerarBase();
        novo->dmgMultiplier=1.0;
    }
    else
    {
        printf("Ja atingiste o maximo de pokemons possiveis");
        return;
    }
    tmp=CAPTURADOS;
    while (tmp->prox!=NULL)
    {
        tmp=tmp->prox;
    }
    tmp->prox=novo;

}

// MOSTRA OS POKEMONS CAPTURADOS
void mostrarPokemons(pokemon *CAPTURADOS)
{
    pokemon *tmp;
    tmp = CAPTURADOS;
    setlocale(LC_ALL, "Portuguese");
    clearScreen();
    printf("*********************************\n");
    printf("*          Pokemon Info         *\n");
    printf("*********************************\n");


    while (tmp->prox!=NULL)
    {
        tmp = tmp->prox;
        printf("*  Number: %-20d *\n", tmp->numero);
        printf("*  Name: %-20s   *\n", tmp->name);
        printf("*  Level: %-20d  *\n", tmp->level);
        printf("*  HP: %-20d     *\n", tmp->hp);
        printf("*  Attack: %-20d *\n", tmp->attack);
        printf("*  Defense: %-20d*\n", tmp->defense);
        printf("*  Velocity: %-19d*\n", tmp->velocidade);
        printf("*  Dmg Multiplier: %-13.2f*\n", tmp->dmgMultiplier);
        printf("*********************************\n");
    }


}

// MENU
void menu()
{
    clearScreen();
    printf("*************************\n");
    printf("*          MENU         *\n");
    printf("*************************\n");
    printf("* 1. Cadastrar Pokemon  *\n");
    printf("* 2. Mostrar Pokemons   *\n");
    printf("* 3. Treinar            *\n");
    printf("* 4. Sair               *\n");
    printf("*************************\n");

}

//TREINAR UM POKEMON
void treinar(pokemon *CAPTURADOS) {
    pokemon *tmp = CAPTURADOS->prox;
    int n;
    int sorte[10] = {12, 21, 32, 43, 52, 66, 67, 78, 89, 95};
    int maxAttempts = 5;
    int attemptCount = 0;
    time_t sucesso;
    srand((unsigned)time(&sucesso));
    sucesso = rand() % 101;

    mostrarPokemons(CAPTURADOS);
    printf("Qual pokemon desejas treinar: ");
    scanf("%d", &n);

    while (tmp->numero != n) {
        tmp = tmp->prox;
        if (tmp == NULL) {
            printf("Pokemon não encontrado.\n");
            getch();
            return;
        }
    }

    printf("A treinar\n");
    printf("*********************************\n");
    printf("*  Number: %-20d *\n", tmp->numero);
    printf("*  Name: %-20s   *\n", tmp->name);
    printf("*  Level: %-20d  *\n", tmp->level);
    printf("*  HP: %-20d     *\n", tmp->hp);
    printf("*  Defense: %-20d*\n", tmp->defense);
    printf("*  Dmg Multiplier: %-13.2f*\n", tmp->dmgMultiplier);
    printf("*********************************\n");

    while (attemptCount < maxAttempts) {
        printf("%d  ", sucesso);
        for (int i = 0; i < 10; i++) {
            if (sucesso == sorte[i]) {
                tmp->dmgMultiplier += 0.1;
                printf("\nO treino foi um sucesso! Agora %s tem um dano multiplicado de %.2f\n", tmp->name, tmp->dmgMultiplier);
                getch();
                return;
            }
        }
        attemptCount++;
        sucesso = rand() % 101;
    }

    printf("\nO treino não teve sucesso após %d tentativas.\n", maxAttempts);
    getch();
}


// SOLTAR TODOS OS POKEMONS
void soltarTodos(pokemon *CAPTURADOS) {
    pokemon *current = CAPTURADOS->prox;

    while (current != NULL) {
        CAPTURADOS->prox = current->prox;
        free(current);
        current = CAPTURADOS->prox;
    }
    printf("Todos os pokmons foram soltos de volta a natureza");
}

int batalha(pokemon *CAPTURADOS)
{
    int n;
    pokemon *adversario = (pokemon *)malloc(sizeof(pokemon));
    if(!adversario)
    {
        printf("Sem adversarios nao da");
        return EXIT_FAILURE;
    }
    pokemon *tmp = CAPTURADOS->prox;
    mostrarPokemons(CAPTURADOS);
    printf("Qual pokemon desejas usar na luta: ");
    scanf("%d", &n);

    while (tmp->numero != n) {
        tmp = tmp->prox;
        if (tmp == NULL) {
            printf("Pokemon não encontrado.\n");
            getch();
            return;
        }
    }

    printf("A lutar com\n");
    printf("*********************************\n");
    printf("*  Number: %-20d *\n", tmp->numero);
    printf("*  Name: %-20s   *\n", tmp->name);
    printf("*  Level: %-20d  *\n", tmp->level);
    printf("*  HP: %-20d     *\n", tmp->hp);
    printf("*  Defense: %-20d*\n", tmp->defense);
    printf("*  Dmg Multiplier: %-13.2f*\n", tmp->dmgMultiplier);
    printf("*********************************\n");

    printf("------------- VS -----------------\n");

    printf("*********************************\n");
    printf("*  Name: %-20s   *\n", adversario->name);
    printf("*  Level: %-20d  *\n", adversario->level);
    printf("*  HP: %-20d     *\n", adversario->hp);
    printf("*  Defense: %-20d*\n", adversario->defense);
    printf("*  Dmg Multiplier: %-13.2f*\n", adversario->dmgMultiplier);
    printf("*********************************\n");

    /*tmp->exp+=((1000 * (tmp->level -1 )) / 10)+1000
    tmp->level=(int)novo->exp/1000;*/
    return tmp->numero;
    getch();
}

// ESCOLHER O NOME DO ADVERSARIO
char* choose_random_name() {
    FILE* file;
    char** names = NULL;
    int num_names = 0;
    char line[MAX_NAME_LENGTH];

    // Open the file
    file = fopen(FILE_PATH, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return NULL;
    }

    // Read the names from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character if present

        // Extract the name without the double quotation marks
        char* name = strtok(line, "\"");
        if (name != NULL) {
            num_names++;

            // Allocate memory for names
            names = realloc(names, sizeof(char*) * num_names);
            names[num_names - 1] = malloc(sizeof(char) * (strlen(name) + 1));
            strcpy(names[num_names - 1], name);
        }
    }

    // Close the file
    fclose(file);

    if (num_names == 0) {
        printf("No names found in the file.\n");
        return NULL;
    }

    // Generate a random index
    srand(time(NULL));
    int random_index = rand() % num_names;

    // Create a copy of the randomly chosen name
    char* random_name = malloc(sizeof(char) * (strlen(names[random_index]) + 1));
    strcpy(random_name, names[random_index]);

    // Free allocated memory
    for (int i = 0; i < num_names; i++) {
        free(names[i]);
    }
    free(names);

    return random_name;
}

// GERADOR DE ADVERSARIOS PARA A LUTA
void gerarAdversario(pokemon *CAPTURADOS)
{
    int nivel = rand() % 8;
    nivel-=3;

    pokemon *tmp = CAPTURADOS;
    while(tmp->numero!=batalha(CAPTURADOS))
    {
        tmp=tmp->prox;
    }
    pokemon *adversario = (pokemon *)malloc(sizeof(pokemon));

    if(!adversario)
    {
        printf("O mundo esta pacifico, nao ha adversarios");
        return EXIT_FAILURE;
    }
    adversario->prox=NULL;
    adversario->name=choose_random_name(file_path);
    adversario->level=tmp->level+nivel;
    adversario->hp=adversario->level*4;
    adversario->attack=gerarBase();
    adversario->defense=gerarBase();
    adversario->velocidade=gerarBase();

}


// GERADORES DE XP E/OU OS NUMEROS BASE PARA O ATAQUE/DEFESA/VELOCIDADE POR CADA POKEMON CAPTURADO E/OU ADVERSARIO CRIADO

float gerarEXP(float min, float max) {
    float exp = (float)rand() / RAND_MAX;
    float xpfinal = exp * (max - min) + min;
    return xpfinal;
}

int gerarBase() {
    int base = rand() % (255 - 1 + 1) + 1;
    return base;
}

// NADA QUE PREOCUPAR
void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coordScreen = {0, 0};
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

    SetConsoleCursorPosition(hConsole, coordScreen);
}
