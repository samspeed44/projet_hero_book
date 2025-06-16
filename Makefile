# Nom de l'exécutable
EXEC = htmlgen

# Fichiers sources
SRC = main.c get_chapter.c

# Commande de compilation
$(EXEC): $(SRC)
	gcc -o $(EXEC) $(SRC)

# Exécute le programme pour générer les .html
run: $(EXEC)
	./$(EXEC)

# Nettoie l'exécutable
clean:
	rm -f $(EXEC)

# Supprime les fichiers HTML générés
clean-html:
	rm -f *.html
