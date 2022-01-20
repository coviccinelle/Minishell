#include "../../minishell.h"

/*
path resolution http://manpagesfr.free.fr/man/man7/path_resolution.7.html
Étape 1 : Démarrer le processus de résolution
Résolution de chemin sous Unix/Linux - Trouver le fichier référencé par son nom
Si le chemin débute avec le caractère « / » (chemin absolu), le répertoire de recherche de départ est le répertoire racine du processus appelant. (Un processus hérite son répertoire racine de son père. Habituellement, c'est le répertoire racine de la hiérarchie des fichiers. Un processus peut avoir un répertoire racine différent avec l'utilisation de l'appel système chroot(2). Un processus peut récupérer un espace nom privé entier dans le cas où lui - ou un de ses parents - a été démarré par une invocation de l'appel système clone(2) avec l'attribut CLONE_NEWNS positionné.) Cela gère la partie « / » du chemin. 
Si le chemin ne débute pas par le caractère « / » (chemin relatif), le répertoire de recherche de départ du processus de résolution est le répertoire courant du processus. (Lui aussi est hérité du père. Il peut être modifié avec l'appel système chdir(2).)
Étape 2 : Se promener le long du chemin
Le répertoire de recherche courant est le répertoire de recherche de départ. On appellera composant d'un chemin une sous-chaîne délimitée par des caractères « / ». Chaque composant du chemin qui n'est pas le composant final est recherché dans le répertoire de recherche courant.
Si le processus n'a pas les permissions nécessaires pour effectuer la recherche dans le répertoire de recherche courant, une erreur EACCES est renvoyée (« Permission refusée », Ndt : « Permission denied »).
*/
https://github.com/maxime-42/minishell/blob/master/src/exec/get_absolut_path.c

int main(int ac, char **av)
{


    const char * path = getenv("PATH");
    printf( "PATH environment variable == %s\n", path );
//	printf("%s\n", realpath(path, NULL));
    return 0;
}
