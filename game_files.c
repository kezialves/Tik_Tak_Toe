// Biblioteca responsável pelos arquivos
// Kézia Alves
// 22.1.4026

#include <stdio.h>
#include <string.h>

#include "game_files.h"
#include "validations.h"
#include "formatting.h"
#include "game_essential.h"
#include "game_interface.h"
#include "structs.h"
#include "game_inteligence.h"
#include "player_vs_player.h"

void continue_saved_game () {

    Game game;
    Player player1, player2;

    // cria e inicializa o tabuleiro
    char board[3][3] = { {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '} };

    char game_file_name[FILE_NAME];
    char c;

    printf ("Digite o nome do arquivo do jogo: ");
    fgets (game_file_name, FILE_NAME, stdin);
    printf ("\n");

    verify_file (game_file_name);

    FILE * file = fopen (game_file_name, "r");

    fscanf (file, "%d", &game.number_of_players);

    fgets (player1.name, PLAYER_NAME, file);
    player1.name[strlen (player1.name) - 1] = '\0';

    if (game.number_of_players == 2) {
        fgets (player2.name, PLAYER_NAME, file);
        player2.name[strlen (player2.name) - 1] = '\0';
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; i < 3; i++) {

            c = fgetc (file);

            if (c == 'X') {
                board[i][j] = 'x';
                game.marked_positions++;
            }

            else if (c == 'O') {
                board[i][j] = 'o';
                game.marked_positions++;
            }

            else if (c == '-') {
                board[i][j] = ' ';
            }

            else {
                i--;
            }
        }
    }

    fclose (file);

    if (game.number_of_players == 1) {
        player_vs_computer (board, game, &player1);
    }

    else {
        player_vs_player (board, game, &player1, &player2);
    }

    printf ("\nDigite qualquer tecla para continuar: ");
    char key[COMMAND_NAME];
    fgets (key, COMMAND_NAME, stdin);

    clear_screen ();
    display_menu ();
    choose_menu (1);
}

void save_game (char file_name[FILE_NAME], char *player1_name, char *player2_name, char board[][3], int last_player) {

    verify_file_name (file_name);

    FILE * file = fopen (file_name, "w+");

    if (!strcmp (player2_name, "Computador")) {
        fprintf (file, "1\n%s\n", player1_name);
    }

    else {
        fprintf (file, "2\n%s\n%s\n", player1_name, player2_name);
    }

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3; j++) {

            if (board[i][j] == 'x') {
                fputc ('X', file);
            }

            else if (board[i][j] == 'o') {
                fputc ('O', file);
            }

            else {
                fputc ('-', file);
            }

            if (j != 2) {
                fputc (' ', file);
            }
        }

        fputc ('\n', file);
    }

    fprintf (file, "%d", last_player);

    fclose (file);
}