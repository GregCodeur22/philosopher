# Variables
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -I includes/
THREADS = -pthread

# Dossiers
SRC_DIR = src
OBJ_DIR = obj

# Récupère tous les fichiers .c dans src/
SRC = $(wildcard $(SRC_DIR)/*.c)

# Transforme src/file.c en obj/file.o
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Nom de l'exécutable
EXEC = philo

# Cible principale
all: $(EXEC)

# Lien final
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(THREADS) -o $@ $^

# Compilation .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crée le dossier obj si nécessaire
$(OBJ_DIR):
	mkdir -p $@

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(EXEC)

re: fclean all
