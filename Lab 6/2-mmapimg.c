#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

const char* MMAPFILENAME = "/tmp/mmapimg";

/* Wyświetla komunikat o błędzie (na podstawie errno)
 * jeśli ret_val == -1 i kończy działanie programu ze statusem 1,
 * w przeciwnym przypadku zwraca ret_val
 */

int handle_error(int ret_val, const char* fname, const char* progname) {
	if (ret_val == -1) {
		fprintf(stderr, "%s: %s: %s\n", progname, fname, strerror(errno));
		exit(1);
	}

	return ret_val;
}

/* Pyta użytkownika o nazwę pliku
 * Zwraca -1 jeśli wystąpił błąd,
 * 0 jeśli użytkownik zażądął koniec działania lub
 * 1 w pozostałych przypadkach.
 */

int read_pathname(char* pathname, size_t pathname_len) {
	printf("Podaj nazwę pliku lub znak '.' aby zakończyć: ");

	// końcówka `pathname` może wyglądać tak:
	//      -5 -4 -3  -2  -1
	//   ... ?  ?  ? [ 0]  ?
	//   ... c  d \n [ 0]  ?
	//   ... b  c  d [\n]  0
	//   ... a  b  c [ d]  0  -- nie jest wczytana cała linia
	char* overwrite_test = pathname + pathname_len-2;
	*overwrite_test = 0;
	if (!fgets(pathname, pathname_len, stdin)) {
		return -1;
	}
	if (*overwrite_test != 0 && *overwrite_test != '\n') {
		errno = ENAMETOOLONG;
		return -1;
	}

	// skasuj znak '\n'
	pathname[strlen(pathname)-1] = 0;

	return strcmp(pathname, ".") != 0;
}

/* Pobiera rozmiar pliku.
 * Zwraca -1 jeśli wystąpił błąd,
 * 0 jeśli plik nie istnieje lub
 * 1 w przeciwnym przypadku
 */

int get_file_size(const char* pathname, size_t* filesize) {
	struct stat sstat;

	if (stat(pathname, &sstat) == -1) {
		if (errno == ENOENT) {
			puts("Podany plik nie istnieje");
			return 0;
		}
		return -1;
	}

	*filesize = sstat.st_size;
	return 1;
}

/* Wczytuje plik o podanej nazwie do pamięci.
 * Zwraca -1 jeśli wystąpił błąd lub
 * 1 w przeciwnym przypadku.
 */

int read_file_to_mem(const char* pathname, char* filemem, size_t filesize) {
	size_t read_count;
	FILE* f = fopen(pathname, "r");
	if (f == NULL) {
		return -1;
	}
	while (filesize > 0 && (read_count = fread(filemem, sizeof(char), 512, f))) {
		filemem += read_count;
		filesize -= read_count;
	}
	fclose(f);
	return 1;
}


/* Uruchamia proces qiv.
 * Zwraca -1 jeśli wystąpił błąd lub pid uruchomionego procesu.
 */

pid_t start_qiv_process(const char* progname) {
	pid_t pid = handle_error(fork(), "fork", progname);

	if (pid == 0) {
		int fd[2];
		pipe(fd);
		dup2(fd[1], 1);
		dup2(fd[1], 2);
		handle_error(execlp("qiv", "qiv", "--watch", MMAPFILENAME, NULL), "exec", progname);
		return -1;
	}

	return pid;
}

int main(int argc, char const *argv[]) {
	int fd;
	pid_t qiv_pid;
	char *filemem, pathname[256];
	size_t old_size = 1, new_size;

	fd = handle_error(open(MMAPFILENAME, O_RDWR|O_CREAT|O_TRUNC, 0660), "open", *argv);
	handle_error(ftruncate(fd, old_size), "ftruncate", *argv);
	filemem = mmap(NULL, old_size, PROT_WRITE, MAP_SHARED, fd, 0);
	if (filemem == (void*) -1) {
		handle_error(-1, "mmap", *argv);
	}

	printf("Nazwa pliku mapowanego: '%s'\n", MMAPFILENAME);

	while (1) {
		// wczytaj nazwę pliku
		if (handle_error(read_pathname(pathname, sizeof(pathname)), "read_pathname", *argv) == 0) {
			// użytkownik zażądął koniec działania
			break;
		}

		// pobierz jego rozmiar
		if (handle_error(get_file_size(pathname, &new_size), "get_file_size", *argv) == 0) {
			// plik nie istnieje
			continue;
		}

		// zmien rozmiar pliku mapowanego oraz pamięci
		handle_error(ftruncate(fd, new_size), "ftruncate", *argv);
		filemem = mremap(filemem, old_size, new_size, MREMAP_MAYMOVE);
		if (filemem == (void*) -1) {
			handle_error(-1, "mremap", *argv);
		}

 		// wczytaj plik do pamięci
		handle_error(read_file_to_mem(pathname, filemem, new_size), "read_file_to_mem", *argv);
		old_size = new_size;

		// uruchom qiv jeśli nie został uruchomiony wcześniej
		if (!qiv_pid) {
			qiv_pid = handle_error(start_qiv_process(*argv), "start_qiv_process", *argv);
		}
	}

	if (qiv_pid) {
		kill(qiv_pid, SIGTERM);
		wait(NULL);
	}

	close(fd);

	return 0;
}
